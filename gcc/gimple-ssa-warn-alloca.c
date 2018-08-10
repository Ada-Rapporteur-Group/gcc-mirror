/* Warn on problematic uses of alloca and variable length arrays.
   Copyright (C) 2016-2018 Free Software Foundation, Inc.
   Contributed by Aldy Hernandez <aldyh@redhat.com>.

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
#include "backend.h"
#include "tree.h"
#include "gimple.h"
#include "tree-pass.h"
#include "ssa.h"
#include "gimple-pretty-print.h"
#include "diagnostic-core.h"
#include "fold-const.h"
#include "gimple-iterator.h"
#include "tree-ssa.h"
#include "params.h"
#include "tree-cfg.h"
#include "builtins.h"
#include "calls.h"
#include "cfgloop.h"
#include "intl.h"
#include "ssa-range.h"

const pass_data pass_data_walloca = {
  GIMPLE_PASS,
  "walloca",
  OPTGROUP_NONE,
  TV_NONE,
  PROP_cfg, // properties_required
  0,	    // properties_provided
  0,	    // properties_destroyed
  0,	    // properties_start
  0,	    // properties_finish
};

class pass_walloca : public gimple_opt_pass
{
public:
  pass_walloca (gcc::context *ctxt)
    : gimple_opt_pass(pass_data_walloca, ctxt), first_time_p (false) {}
  opt_pass *clone () { return new pass_walloca (m_ctxt); }
  void set_pass_param (unsigned int n, bool param)
    {
      gcc_assert (n == 0);
      first_time_p = param;
    }
  virtual bool gate (function *);
  virtual unsigned int execute (function *);

 private:
  // Set to TRUE the first time we run this pass on a function.
  bool first_time_p;
};

bool
pass_walloca::gate (function *fun ATTRIBUTE_UNUSED)
{
  // The first time we run, we run too early in the pipeline and can
  // only perform strict alloca checking.
  if (first_time_p)
    return warn_alloca != 0;

  // Warning is disabled when its size limit is greater than PTRDIFF_MAX
  // for the target maximum, which makes the limit negative since when
  // represented in signed HOST_WIDE_INT.
  return warn_alloca_limit >= 0 || warn_vla_limit >= 0;
}

// Possible problematic uses of alloca.
enum alloca_type {
  // Alloca argument is within known bounds that are appropriate.
  ALLOCA_OK,

  // Alloca argument is KNOWN to have a value that is too large.
  ALLOCA_BOUND_DEFINITELY_LARGE,

  // Alloca argument may be too large.
  ALLOCA_BOUND_MAYBE_LARGE,

  // Alloca appears in a loop.
  ALLOCA_IN_LOOP,

  // Alloca argument is 0.
  ALLOCA_ARG_IS_ZERO,

  // Alloca call is unbounded.  That is, there is no controlling
  // predicate for its argument.
  ALLOCA_UNBOUNDED
};

// Type of an alloca call with its corresponding argument, if applicable.
struct alloca_type_and_limit {
  enum alloca_type type;
  // For ALLOCA_BOUND_MAYBE_LARGE and ALLOCA_BOUND_DEFINITELY_LARGE
  // types, this field indicates the assumed limit if known or
  // integer_zero_node if unknown.  For any other alloca types, this
  // field is undefined.
  wide_int limit;
  alloca_type_and_limit ();
  alloca_type_and_limit (enum alloca_type type,
			 wide_int i) : type(type), limit(i) { }
  alloca_type_and_limit (enum alloca_type type) : type(type) { }
};

// Analyze the alloca call in STMT and return the alloca type with its
// corresponding argument (if applicable).  IS_VLA is set if the alloca
// call was created by the gimplifier for a VLA.

static struct alloca_type_and_limit
alloca_call_type (path_ranger &ranger, gimple *stmt, bool is_vla)
{
  gcc_assert (gimple_alloca_call_p (stmt));
  tree len = gimple_call_arg (stmt, 0);

  gcc_assert (!is_vla || warn_vla_limit >= 0);
  gcc_assert (is_vla || warn_alloca_limit >= 0);

  unsigned HOST_WIDE_INT max_size;
  if (is_vla)
    max_size = warn_vla_limit;
  else
    max_size = warn_alloca_limit;

  // Check for the obviously bounded case.
  if (TREE_CODE (len) == INTEGER_CST)
    {
      if (tree_to_uhwi (len) > max_size)
	return alloca_type_and_limit (ALLOCA_BOUND_DEFINITELY_LARGE,
				      wi::to_wide (len));
      if (integer_zerop (len))
	{
	  const offset_int maxobjsize
	    = wi::to_offset (max_object_size ());
	  alloca_type result = (max_size < maxobjsize
				? ALLOCA_ARG_IS_ZERO : ALLOCA_OK);
	  return alloca_type_and_limit (result);
	}

      return alloca_type_and_limit (ALLOCA_OK);
    }

  // If we have a declared maximum size, use that.
  if (gimple_call_builtin_p (stmt, BUILT_IN_ALLOCA_WITH_ALIGN_AND_MAX))
    {
      tree arg = gimple_call_arg (stmt, 2);
      if (compare_tree_int (arg, max_size) <= 0)
	return alloca_type_and_limit (ALLOCA_OK);
      else
	{
	  const offset_int maxobjsize
	    = wi::to_offset (max_object_size ());
	  alloca_type result = (max_size < maxobjsize
				? ALLOCA_BOUND_MAYBE_LARGE : ALLOCA_OK);
	  return alloca_type_and_limit (result, wi::to_wide (arg));
	}
    }

  irange r;
  if (TREE_CODE (len) == SSA_NAME
      && ranger.path_range_on_stmt (r, len, stmt)
      && !r.range_for_type_p ())
    {
      // The invalid bits are anything outside of [0..MAX_SIZE].
      // If our range is outside of this, the bound may be large.
      irange invalid_range (size_type_node, 0, max_size, irange::INVERSE);
      if (r.intersect (invalid_range).empty_p ())
	return alloca_type_and_limit (ALLOCA_OK);
      return alloca_type_and_limit (ALLOCA_BOUND_MAYBE_LARGE);
    }

  /* When MAX_SIZE is greater than or equal to PTRDIFF_MAX treat
     allocations that aren't visibly constrained as OK, otherwise
     report them as (potentially) unbounded.  */
  const offset_int maxobjsize = tree_to_shwi (max_object_size ());
  alloca_type unbounded_result = (max_size < maxobjsize.to_uhwi ()
				  ? ALLOCA_UNBOUNDED : ALLOCA_OK);
  return alloca_type_and_limit (unbounded_result);
}

// Return TRUE if STMT is in a loop, otherwise return FALSE.

static bool
in_loop_p (gimple *stmt)
{
  basic_block bb = gimple_bb (stmt);
  return
    bb->loop_father && bb->loop_father->header != ENTRY_BLOCK_PTR_FOR_FN (cfun);
}

unsigned int
pass_walloca::execute (function *fun)
{
  basic_block bb;
  path_ranger ranger;

  if (dump_file && (dump_flags & TDF_DETAILS))
    ranger.exercise (dump_file);

  FOR_EACH_BB_FN (bb, fun)
    {
      for (gimple_stmt_iterator si = gsi_start_bb (bb); !gsi_end_p (si);
	   gsi_next (&si))
	{
	  gimple *stmt = gsi_stmt (si);
	  location_t loc = gimple_location (stmt);

	  if (!gimple_alloca_call_p (stmt))
	    continue;

	  const bool is_vla
	    = gimple_call_alloca_for_var_p (as_a <gcall *> (stmt));

	  // Strict mode whining for VLAs is handled by the front-end,
	  // so we can safely ignore this case.  Also, ignore VLAs if
	  // the user doesn't care about them.
	  if (is_vla)
	    {
	      if (warn_vla > 0 || warn_vla_limit < 0)
		continue;
	    }
	  else if (warn_alloca)
	    {
	      warning_at (loc, OPT_Walloca, G_("use of %<alloca%>"));
	      continue;
	    }
	  else if (warn_alloca_limit < 0)
	    continue;

	  struct alloca_type_and_limit t
	    = alloca_call_type (ranger, stmt, is_vla);

	  // Even if we think the alloca call is OK, make sure it's not in a
	  // loop, except for a VLA, since VLAs are guaranteed to be cleaned
	  // up when they go out of scope, including in a loop.
	  if (t.type == ALLOCA_OK && !is_vla && in_loop_p (stmt))
	    {
	      /* As in other instances, only diagnose this when the limit
		 is less than the maximum valid object size.  */
	      const offset_int maxobjsize
		= wi::to_offset (max_object_size ());
	      if ((unsigned HOST_WIDE_INT) warn_alloca_limit
		  < maxobjsize.to_uhwi ())
		t = alloca_type_and_limit (ALLOCA_IN_LOOP);
	    }

	  enum opt_code wcode
	    = is_vla ? OPT_Wvla_larger_than_ : OPT_Walloca_larger_than_;
	  char buff[WIDE_INT_MAX_PRECISION / 4 + 4];
	  switch (t.type)
	    {
	    case ALLOCA_OK:
	      break;
	    case ALLOCA_BOUND_MAYBE_LARGE:
	      if (warning_at (loc, wcode,
			      is_vla ? G_("argument to variable-length array "
					  "may be too large")
			      : G_("argument to %<alloca%> may be too large"))
		  && t.limit != 0)
		{
		  print_decu (t.limit, buff);
		  inform (loc, G_("limit is %wu bytes, but argument "
				  "may be as large as %s"),
			  is_vla ? warn_vla_limit : warn_alloca_limit, buff);
		}
	      break;
	    case ALLOCA_BOUND_DEFINITELY_LARGE:
	      if (warning_at (loc, wcode,
			      is_vla ? G_("argument to variable-length array "
					  "is too large")
			      : G_("argument to %<alloca%> is too large"))
		  && t.limit != 0)
		{
		  print_decu (t.limit, buff);
		  inform (loc, G_("limit is %wu bytes, but argument is %s"),
			  is_vla ? warn_vla_limit : warn_alloca_limit, buff);
		}
	      break;
	    case ALLOCA_UNBOUNDED:
	      warning_at (loc, wcode,
			  is_vla ? G_("unbounded use of variable-length array")
			  : G_("unbounded use of %<alloca%>"));
	      break;
	    case ALLOCA_IN_LOOP:
	      gcc_assert (!is_vla);
	      warning_at (loc, wcode, G_("use of %<alloca%> within a loop"));
	      break;
	    case ALLOCA_ARG_IS_ZERO:
	      warning_at (loc, wcode,
			  is_vla ? G_("argument to variable-length array "
				      "is zero")
			  : G_("argument to %<alloca%> is zero"));
	      break;
	    default:
	      gcc_unreachable ();
	    }
	}
    }
  return 0;
}

gimple_opt_pass *
make_pass_walloca (gcc::context *ctxt)
{
  return new pass_walloca (ctxt);
}
