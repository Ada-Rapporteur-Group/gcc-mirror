/* Value range propagation pass using the ranger.
   Copyright (C) 2020 Free Software Foundation, Inc.
   Contributed by Aldy Hernandez <aldyh@redhat.com>.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

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
#include "gimple-pretty-print.h"
#include "cfganal.h"
#include "gimple-fold.h"
#include "tree-eh.h"
#include "gimple-iterator.h"
#include "tree-cfg.h"
#include "tree-ssa-loop-manip.h"
#include "tree-ssa-loop.h"
#include "cfgloop.h"
#include "tree-scalar-evolution.h"
#include "tree-ssa-propagate.h"
#include "alloc-pool.h"
#include "domwalk.h"
#include "tree-cfgcleanup.h"
#include "vr-values.h"
#include "gimple-ssa-evrp-analyze.h"
#include "gimple-range.h"

#include "gimple-range-trace.h"

class rvrp_ranger : public range_query
{
public:
  rvrp_ranger ()
    : simplifier (this), range_pool ("rvrp value range pool") { }
  ~rvrp_ranger ()
  {
    range_pool.release ();
  }
  virtual const value_range_equiv *get_value_range (const_tree expr,
						    gimple *stmt) OVERRIDE
  {
    widest_irange r;
    if (query.range_of_expr (r, const_cast<tree> (expr), stmt))
      return new (range_pool.allocate ()) value_range_equiv (r);
    return new (range_pool.allocate ()) value_range_equiv (TREE_TYPE (expr));
  }
  loop_ranger query;
  simplify_using_ranges simplifier;
private:
  object_allocator<value_range_equiv> range_pool;
};

class rvrp_folder : public substitute_and_fold_engine
{
public:
  rvrp_ranger ranger;

  rvrp_folder (bool allow_il_changes)
    : allow_il_changes (allow_il_changes) { }

  tree get_value (tree op, gimple *stmt) OVERRIDE
  {
    widest_irange r;
    tree singleton;
    if (ranger.query.range_of_expr (r, op, stmt) && r.singleton_p (&singleton)
	&& allow_il_changes)
      return singleton;
    return NULL;
  }

  bool fold_cond (gcond *cond)
  {
    if (!irange::supports_type_p (gimple_expr_type (cond)))
      return false;

    widest_irange r;
    if (ranger.query.range_of_stmt (r, cond) && r.singleton_p ())
      {
	if (allow_il_changes)
	  {
	    if (r.zero_p ())
	      gimple_cond_make_false (cond);
	    else
	      gimple_cond_make_true (cond);
	    return true;
	  }
      }
    return false;
  }

  bool fold_stmt (gimple_stmt_iterator *gsi) OVERRIDE
  {
    gcond *cond = dyn_cast <gcond *> (gsi_stmt (*gsi));
    if (cond && fold_cond (cond))
      return true;

    return ranger.simplifier.simplify (gsi);
  }

private:
  bool allow_il_changes;
};

static unsigned int
execute_ranger_vrp (bool allow_il_changes)
{
  loop_optimizer_init (LOOPS_NORMAL | LOOPS_HAVE_RECORDED_EXITS);
  rewrite_into_loop_closed_ssa (NULL, TODO_update_ssa);
  scev_initialize ();
  calculate_dominance_info (CDI_DOMINATORS);

  rvrp_folder folder (allow_il_changes);
  folder.substitute_and_fold ();

  scev_finalize ();
  loop_optimizer_finalize ();

  if (dump_file && (dump_flags & TDF_DETAILS))
    folder.ranger.query.dump (dump_file);
  return 0;
}

namespace {

const pass_data pass_data_ranger_vrp =
{
 GIMPLE_PASS,			// type
 "rvrp",			// name
 OPTGROUP_NONE,			// optinfo_flags
 TV_TREE_RVRP,			// tv_id
 PROP_ssa,			// properties_required
 0,				// properties_provided
 0,				// properties_destroyed
 0,				// todo_flags_start
 ( TODO_cleanup_cfg | TODO_update_ssa | TODO_verify_all ),
};

class pass_ranger_vrp : public gimple_opt_pass
{
public:
  pass_ranger_vrp (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_ranger_vrp, ctxt)
    {
      static int pass = 1;
      rvrp_pass_num = pass;
      pass++;
    }
  opt_pass *clone () { return new pass_ranger_vrp (m_ctxt); }
  virtual bool gate (function *)
    { return flag_tree_vrp != 0; }
  virtual unsigned int execute (function *)
    {
      return execute_ranger_vrp (true);
    }
private:
  bool allow_il_changes;
  int rvrp_pass_num;
};

} // anon namespace

gimple_opt_pass *
make_pass_ranger_vrp (gcc::context *ctxt)
{
  return new pass_ranger_vrp (ctxt);
}
