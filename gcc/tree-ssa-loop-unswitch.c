/* Loop unswitching.
   Copyright (C) 2004-2021 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

GCC is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "tree.h"
#include "gimple.h"
#include "tree-pass.h"
#include "ssa.h"
#include "fold-const.h"
#include "gimplify.h"
#include "tree-cfg.h"
#include "tree-ssa.h"
#include "tree-ssa-loop-niter.h"
#include "tree-ssa-loop.h"
#include "tree-into-ssa.h"
#include "cfgloop.h"
#include "tree-inline.h"
#include "gimple-iterator.h"
#include "cfghooks.h"
#include "tree-ssa-loop-manip.h"
#include "tree-pretty-print.h"
#include "gimple-range.h"
#include "dbgcnt.h"

#include <utility>

/* This file implements the loop unswitching, i.e. transformation of loops like

   while (A)
     {
       if (inv)
         B;

       X;

       if (!inv)
	 C;
     }

   where inv is the loop invariant, into

   if (inv)
     {
       while (A)
	 {
           B;
	   X;
	 }
     }
   else
     {
       while (A)
	 {
	   X;
	   C;
	 }
     }

   Inv is considered invariant iff the values it compares are both invariant;
   tree-ssa-loop-im.c ensures that all the suitable conditions are in this
   shape.  */

/* A tuple that holds GIMPLE condition and value range for an unswitching
   predicate.  */

struct unswitch_predicate
{
  /* Default constructor.  */
  unswitch_predicate (tree cond, tree lhs_)
  : condition (cond), lhs (lhs_), true_range (), false_range ()
  {}

  tree condition;
  tree lhs;
  int_range_max true_range;
  int_range_max false_range;
};

/* Cache storage for unswitch_predicate belonging to a basic block.  */
static vec<vec<unswitch_predicate *>> *bb_predicates = NULL;

/* Ranger instance used in the pass.  */
static gimple_ranger *ranger = NULL;

/* The type represents a predicate path leading to a basic block.  */
typedef auto_vec<std::pair<unswitch_predicate *, bool>> predicate_vector;

static class loop *tree_unswitch_loop (class loop *, basic_block, tree);
static bool tree_unswitch_single_loop (class loop *, int,
				       predicate_vector &predicate_path);
static void
find_unswitching_predicates_for_bb (basic_block bb, class loop *loop,
				    vec<unswitch_predicate *> &candidates);
static bool tree_unswitch_outer_loop (class loop *);
static edge find_loop_guard (class loop *);
static bool empty_bb_without_guard_p (class loop *, basic_block);
static bool used_outside_loop_p (class loop *, tree);
static void hoist_guard (class loop *, edge);
static bool check_exit_phi (class loop *);
static tree get_vop_from_header (class loop *);

/* Return vector of predicates that belong to a basic block.  */

static vec<unswitch_predicate *> &
get_predicates_for_bb (basic_block bb)
{
  gimple *last = last_stmt (bb);
  return (*bb_predicates)[last == NULL ? 0 : gimple_uid (last)];
}

/* Save predicates that belong to a basic block.  */

static void
set_predicates_for_bb (basic_block bb, vec<unswitch_predicate *> predicates)
{
  gimple_set_uid (last_stmt (bb), bb_predicates->length ());
  bb_predicates->safe_push (predicates);
}

/* Initialize LOOP information reused during the unswitching pass.  */

static void
init_loop_unswitch_info (class loop *loop)
{
  /* Calculate instruction count.  */
  basic_block *bbs = get_loop_body (loop);
  for (unsigned i = 0; i < loop->num_nodes; i++)
    {
      unsigned insns = 0;
      for (gimple_stmt_iterator gsi = gsi_start_bb (bbs[i]); !gsi_end_p (gsi);
	   gsi_next (&gsi))
	insns += estimate_num_insns (gsi_stmt (gsi), &eni_size_weights);

      bbs[i]->aux = (void *)(size_t)insns;
    }

  /* Find all unswitching candidates.  */
  for (unsigned i = 0; i != loop->num_nodes; i++)
    {
      /* Find a bb to unswitch on.  */
      vec<unswitch_predicate *> candidates;
      candidates.create (1);
      find_unswitching_predicates_for_bb (bbs[i], loop, candidates);
      if (!candidates.is_empty ())
	set_predicates_for_bb (bbs[i], candidates);
      else
	{
	  gimple *last = last_stmt (bbs[i]);
	  if (last != NULL)
	    gimple_set_uid (last, 0);
	}
    }

  free (bbs);
}

/* Main entry point.  Perform loop unswitching on all suitable loops.  */

unsigned int
tree_ssa_unswitch_loops (void)
{
  bool changed = false;

  ranger = enable_ranger (cfun);

  /* Go through all loops starting from innermost.  */
  for (auto loop : loops_list (cfun, LI_FROM_INNERMOST))
    {
      if (!loop->inner)
	{
	  bb_predicates = new vec<vec<unswitch_predicate *>> ();
	  bb_predicates->safe_push (vec<unswitch_predicate *> ());

	  /* Unswitch innermost loop.  */
	  init_loop_unswitch_info (loop);
	  predicate_vector predicate_path;
	  changed |= tree_unswitch_single_loop (loop, 0, predicate_path);

	  delete bb_predicates;
	  bb_predicates = NULL;
	}
      else
	changed |= tree_unswitch_outer_loop (loop);
    }


  disable_ranger (cfun);
  clear_aux_for_blocks ();

  if (changed)
    return TODO_cleanup_cfg;
  return 0;
}

/* Return TRUE if an SSA_NAME maybe undefined and is therefore
   unsuitable for unswitching.  STMT is the statement we are
   considering for unswitching and LOOP is the loop it appears in.  */

static bool
is_maybe_undefined (const tree name, gimple *stmt, class loop *loop)
{
  /* The loop header is the only block we can trivially determine that
     will always be executed.  If the comparison is in the loop
     header, we know it's OK to unswitch on it.  */
  if (gimple_bb (stmt) == loop->header)
    return false;

  auto_bitmap visited_ssa;
  auto_vec<tree> worklist;
  worklist.safe_push (name);
  bitmap_set_bit (visited_ssa, SSA_NAME_VERSION (name));
  while (!worklist.is_empty ())
    {
      tree t = worklist.pop ();

      /* If it's obviously undefined, avoid further computations.  */
      if (ssa_undefined_value_p (t, true))
	return true;

      if (ssa_defined_default_def_p (t))
	continue;

      gimple *def = SSA_NAME_DEF_STMT (t);

      /* Check that all the PHI args are fully defined.  */
      if (gphi *phi = dyn_cast <gphi *> (def))
	{
	  for (unsigned i = 0; i < gimple_phi_num_args (phi); ++i)
	    {
	      tree t = gimple_phi_arg_def (phi, i);
	      /* If an SSA has already been seen, it may be a loop,
		 but we can continue and ignore this use.  Otherwise,
		 add the SSA_NAME to the queue and visit it later.  */
	      if (TREE_CODE (t) == SSA_NAME
		  && bitmap_set_bit (visited_ssa, SSA_NAME_VERSION (t)))
		worklist.safe_push (t);
	    }
	  continue;
	}

      /* Uses in stmts always executed when the region header executes
	 are fine.  */
      if (dominated_by_p (CDI_DOMINATORS, loop->header, gimple_bb (def)))
	continue;

      /* Handle calls and memory loads conservatively.  */
      if (!is_gimple_assign (def)
	  || (gimple_assign_single_p (def)
	      && gimple_vuse (def)))
	return true;

      /* Check that any SSA names used to define NAME are also fully
	 defined.  */
      use_operand_p use_p;
      ssa_op_iter iter;
      FOR_EACH_SSA_USE_OPERAND (use_p, def, iter, SSA_OP_USE)
	{
	  tree t = USE_FROM_PTR (use_p);
	  /* If an SSA has already been seen, it may be a loop,
	     but we can continue and ignore this use.  Otherwise,
	     add the SSA_NAME to the queue and visit it later.  */
	  if (bitmap_set_bit (visited_ssa, SSA_NAME_VERSION (t)))
	    worklist.safe_push (t);
	}
    }
  return false;
}

/* Checks whether we can unswitch LOOP on condition at end of BB -- one of its
   basic blocks (for what it means see comments below).
   All candidates all filled to the provided vector CANDIDATES.  */

static void
find_unswitching_predicates_for_bb (basic_block bb, class loop *loop,
				    vec<unswitch_predicate *> &candidates)
{
  gimple *last, *def;
  gcond *stmt;
  tree cond, use;
  basic_block def_bb;
  ssa_op_iter iter;

  /* BB must end in a simple conditional jump.  */
  last = last_stmt (bb);
  if (!last || gimple_code (last) != GIMPLE_COND)
    return;
  stmt = as_a <gcond *> (last);

  /* To keep the things simple, we do not directly remove the conditions,
     but just replace tests with 0 != 0 resp. 1 != 0.  Prevent the infinite
     loop where we would unswitch again on such a condition.  */
  if (gimple_cond_true_p (stmt) || gimple_cond_false_p (stmt))
    return;

  /* Condition must be invariant.  */
  FOR_EACH_SSA_TREE_OPERAND (use, stmt, iter, SSA_OP_USE)
    {
      def = SSA_NAME_DEF_STMT (use);
      def_bb = gimple_bb (def);
      if (def_bb
	  && flow_bb_inside_loop_p (loop, def_bb))
	return;
      /* Unswitching on undefined values would introduce undefined
	 behavior that the original program might never exercise.  */
      if (is_maybe_undefined (use, stmt, loop))
	return;
    }

  tree lhs = gimple_cond_lhs (stmt);
  tree rhs = gimple_cond_rhs (stmt);

  cond = build2 (gimple_cond_code (stmt), boolean_type_node, lhs, rhs);
  edge edge_true, edge_false;
  extract_true_false_edges_from_block (bb, &edge_true, &edge_false);

  unswitch_predicate *predicate = new unswitch_predicate (cond, lhs);
  if (irange::supports_type_p (TREE_TYPE (lhs)) && CONSTANT_CLASS_P (rhs))
    {
      ranger->range_on_edge (predicate->true_range, edge_true, lhs);
      predicate->false_range = predicate->true_range;

      if (!predicate->false_range.varying_p ()
	  && !predicate->false_range.undefined_p ())
	predicate->false_range.invert ();
    }

  candidates.safe_push (predicate);
}

static void
combine_range (predicate_vector &predicate_path, tree index, irange &path_range)
{
  bool first = true;

  for (auto p: predicate_path)
    {
      unswitch_predicate *predicate = p.first;
      bool true_edge = p.second;

      if (operand_equal_p (predicate->lhs, index, 0))
	{
	  irange &other
	    = true_edge ? predicate->true_range : predicate->false_range;
	  if (first)
	    {
	      first = false;
	      path_range = other;
	    }
	  else
	    path_range.intersect (other);
	}
    }
}

/* Simplifies COND using checks in front of the entry of the LOOP.
   Utilize both symbolic expressions and value ranges calculated by Ranger.  */

static tree
evaluate_control_stmt_using_entry_checks (gimple *stmt,
					  predicate_vector &predicate_path)
{
  if (predicate_path.is_empty ())
    return NULL_TREE;

  tree lhs = gimple_cond_lhs (stmt);
  unswitch_predicate *last_predicate = predicate_path.last ().first;
  bool true_edge = predicate_path.last ().second;

  if (gimple_code (stmt) == GIMPLE_COND
      && operand_equal_p (lhs, last_predicate->lhs, 0))
    {
      if (gimple_cond_code (stmt) == TREE_CODE (last_predicate->condition)
	  && operand_equal_p (gimple_cond_rhs (stmt),
			      TREE_OPERAND (last_predicate->condition, 1), 0))
	return true_edge ? boolean_true_node : boolean_false_node;
      else if (irange::supports_type_p (TREE_TYPE (lhs)))
	{
	  int_range_max r;
	  int_range_max path_range;
	  combine_range (predicate_path, lhs, path_range);
	  if (!path_range.undefined_p ()
	      && fold_range (r, stmt, path_range)
	      && r.singleton_p ())
	    return r.zero_p () ? boolean_false_node : boolean_true_node;
	}
    }

  return NULL_TREE;
}

/* Simplify LOOP based on PREDICATE_PATH where dead edges are properly
   marked.  */

static bool
simplify_loop_version (class loop *loop, predicate_vector &predicate_path)
{
  bool changed = false;
  basic_block *bbs = get_loop_body (loop);

  for (unsigned i = 0; i != loop->num_nodes; i++)
    {
      // FIXME: works only for gconds
      if (!get_predicates_for_bb (bbs[i]).is_empty ())
	{
	  gimple *stmt = last_stmt (bbs[i]);

	  tree folded = evaluate_control_stmt_using_entry_checks (stmt,
								  predicate_path);
	  if (folded != NULL_TREE)
	    {
	      /* Remove path.  */
	      gcond *cond = dyn_cast<gcond *> (stmt);
	      if (integer_nonzerop (folded))
		gimple_cond_set_condition_from_tree (cond, boolean_true_node);
	      else
		gimple_cond_set_condition_from_tree (cond, boolean_false_node);

	      gimple_set_uid (cond, 0);
	      update_stmt (cond);
	      changed = true;
	    }
	}
    }

  free (bbs);
  return changed;
}

/* Evaluate how many instructions will be executed if we unswitch
   LOOP (with BBS) based on PREDICATE_PATH.
   REACHABLE_FLAG is used for marking of the basic blocks.  */

static unsigned
evaluate_insns (class loop *loop, basic_block *bbs,
		predicate_vector &predicate_path,
		auto_bb_flag &reachable_flag)
{
  auto_vec<basic_block> worklist (loop->num_nodes);
  worklist.quick_push (bbs[0]);

  while (!worklist.is_empty ())
    {
      edge e;
      edge_iterator ei;
      int flags = 0;
      basic_block bb = worklist.pop ();

      if (EDGE_COUNT (bb->succs) == 2)
	{
	  gcond *cond = dyn_cast<gcond *> (last_stmt (bb));
	  if (cond != NULL)
	    {
	      if (gimple_cond_true_p (cond))
		flags = EDGE_FALSE_VALUE;
	      else if (gimple_cond_false_p (cond))
		flags = EDGE_TRUE_VALUE;
	      else
		{
		  // FIXME: works only for gconds
		  unswitch_predicate *predicate = NULL;
		  if (!get_predicates_for_bb (bb).is_empty ())
		    predicate = get_predicates_for_bb (bb)[0];

		  if (predicate != NULL)
		    {
		      tree folded
			= evaluate_control_stmt_using_entry_checks (cond,
								    predicate_path);
		      if (folded == boolean_true_node)
			flags = EDGE_FALSE_VALUE;
		      else if (folded == boolean_false_node)
			flags = EDGE_TRUE_VALUE;
		    }
		}
	    }
	}

      FOR_EACH_EDGE (e, ei, bb->succs)
	{
	  basic_block dest = e->dest;

	  if (dest->loop_father == loop
	      && !(dest->flags & reachable_flag)
	      && !(e->flags & flags))
	    {
	      worklist.safe_push (dest);
	      dest->flags |= reachable_flag;
	    }
	}
    }

  /* Evaluate insns.  */
  unsigned size = 0;

  for (unsigned i = 0; i < loop->num_nodes; i++)
    if (bbs[i]->flags & reachable_flag)
      size += (size_t)bbs[i]->aux;

  /* Clear the flag from basic blocks.  */
  for (unsigned i = 0; i < loop->num_nodes; i++)
    bbs[i]->flags &= ~reachable_flag;

  return size;
}

/* Evaluate how many instruction will we have if we unswitch LOOP (with BBS)
   based on PREDICATE predicate (using PREDICATE_PATH).  */

static unsigned
evaluate_loop_insns_for_predicate (class loop *loop, basic_block *bbs,
				   predicate_vector &predicate_path,
				   unswitch_predicate *predicate)
{
  auto_bb_flag reachable_flag (cfun);

  predicate_path.safe_push (std::make_pair (predicate, true));
  unsigned true_loop_cost = evaluate_insns (loop, bbs, predicate_path,
					    reachable_flag);
  predicate_path.pop ();

  predicate_path.safe_push (std::make_pair (predicate, false));
  unsigned false_loop_cost = evaluate_insns (loop, bbs, predicate_path,
					     reachable_flag);
  predicate_path.pop ();

  return true_loop_cost + false_loop_cost;
}

/* Unswitch single LOOP.  NUM is number of unswitchings done; we do not allow
   it to grow too much, it is too easy to create example on that the code would
   grow exponentially.  PREDICATE_PATH contains so far used predicates
   for unswitching.  */

static bool
tree_unswitch_single_loop (class loop *loop, int num,
			   predicate_vector &predicate_path)
{
  basic_block *bbs = NULL;
  class loop *nloop;
  bool changed = false;
  HOST_WIDE_INT iterations;

  /* Perform initial tests if unswitch is eligible.  */
  if (num == 0)
    {
      /* Do not unswitch in cold regions. */
      if (optimize_loop_for_size_p (loop))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, ";; Not unswitching cold loops\n");
	  return false;
	}

      /* If the loop is not expected to iterate, there is no need
	 for unswitching.  */
      iterations = estimated_loop_iterations_int (loop);
      if (iterations < 0)
        iterations = likely_max_loop_iterations_int (loop);
      if (iterations >= 0 && iterations <= 1)
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, ";; Not unswitching, loop is not expected"
		     " to iterate\n");
	  return false;
	}
    }

  unswitch_predicate *predicate = NULL;
  basic_block bb = NULL;
  if (num > param_max_unswitch_level)
    {
      if (dump_file
	  && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, ";; Not unswitching anymore, hit max level\n");
      goto exit;
    }

  bbs = get_loop_body (loop);

  for (unsigned i = 0; i < loop->num_nodes; i++)
    {
      vec<unswitch_predicate *> &preds = get_predicates_for_bb (bbs[i]);
      for (auto pred: preds)
	{
	  // FIXME: update badget costing
	  unsigned cost
	    = evaluate_loop_insns_for_predicate (loop, bbs, predicate_path,
						 pred);

	  /* FIXME: right now we select first candidate, but we can choose
	     a cheapest (best) one.  */
	  if (cost <= (unsigned)param_max_unswitch_insns)
	    {
	      predicate = pred;
	      bb = bbs[i];
	      break;
	    }
	  else if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, ";; Not unswitching condition, cost too big "
		       "(%d insns): ", cost);
	      print_generic_expr (dump_file, pred->condition);
	      fprintf (dump_file, "\n");
	    }
	}
    }

  if (predicate != NULL)
    {
      if (!dbg_cnt (loop_unswitch))
	goto exit;

      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, ";; Unswitching loop on condition: ");
	  print_generic_expr (dump_file, predicate->condition);
	  fprintf (dump_file, "\n");
	}

      initialize_original_copy_tables ();
      /* Unswitch the loop on this condition.  */
      nloop = tree_unswitch_loop (loop, bb, predicate->condition);
      if (!nloop)
	{
	  free_original_copy_tables ();
	  goto exit;
	}

      /* Copy BB costs.  */
      basic_block *bbs2 = get_loop_body (nloop);
      for (unsigned i = 0; i < nloop->num_nodes; i++)
	bbs2[i]->aux = get_bb_original (bbs2[i])->aux;

      free (bbs2);

      /* Update the SSA form after unswitching.  */
      update_ssa (TODO_update_ssa);
      free_original_copy_tables ();

      /* Invoke itself on modified loops.  */
      predicate_path.safe_push (std::make_pair (predicate, false));
      changed |= simplify_loop_version (nloop, predicate_path);
      tree_unswitch_single_loop (nloop, num + 1, predicate_path);
      predicate_path.pop ();

      predicate_path.safe_push (std::make_pair (predicate, true));
      changed |= simplify_loop_version (loop, predicate_path);
      tree_unswitch_single_loop (loop, num + 1, predicate_path);
      predicate_path.pop ();
      changed = true;
    }

exit:
  free (bbs);
  return changed;
}

/* Unswitch a LOOP w.r. to given basic block UNSWITCH_ON.  We only support
   unswitching of innermost loops.  COND is the condition determining which
   loop is entered -- the new loop is entered if COND is true.  Returns NULL
   if impossible, new loop otherwise.  */

static class loop *
tree_unswitch_loop (class loop *loop,
		    basic_block unswitch_on, tree cond)
{
  profile_probability prob_true;
  edge edge_true, edge_false;

  /* Some sanity checking.  */
  gcc_assert (flow_bb_inside_loop_p (loop, unswitch_on));
  gcc_assert (EDGE_COUNT (unswitch_on->succs) == 2);
  gcc_assert (loop->inner == NULL);

  extract_true_false_edges_from_block (unswitch_on, &edge_true, &edge_false);
  prob_true = edge_true->probability;
  return loop_version (loop, unshare_expr (cond),
		       NULL, prob_true,
		       prob_true.invert (),
		       prob_true, prob_true.invert (),
		       false);
}

/* Unswitch outer loops by hoisting invariant guard on
   inner loop without code duplication.  */
static bool
tree_unswitch_outer_loop (class loop *loop)
{
  edge exit, guard;
  HOST_WIDE_INT iterations;

  gcc_assert (loop->inner);
  if (loop->inner->next)
    return false;
  /* Accept loops with single exit only which is not from inner loop.  */
  exit = single_exit (loop);
  if (!exit || exit->src->loop_father != loop)
    return false;
  /* Check that phi argument of exit edge is not defined inside loop.  */
  if (!check_exit_phi (loop))
    return false;
  /* If the loop is not expected to iterate, there is no need
      for unswitching.  */
  iterations = estimated_loop_iterations_int (loop);
  if (iterations < 0)
    iterations = likely_max_loop_iterations_int (loop);
  if (iterations >= 0 && iterations <= 1)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, ";; Not unswitching, loop is not expected"
		 " to iterate\n");
      return false;
    }

  bool changed = false;
  while ((guard = find_loop_guard (loop)))
    {
      if (! changed)
	rewrite_virtuals_into_loop_closed_ssa (loop);
      hoist_guard (loop, guard);
      changed = true;
    }
  return changed;
}

/* Checks if the body of the LOOP is within an invariant guard.  If this
   is the case, returns the edge that jumps over the real body of the loop,
   otherwise returns NULL.  */

static edge
find_loop_guard (class loop *loop)
{
  basic_block header = loop->header;
  edge guard_edge, te, fe;
  basic_block *body = NULL;
  unsigned i;
  tree use;
  ssa_op_iter iter;

  /* We check for the following situation:

     while (1)
       {
	 [header]]
         loop_phi_nodes;
	 something1;
	 if (cond1)
	   body;
	 nvar = phi(orig, bvar) ... for all variables changed in body;
	 [guard_end]
	 something2;
	 if (cond2)
	   break;
	 something3;
       }

     where:

     1) cond1 is loop invariant
     2) If cond1 is false, then the loop is essentially empty; i.e.,
	a) nothing in something1, something2 and something3 has side
	   effects
	b) anything defined in something1, something2 and something3
	   is not used outside of the loop.  */

  gcond *cond;
  do
    {
      basic_block next = NULL;
      if (single_succ_p (header))
	next = single_succ (header);
      else
	{
	  cond = safe_dyn_cast <gcond *> (last_stmt (header));
	  if (! cond)
	    return NULL;
	  extract_true_false_edges_from_block (header, &te, &fe);
	  /* Make sure to skip earlier hoisted guards that are left
	     in place as if (true).  */
	  if (gimple_cond_true_p (cond))
	    next = te->dest;
	  else if (gimple_cond_false_p (cond))
	    next = fe->dest;
	  else
	    break;
	}
      /* Never traverse a backedge.  */
      if (header->loop_father->header == next)
	return NULL;
      header = next;
    }
  while (1);
  if (!flow_bb_inside_loop_p (loop, te->dest)
      || !flow_bb_inside_loop_p (loop, fe->dest))
    return NULL;

  if (just_once_each_iteration_p (loop, te->dest)
      || (single_succ_p (te->dest)
	  && just_once_each_iteration_p (loop, single_succ (te->dest))))
    {
      if (just_once_each_iteration_p (loop, fe->dest))
	return NULL;
      guard_edge = te;
    }
  else if (just_once_each_iteration_p (loop, fe->dest)
	   || (single_succ_p (fe->dest)
	       && just_once_each_iteration_p (loop, single_succ (fe->dest))))
    guard_edge = fe;
  else
    return NULL;

  /* Guard edge must skip inner loop.  */
  if (!dominated_by_p (CDI_DOMINATORS, loop->inner->header,
      guard_edge == fe ? te->dest : fe->dest))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Guard edge %d --> %d is not around the loop!\n",
		 guard_edge->src->index, guard_edge->dest->index);
      return NULL;
    }
  if (guard_edge->dest == loop->latch)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Guard edge destination is loop latch.\n");
      return NULL;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file,
	     "Considering guard %d -> %d in loop %d\n",
	     guard_edge->src->index, guard_edge->dest->index, loop->num);
  /* Check if condition operands do not have definitions inside loop since
     any bb copying is not performed.  */
  FOR_EACH_SSA_TREE_OPERAND (use, cond, iter, SSA_OP_USE)
    {
      gimple *def = SSA_NAME_DEF_STMT (use);
      basic_block def_bb = gimple_bb (def);
      if (def_bb
          && flow_bb_inside_loop_p (loop, def_bb))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "  guard operands have definitions"
				" inside loop\n");
	  return NULL;
	}
    }

  body = get_loop_body (loop);
  for (i = 0; i < loop->num_nodes; i++)
    {
      basic_block bb = body[i];
      if (bb->loop_father != loop)
	continue;
      if (bb->flags & BB_IRREDUCIBLE_LOOP)
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "Block %d is marked as irreducible in loop\n",
		      bb->index);
	  guard_edge = NULL;
	  goto end;
	}
      if (!empty_bb_without_guard_p (loop, bb))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "  block %d has side effects\n", bb->index);
	  guard_edge = NULL;
	  goto end;
	}
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "  suitable to hoist\n");
end:
  if (body)
    free (body);
  return guard_edge;
}

/* Returns true if
   1) no statement in BB has side effects
   2) assuming that edge GUARD is always taken, all definitions in BB
      are noy used outside of the loop.
   KNOWN_INVARIANTS is a set of ssa names we know to be invariant, and
   PROCESSED is a set of ssa names for that we already tested whether they
   are invariant or not.  */

static bool
empty_bb_without_guard_p (class loop *loop, basic_block bb)
{
  basic_block exit_bb = single_exit (loop)->src;
  bool may_be_used_outside = (bb == exit_bb
			      || !dominated_by_p (CDI_DOMINATORS, bb, exit_bb));
  tree name;
  ssa_op_iter op_iter;

  /* Phi nodes do not have side effects, but their results might be used
     outside of the loop.  */
  if (may_be_used_outside)
    {
      for (gphi_iterator gsi = gsi_start_phis (bb);
	   !gsi_end_p (gsi); gsi_next (&gsi))
	{
	  gphi *phi = gsi.phi ();
	  name = PHI_RESULT (phi);
	  if (virtual_operand_p (name))
	    continue;

	  if (used_outside_loop_p (loop, name))
	    return false;
	}
    }

  for (gimple_stmt_iterator gsi = gsi_start_bb (bb);
       !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gimple *stmt = gsi_stmt (gsi);
      if (gimple_has_side_effects (stmt))
	return false;

      if (gimple_vdef(stmt))
	return false;

      FOR_EACH_SSA_TREE_OPERAND (name, stmt, op_iter, SSA_OP_DEF)
	{
	  if (may_be_used_outside
	      && used_outside_loop_p (loop, name))
	    return false;
	}
    }
  return true;
}

/* Return true if NAME is used outside of LOOP.  */

static bool
used_outside_loop_p (class loop *loop, tree name)
{
  imm_use_iterator it;
  use_operand_p use;

  FOR_EACH_IMM_USE_FAST (use, it, name)
    {
      gimple *stmt = USE_STMT (use);
      if (!flow_bb_inside_loop_p (loop, gimple_bb (stmt)))
	return true;
    }

  return false;
}

/* Return argument for loop preheader edge in header virtual phi if any.  */

static tree
get_vop_from_header (class loop *loop)
{
  for (gphi_iterator gsi = gsi_start_phis (loop->header);
       !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gphi *phi = gsi.phi ();
      if (!virtual_operand_p (gimple_phi_result (phi)))
	continue;
      return PHI_ARG_DEF_FROM_EDGE (phi, loop_preheader_edge (loop));
    }
  return NULL_TREE;
}

/* Move the check of GUARD outside of LOOP.  */

static void
hoist_guard (class loop *loop, edge guard)
{
  edge exit = single_exit (loop);
  edge preh = loop_preheader_edge (loop);
  basic_block pre_header = preh->src;
  basic_block bb;
  edge te, fe, e, new_edge;
  gimple *stmt;
  basic_block guard_bb = guard->src;
  edge not_guard;
  gimple_stmt_iterator gsi;
  int flags = 0;
  bool fix_dom_of_exit;
  gcond *cond_stmt, *new_cond_stmt;

  bb = get_immediate_dominator (CDI_DOMINATORS, exit->dest);
  fix_dom_of_exit = flow_bb_inside_loop_p (loop, bb);
  gsi = gsi_last_bb (guard_bb);
  stmt = gsi_stmt (gsi);
  gcc_assert (gimple_code (stmt) == GIMPLE_COND);
  cond_stmt = as_a <gcond *> (stmt);
  extract_true_false_edges_from_block (guard_bb, &te, &fe);
  /* Insert guard to PRE_HEADER.  */
  if (!empty_block_p (pre_header))
    gsi = gsi_last_bb (pre_header);
  else
    gsi = gsi_start_bb (pre_header);
  /* Create copy of COND_STMT.  */
  new_cond_stmt = gimple_build_cond (gimple_cond_code (cond_stmt),
				     gimple_cond_lhs (cond_stmt),
				     gimple_cond_rhs (cond_stmt),
				     NULL_TREE, NULL_TREE);
  gsi_insert_after (&gsi, new_cond_stmt, GSI_NEW_STMT);
  /* Convert COND_STMT to true/false conditional.  */
  if (guard == te)
    gimple_cond_make_false (cond_stmt);
  else
    gimple_cond_make_true (cond_stmt);
  update_stmt (cond_stmt);
  /* Create new loop pre-header.  */
  e = split_block (pre_header, last_stmt (pre_header));
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  Moving guard %i->%i (prob ",
	       guard->src->index, guard->dest->index);
      guard->probability.dump (dump_file);
      fprintf (dump_file, ") to bb %i, new preheader is %i\n",
	       e->src->index, e->dest->index);
    }

  gcc_assert (loop_preheader_edge (loop)->src == e->dest);

  if (guard == fe)
    {
      e->flags = EDGE_TRUE_VALUE;
      flags |= EDGE_FALSE_VALUE;
      not_guard = te;
    }
  else
    {
      e->flags = EDGE_FALSE_VALUE;
      flags |= EDGE_TRUE_VALUE;
      not_guard = fe;
    }
  new_edge = make_edge (pre_header, exit->dest, flags);

  /* Determine the probability that we skip the loop.  Assume that loop has
     same average number of iterations regardless outcome of guard.  */
  new_edge->probability = guard->probability;
  profile_count skip_count = guard->src->count.nonzero_p ()
		   ? guard->count ().apply_scale (pre_header->count,
					       guard->src->count)
		   : guard->count ().apply_probability (new_edge->probability);

  if (skip_count > e->count ())
    {
      fprintf (dump_file, "  Capping count; expect profile inconsistency\n");
      skip_count = e->count ();
    }
  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "  Estimated probability of skipping loop is ");
      new_edge->probability.dump (dump_file);
      fprintf (dump_file, "\n");
    }

  /* Update profile after the transform:

     First decrease count of path from newly hoisted loop guard
     to loop header...  */
  e->probability = new_edge->probability.invert ();
  e->dest->count = e->count ();

  /* ... now update profile to represent that original guard will be optimized
     away ...  */
  guard->probability = profile_probability::never ();
  not_guard->probability = profile_probability::always ();

  /* ... finally scale everything in the loop except for guarded basic blocks
     where profile does not change.  */
  basic_block *body = get_loop_body (loop);

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "  Scaling nonguarded BBs in loop:");
  for (unsigned int i = 0; i < loop->num_nodes; i++)
    {
      basic_block bb = body[i];
      if (!dominated_by_p (CDI_DOMINATORS, bb, not_guard->dest))
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, " %i", bb->index);
	  if (e->probability.initialized_p ())
            scale_bbs_frequencies (&bb, 1, e->probability);
  	}
    }

  if (fix_dom_of_exit)
    set_immediate_dominator (CDI_DOMINATORS, exit->dest, pre_header);
  /* Add NEW_ADGE argument for all phi in post-header block.  */
  bb = exit->dest;
  for (gphi_iterator gsi = gsi_start_phis (bb);
       !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gphi *phi = gsi.phi ();
      tree arg;
      if (virtual_operand_p (gimple_phi_result (phi)))
	{
	  arg = get_vop_from_header (loop);
	  if (arg == NULL_TREE)
	    /* Use exit edge argument.  */
	    arg =  PHI_ARG_DEF_FROM_EDGE (phi, exit);
	  add_phi_arg (phi, arg, new_edge, UNKNOWN_LOCATION);
	}
      else
	{
	  /* Use exit edge argument.  */
	  arg = PHI_ARG_DEF_FROM_EDGE (phi, exit);
	  add_phi_arg (phi, arg, new_edge, UNKNOWN_LOCATION);
	}
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "\n  guard hoisted.\n");

  free (body);
}

/* Return true if phi argument for exit edge can be used
   for edge around loop.  */

static bool
check_exit_phi (class loop *loop)
{
  edge exit = single_exit (loop);
  basic_block pre_header = loop_preheader_edge (loop)->src;

  for (gphi_iterator gsi = gsi_start_phis (exit->dest);
       !gsi_end_p (gsi); gsi_next (&gsi))
    {
      gphi *phi = gsi.phi ();
      tree arg;
      gimple *def;
      basic_block def_bb;
      if (virtual_operand_p (gimple_phi_result (phi)))
	continue;
      arg = PHI_ARG_DEF_FROM_EDGE (phi, exit);
      if (TREE_CODE (arg) != SSA_NAME)
	continue;
      def = SSA_NAME_DEF_STMT (arg);
      if (!def)
	continue;
      def_bb = gimple_bb (def);
      if (!def_bb)
	continue;
      if (!dominated_by_p (CDI_DOMINATORS, pre_header, def_bb))
	/* Definition inside loop!  */
	return false;
      /* Check loop closed phi invariant.  */
      if (!flow_bb_inside_loop_p (def_bb->loop_father, pre_header))
	return false;
    }
  return true;
}

/* Loop unswitching pass.  */

namespace {

const pass_data pass_data_tree_unswitch =
{
  GIMPLE_PASS, /* type */
  "unswitch", /* name */
  OPTGROUP_LOOP, /* optinfo_flags */
  TV_TREE_LOOP_UNSWITCH, /* tv_id */
  PROP_cfg, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  0, /* todo_flags_finish */
};

class pass_tree_unswitch : public gimple_opt_pass
{
public:
  pass_tree_unswitch (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_tree_unswitch, ctxt)
  {}

  /* opt_pass methods: */
  virtual bool gate (function *) { return flag_unswitch_loops != 0; }
  virtual unsigned int execute (function *);

}; // class pass_tree_unswitch

unsigned int
pass_tree_unswitch::execute (function *fun)
{
  if (number_of_loops (fun) <= 1)
    return 0;

  return tree_ssa_unswitch_loops ();
}

} // anon namespace

gimple_opt_pass *
make_pass_tree_unswitch (gcc::context *ctxt)
{
  return new pass_tree_unswitch (ctxt);
}


