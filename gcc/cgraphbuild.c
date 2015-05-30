/* Callgraph construction.
   Copyright (C) 2003-2014 Free Software Foundation, Inc.
   Contributed by Jan Hubicka

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tree.h"
#include "tree-eh.h"
#include "predict.h"
#include "vec.h"
#include "hashtab.h"
#include "hash-set.h"
#include "machmode.h"
#include "hard-reg-set.h"
#include "input.h"
#include "function.h"
#include "dominance.h"
#include "cfg.h"
#include "basic-block.h"
#include "tree-ssa-alias.h"
#include "tree-ssa-operands.h"
#include "tree-into-ssa.h"
#include "internal-fn.h"
#include "gimple-fold.h"
#include "gimple-expr.h"
#include "is-a.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "gimple-walk.h"
#include "gimple-ssa.h"
#include "langhooks.h"
#include "intl.h"
#include "toplev.h"
#include "gcov-io.h"
#include "coverage.h"
#include "tree-pass.h"
#include "hash-map.h"
#include "plugin-api.h"
#include "ipa-ref.h"
#include "cgraph.h"
#include "ipa-utils.h"
#include "except.h"
#include "l-ipo.h"
#include "alloc-pool.h"
#include "ipa-prop.h"
#include "ipa-inline.h"

/* Context of record_reference.  */
struct record_reference_ctx
{
  bool only_vars;
  class varpool_node *varpool_node;
};

/* Walk tree and record all calls and references to functions/variables.
   Called via walk_tree: TP is pointer to tree to be examined.
   When DATA is non-null, record references to callgraph.
   */

static tree
record_reference (tree *tp, int *walk_subtrees, void *data)
{
  tree t = *tp;
  tree decl;
  record_reference_ctx *ctx = (record_reference_ctx *)data;

  t = canonicalize_constructor_val (t, NULL);
  if (!t)
    t = *tp;
  else if (t != *tp)
    *tp = t;

  switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case FUNCTION_DECL:
      gcc_unreachable ();
      break;

    case FDESC_EXPR:
    case ADDR_EXPR:
      /* Record dereferences to the functions.  This makes the
	 functions reachable unconditionally.  */
      decl = get_base_var (*tp);
      if (TREE_CODE (decl) == FUNCTION_DECL)
	{
	  cgraph_node *node = cgraph_node::get_create (decl);
	  if (!ctx->only_vars)
	    node->mark_address_taken ();
	  ctx->varpool_node->create_reference (node, IPA_REF_ADDR);
	}

      if (TREE_CODE (decl) == VAR_DECL)
	{
	  varpool_node *vnode = varpool_node::get_create (decl);
	  ctx->varpool_node->create_reference (vnode, IPA_REF_ADDR);
	}
      *walk_subtrees = 0;
      break;

    default:
      /* Save some cycles by not walking types and declaration as we
	 won't find anything useful there anyway.  */
      if (IS_TYPE_OR_DECL_P (*tp))
	{
	  *walk_subtrees = 0;
	  break;
	}
      break;
    }

  return NULL_TREE;
}

/* Record references to typeinfos in the type list LIST.  */

static void
record_type_list (cgraph_node *node, tree list)
{
  for (; list; list = TREE_CHAIN (list))
    {
      tree type = TREE_VALUE (list);
      
      if (TYPE_P (type))
	type = lookup_type_for_runtime (type);
      STRIP_NOPS (type);
      if (TREE_CODE (type) == ADDR_EXPR)
	{
	  type = TREE_OPERAND (type, 0);
	  if (TREE_CODE (type) == VAR_DECL)
	    {
	      varpool_node *vnode = varpool_node::get_create (type);
	      node->create_reference (vnode, IPA_REF_ADDR);
	    }
	}
    }
}

/* Record all references we will introduce by producing EH tables
   for NODE.  */

static void
record_eh_tables (cgraph_node *node, function *fun)
{
  eh_region i;

  if (DECL_FUNCTION_PERSONALITY (node->decl))
    {
      tree per_decl = DECL_FUNCTION_PERSONALITY (node->decl);
      cgraph_node *per_node = cgraph_node::get_create (per_decl);

      node->create_reference (per_node, IPA_REF_ADDR);
      per_node->mark_address_taken ();
    }

  i = fun->eh->region_tree;
  if (!i)
    return;

  while (1)
    {
      switch (i->type)
	{
	case ERT_CLEANUP:
	case ERT_MUST_NOT_THROW:
	  break;

	case ERT_TRY:
	  {
	    eh_catch c;
	    for (c = i->u.eh_try.first_catch; c; c = c->next_catch)
	      record_type_list (node, c->type_list);
	  }
	  break;

	case ERT_ALLOWED_EXCEPTIONS:
	  record_type_list (node, i->u.allowed.type_list);
	  break;
	}
      /* If there are sub-regions, process them.  */
      if (i->inner)
	i = i->inner;
      /* If there are peers, process them.  */
      else if (i->next_peer)
	i = i->next_peer;
      /* Otherwise, step back up the tree to the next peer.  */
      else
	{
	  do
	    {
	      i = i->outer;
	      if (i == NULL)
		return;
	    }
	  while (i->next_peer == NULL);
	  i = i->next_peer;
	}
    }
}

/* Computes the frequency of the call statement so that it can be stored in
   cgraph_edge.  BB is the basic block of the call statement.  */
int
compute_call_stmt_bb_frequency (tree decl, basic_block bb)
{
  int entry_freq = ENTRY_BLOCK_PTR_FOR_FN
  		     (DECL_STRUCT_FUNCTION (decl))->frequency;
  int freq = bb->frequency;

  if (profile_status_for_fn (DECL_STRUCT_FUNCTION (decl)) == PROFILE_ABSENT)
    return CGRAPH_FREQ_BASE;

  if (!entry_freq)
    entry_freq = 1, freq++;

  freq = freq * CGRAPH_FREQ_BASE / entry_freq;
  if (freq > CGRAPH_FREQ_MAX)
    freq = CGRAPH_FREQ_MAX;

  return freq;
}


bool cgraph_pre_profiling_inlining_done = false;

/* Return true if E is a fake indirect call edge.  */

bool
cgraph_is_fake_indirect_call_edge (struct cgraph_edge *e)
{
  return !e->call_stmt;
}


/* Add fake cgraph edges from NODE to its indirect call callees
   using profile data.  */

static void
add_fake_indirect_call_edges (struct cgraph_node *node)
{
  unsigned n_counts, i;
  gcov_type *ic_counts;

  /* Enable this only for LIPO for now.  */
  if (!L_IPO_COMP_MODE)
    return;

  ic_counts
      = get_coverage_counts_no_warn (DECL_STRUCT_FUNCTION (node->decl),
                                     GCOV_COUNTER_ICALL_TOPNV, &n_counts);

  if (!ic_counts)
    return;

  gcc_assert ((n_counts % GCOV_ICALL_TOPN_NCOUNTS) == 0);

/* After the early_inline_1 before value profile transformation,
   functions that are indirect call targets may have their bodies
   removed (extern inline functions or functions from aux modules,
   functions in comdat etc) if all direct callsites are inlined. This
   will lead to missing inline opportunities after profile based
   indirect call promotion. The solution is to add fake edges to
   indirect call targets. Note that such edges are not associated
   with actual indirect call sites because it is not possible to
   reliably match pre-early-inline indirect callsites with indirect
   call profile counters which are from post-early inline function body.  */

  for (i = 0; i < n_counts;
       i += GCOV_ICALL_TOPN_NCOUNTS, ic_counts += GCOV_ICALL_TOPN_NCOUNTS)
    {
      gcov_type val1, val2, count1, count2;
      struct cgraph_node *direct_call1 = 0, *direct_call2 = 0;

      val1 = ic_counts[1];
      count1 = ic_counts[2];
      val2 = ic_counts[3];
      count2 = ic_counts[4];

      if (val1 == 0 || count1 == 0)
        continue;

      direct_call1 = find_func_by_global_id (val1);
      if (direct_call1)
        {
          tree decl = direct_call1->decl;
          node->create_edge (cgraph_node::get_create (decl), 
														NULL,
                             count1, 0);
        }

      if (val2 == 0 || count2 == 0)
        continue;
      direct_call2 = find_func_by_global_id (val2);
      if (direct_call2)
        {
          tree decl = direct_call2->decl;
          node->create_edge (cgraph_node::get_create (decl),
                             NULL,
                             count2, 0);
        }
    }
}


/* This can be implemented as an IPA pass that must be first one 
   before any unreachable node elimination. */

void
cgraph_add_fake_indirect_call_edges (void)
{
  struct cgraph_node *node;

  /* Enable this only for LIPO for now.  */
  if (!L_IPO_COMP_MODE)
    return;

  FOR_EACH_DEFINED_FUNCTION (node)
    {
      if (!gimple_has_body_p (node->decl))
	continue;
      add_fake_indirect_call_edges (node);
    }
}

/* Remove zero count fake edges added for the purpose of ensuring
   the right processing order.  This should be called after all
   small ipa passes.  */
void
cgraph_remove_zero_count_fake_edges (void)
{
  struct cgraph_node *node;

  /* Enable this only for LIPO for now.  */
  if (!L_IPO_COMP_MODE)
    return;

  FOR_EACH_DEFINED_FUNCTION (node)
    {
      if (!gimple_has_body_p (node->decl))
	continue;

     struct cgraph_edge *e, *f;
     for (e = node->callees; e; e = f)
       {
         f = e->next_callee;
	 if (!e->call_stmt && !e->count && !e->frequency)
           e->remove ();
       }
    }
}

static void
record_reference_to_real_target_from_alias (struct cgraph_node *alias)
{
  if (!L_IPO_COMP_MODE || !cgraph_pre_profiling_inlining_done)
    return;

  /* Need to add a reference to the resolved node in LIPO
     mode to avoid the real node from eliminated  */
  if (alias->alias && alias->analyzed)
    {
      struct cgraph_node *target, *real_target;

      target = alias->get_alias_target (); 
      real_target = cgraph_lipo_get_resolved_node (target->decl);
      /* TODO: this make create duplicate entries in the reference list.  */
      if (real_target != target)
        alias->create_reference (real_target, IPA_REF_ALIAS, NULL);
    }
}

/* Mark address taken in STMT.  */

static bool
mark_address (gimple stmt, tree addr, tree, void *data)
{
  addr = get_base_address (addr);
  if (TREE_CODE (addr) == FUNCTION_DECL)
    {
      cgraph_node *node = cgraph_node::get_create (addr);
      if (L_IPO_COMP_MODE && cgraph_pre_profiling_inlining_done)
        node = cgraph_lipo_get_resolved_node (addr);
      node->mark_address_taken ();
      ((symtab_node *)data)->create_reference (node, IPA_REF_ADDR, stmt);
      record_reference_to_real_target_from_alias (node);
    }
  else if (addr && TREE_CODE (addr) == VAR_DECL
	   && (TREE_STATIC (addr) || DECL_EXTERNAL (addr)))
    {
      varpool_node *vnode = varpool_node::get_create (addr);

      ((symtab_node *)data)->create_reference (vnode, IPA_REF_ADDR, stmt);
      if (L_IPO_COMP_MODE && cgraph_pre_profiling_inlining_done)
        {
          struct varpool_node *rvnode = real_varpool_node (addr);
          if (rvnode != vnode)
	    ((symtab_node *)data)->create_reference (rvnode, IPA_REF_ADDR, stmt);
        }
    }

  return false;
}

/* Mark load of T.  */

static bool
mark_load (gimple stmt, tree t, tree, void *data)
{
  t = get_base_address (t);
  if (t && TREE_CODE (t) == FUNCTION_DECL)
    {
      /* ??? This can happen on platforms with descriptors when these are
	 directly manipulated in the code.  Pretend that it's an address.  */
      cgraph_node *node = cgraph_node::get_create (t);
      node->mark_address_taken ();
      ((symtab_node *)data)->create_reference (node, IPA_REF_ADDR, stmt);
    }
  else if (t && TREE_CODE (t) == VAR_DECL
	   && (TREE_STATIC (t) || DECL_EXTERNAL (t)))
    {
      varpool_node *vnode = varpool_node::get_create (t);

      ((symtab_node *)data)->create_reference (vnode, IPA_REF_LOAD, stmt);

      if (L_IPO_COMP_MODE && cgraph_pre_profiling_inlining_done)
        {
          struct varpool_node *rvnode = real_varpool_node (t);
          if (rvnode != vnode)
	    ((symtab_node *) data)->create_reference (rvnode, IPA_REF_ADDR, stmt);
        }
    }
  return false;
}

/* Mark store of T.  */

static bool
mark_store (gimple stmt, tree t, tree, void *data)
{
  t = get_base_address (t);
  if (t && TREE_CODE (t) == VAR_DECL
      && (TREE_STATIC (t) || DECL_EXTERNAL (t)))
    {
      varpool_node *vnode = varpool_node::get_create (t);

      ((symtab_node *)data)->create_reference (vnode, IPA_REF_STORE, stmt);
      if (L_IPO_COMP_MODE && cgraph_pre_profiling_inlining_done)
        {
          struct varpool_node *rvnode = real_varpool_node (t);
          if (rvnode != vnode)
	    ((symtab_node *) data)->create_reference (rvnode, IPA_REF_ADDR, stmt);
        }
     }
  return false;
}

/* Record all references from cgraph_node that are taken in statement STMT.  */

void
cgraph_node::record_stmt_references (gimple stmt)
{
  walk_stmt_load_store_addr_ops (stmt, this, mark_load, mark_store,
				 mark_address);
}

/* Create cgraph edges for function calls.
   Also look for functions and variables having addresses taken.  */

namespace {

const pass_data pass_data_build_cgraph_edges =
{
  GIMPLE_PASS, /* type */
  "*build_cgraph_edges", /* name */
  OPTGROUP_NONE, /* optinfo_flags */
  TV_NONE, /* tv_id */
  PROP_cfg, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class pass_build_cgraph_edges : public gimple_opt_pass
{
public:
  pass_build_cgraph_edges (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_build_cgraph_edges, ctxt)
  {}

  /* opt_pass methods: */
  virtual unsigned int execute (function *);

}; // class pass_build_cgraph_edges

unsigned int
pass_build_cgraph_edges::execute (function *fun)
{
  basic_block bb;
  cgraph_node *node = cgraph_node::get (current_function_decl);
  gimple_stmt_iterator gsi;
  tree decl;
  unsigned ix;

  /* Create the callgraph edges and record the nodes referenced by the function.
     body.  */
  FOR_EACH_BB_FN (bb, fun)
    {
      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gimple stmt = gsi_stmt (gsi);
	  tree decl;

	  if (is_gimple_debug (stmt))
	    continue;

	  if (gcall *call_stmt = dyn_cast <gcall *> (stmt))
	    {
	      int freq = compute_call_stmt_bb_frequency (current_function_decl,
							 bb);
	      decl = gimple_call_fndecl (call_stmt);
	      if (decl)
		node->create_edge (cgraph_node::get_create (decl), call_stmt, bb->count, freq);
	      else if (gimple_call_internal_p (call_stmt))
		;
	      else
		node->create_indirect_edge (call_stmt,
					    gimple_call_flags (call_stmt),
					    bb->count, freq);
	    }
	  node->record_stmt_references (stmt);
	  if (gomp_parallel *omp_par_stmt = dyn_cast <gomp_parallel *> (stmt))
	    {
	      tree fn = gimple_omp_parallel_child_fn (omp_par_stmt);
	      node->create_reference (cgraph_node::get_create (fn),
				      IPA_REF_ADDR, stmt);
	    }
	  if (gimple_code (stmt) == GIMPLE_OMP_TASK)
	    {
	      tree fn = gimple_omp_task_child_fn (stmt);
	      if (fn)
		node->create_reference (cgraph_node::get_create (fn),
					IPA_REF_ADDR, stmt);
	      fn = gimple_omp_task_copy_fn (stmt);
	      if (fn)
		node->create_reference (cgraph_node::get_create (fn),
					IPA_REF_ADDR, stmt);
	    }
	}
      for (gsi = gsi_start_phis (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	node->record_stmt_references (gsi_stmt (gsi));
   }


  /* Look for initializers of constant variables and private statics.  */
  FOR_EACH_LOCAL_DECL (fun, ix, decl)
    if (TREE_CODE (decl) == VAR_DECL
	&& (TREE_STATIC (decl) && !DECL_EXTERNAL (decl))
	&& !DECL_HAS_VALUE_EXPR_P (decl))
      varpool_node::finalize_decl (decl);
  record_eh_tables (node, fun);

  return 0;
}

} // anon namespace

gimple_opt_pass *
make_pass_build_cgraph_edges (gcc::context *ctxt)
{
  return new pass_build_cgraph_edges (ctxt);
}

/* Record references to functions and other variables present in the
   initial value of DECL, a variable.
   When ONLY_VARS is true, we mark needed only variables, not functions.  */

void
record_references_in_initializer (tree decl, bool only_vars)
{
  varpool_node *node = varpool_node::get_create (decl);
  hash_set<tree> visited_nodes;
  record_reference_ctx ctx = {false, NULL};

  ctx.varpool_node = node;
  ctx.only_vars = only_vars;
  walk_tree (&DECL_INITIAL (decl), record_reference,
             &ctx, &visited_nodes);
}

/* In LIPO mode, before tree_profiling, the call graph edge
   needs to be built with the original target node to make
   sure consistent early inline decisions between profile
   generate and profile use. After tree-profiling, the target
   needs to be set to the resolved node so that ipa-inline
   sees the definitions.  */
#include "gimple-pretty-print.h"
static void
lipo_fixup_cgraph_edge_call_target (gimple stmt)
{
  tree decl;
  gcc_assert (is_gimple_call (stmt));

  decl = gimple_call_fndecl (stmt);
  if (decl)
    {
      struct cgraph_node *real_callee;
      real_callee = cgraph_lipo_get_resolved_node (decl);

      if (decl != real_callee->decl)
        {
          int lp_nr;

          gcc_assert (!real_callee->clone.combined_args_to_skip);
          gimple_call_set_fndecl (stmt, real_callee->decl);
          update_stmt (stmt);
          lp_nr = lookup_stmt_eh_lp (stmt);
          if (lp_nr != 0 && !stmt_could_throw_p (stmt))
            remove_stmt_from_eh_lp (stmt);
        }
    }
}

/* Link the cgraph nodes, varpool nodes and fixup the call target to
   the correct decl. Remove dead functions.  */


void
lipo_link_and_fixup ()
{
  struct cgraph_node *node;

  cgraph_pre_profiling_inlining_done = true;
  cgraph_process_module_scope_statics ();
  /* Now perform link to allow cross module inlining.  */
  cgraph_do_link ();
  varpool_do_link ();
  cgraph_unify_type_alias_sets ();
  cgraph_init_gid_map ();
 
  FOR_EACH_DEFINED_FUNCTION (node)
    {
      if (!gimple_has_body_p (node->decl))
	continue;

      /* Don't profile functions produced for builtin stuff.  */
      if (DECL_SOURCE_LOCATION (node->decl) == BUILTINS_LOCATION)
	continue;

      push_cfun (DECL_STRUCT_FUNCTION (node->decl));

      if (L_IPO_COMP_MODE)
	{
	  basic_block bb;
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
		{
		  gimple stmt = gsi_stmt (gsi);
		  if (is_gimple_call (stmt))
		    lipo_fixup_cgraph_edge_call_target (stmt);
		}
	    }
	  update_ssa (TODO_update_ssa);
	}
      cgraph_edge::rebuild_edges ();
      pop_cfun ();
    }

  cgraph_add_fake_indirect_call_edges ();
  symtab->remove_unreachable_nodes (dump_file);
}


/* Rebuild cgraph edges for current function node.  This needs to be run after
   passes that don't update the cgraph.  */

unsigned int
cgraph_edge::rebuild_edges (void)
{
  basic_block bb;
  cgraph_node *node = cgraph_node::get (current_function_decl);
  gimple_stmt_iterator gsi;

  node->remove_callees ();
  node->remove_all_references ();

  node->count = ENTRY_BLOCK_PTR_FOR_FN (cfun)->count;
  node->max_bb_count = 0;

  FOR_EACH_BB_FN (bb, cfun)
    {
      if (bb->count > node->max_bb_count)
	node->max_bb_count = bb->count;
      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gimple stmt = gsi_stmt (gsi);
	  tree decl;

	  if (gcall *call_stmt = dyn_cast <gcall *> (stmt))
	    {
	      int freq = compute_call_stmt_bb_frequency (current_function_decl,
							 bb);
	      decl = gimple_call_fndecl (call_stmt);
	      if (decl)
                {
                  struct cgraph_node *callee = cgraph_node::get_create (decl);
                  if (L_IPO_COMP_MODE)
                    record_reference_to_real_target_from_alias (callee);
									node->create_edge (callee, call_stmt,
																	   bb->count, freq);
                }
	      else if (gimple_call_internal_p (call_stmt))
		;
	      else
		node->create_indirect_edge (call_stmt,
					    gimple_call_flags (call_stmt),
					    bb->count, freq);
	    }
	  node->record_stmt_references (stmt);
	}
      for (gsi = gsi_start_phis (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	node->record_stmt_references (gsi_stmt (gsi));
    }

  if (!cgraph_pre_profiling_inlining_done)
    add_fake_indirect_call_edges (node);
  record_eh_tables (node, cfun);
  gcc_assert (!node->global.inlined_to);

  if (node->instrumented_version
      && !node->instrumentation_clone)
    node->create_reference (node->instrumented_version, IPA_REF_CHKP, NULL);

  return 0;
}

/* Rebuild cgraph references for current function node.  This needs to be run
   after passes that don't update the cgraph.  */

void
cgraph_edge::rebuild_references (void)
{
  basic_block bb;
  cgraph_node *node = cgraph_node::get (current_function_decl);
  gimple_stmt_iterator gsi;
  ipa_ref *ref = NULL;
  int i;

  /* Keep speculative references for further cgraph edge expansion.  */
  for (i = 0; node->iterate_reference (i, ref);)
    if (!ref->speculative)
      ref->remove_reference ();
    else
      i++;

  node->count = ENTRY_BLOCK_PTR_FOR_FN (cfun)->count;

  FOR_EACH_BB_FN (bb, cfun)
    {
      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	node->record_stmt_references (gsi_stmt (gsi));
      for (gsi = gsi_start_phis (bb); !gsi_end_p (gsi); gsi_next (&gsi))
	node->record_stmt_references (gsi_stmt (gsi));
    }
  record_eh_tables (node, cfun);

  if (node->instrumented_version
      && !node->instrumentation_clone)
    node->create_reference (node->instrumented_version, IPA_REF_CHKP, NULL);
}

namespace {

const pass_data pass_data_rebuild_cgraph_edges =
{
  GIMPLE_PASS, /* type */
  "*rebuild_cgraph_edges", /* name */
  OPTGROUP_NONE, /* optinfo_flags */
  TV_CGRAPH, /* tv_id */
  PROP_cfg, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class pass_rebuild_cgraph_edges : public gimple_opt_pass
{
public:
  pass_rebuild_cgraph_edges (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_rebuild_cgraph_edges, ctxt)
  {}

  /* opt_pass methods: */
  opt_pass * clone () { return new pass_rebuild_cgraph_edges (m_ctxt); }
  virtual unsigned int execute (function *)
  {
    return cgraph_edge::rebuild_edges ();
  }

}; // class pass_rebuild_cgraph_edges

} // anon namespace

/* Defined in passes.c  */
extern bool cgraph_callee_edges_final_cleanup; 

gimple_opt_pass *
make_pass_rebuild_cgraph_edges (gcc::context *ctxt)
{
  return new pass_rebuild_cgraph_edges (ctxt);
}

namespace {

const pass_data pass_data_remove_cgraph_callee_edges =
{
  GIMPLE_PASS, /* type */
  "*remove_cgraph_callee_edges", /* name */
  OPTGROUP_NONE, /* optinfo_flags */
  TV_NONE, /* tv_id */
  0, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class pass_remove_cgraph_callee_edges : public gimple_opt_pass
{
public:
  pass_remove_cgraph_callee_edges (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_remove_cgraph_callee_edges, ctxt)
  {}

  /* opt_pass methods: */
  opt_pass * clone () {
    return new pass_remove_cgraph_callee_edges (m_ctxt);
  }
  virtual unsigned int execute (function *);

}; // class pass_remove_cgraph_callee_edges

unsigned int
pass_remove_cgraph_callee_edges::execute (function *)
{
  /* The -freorder-functions=* needs the call-graph preserved till
     pass_final.  */
  if (cgraph_callee_edges_final_cleanup
      && (flag_reorder_functions > 1))
      return 0;

  cgraph_node *node = cgraph_node::get (current_function_decl);
  node->remove_callees ();
  node->remove_all_references ();
  return 0;
}

} // anon namespace

gimple_opt_pass *
make_pass_remove_cgraph_callee_edges (gcc::context *ctxt)
{
  return new pass_remove_cgraph_callee_edges (ctxt);
}
