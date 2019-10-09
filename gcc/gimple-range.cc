/* Code for GIMPLE range related routines.
   Copyright (C) 2019 Free Software Foundation, Inc.
   Contributed by Andrew MacLeod <amacleod@redhat.com>
   and Aldy Hernandez <aldyh@redhat.com>.

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
#include "insn-codes.h"
#include "rtl.h"
#include "tree.h"
#include "gimple.h"
#include "cfghooks.h"
#include "tree-pass.h"
#include "ssa.h"
#include "optabs-tree.h"
#include "gimple-pretty-print.h"
#include "diagnostic-core.h"
#include "flags.h"
#include "fold-const.h"
#include "stor-layout.h"
#include "calls.h"
#include "cfganal.h"
#include "gimple-fold.h"
#include "tree-eh.h"
#include "gimple-iterator.h"
#include "gimple-walk.h"
#include "tree-cfg.h"
#include "wide-int.h"
#include "gimple-range.h"

// This function looks for situations when walking the use/def chains
// may provide additonal contextual range information not exposed on
// this statement.  Like knowing the IMAGPART return value from a
// builtin function is a boolean result.

static void
gimple_range_adjustment (const gimple *s, value_range_base &res)
{
  switch (gimple_expr_code (s))
    {
    case IMAGPART_EXPR:
      {
	value_range_base r;
	tree name;
	tree type = TREE_TYPE (gimple_assign_lhs (s));

	name = TREE_OPERAND (gimple_assign_rhs1 (s), 0);
	if (TREE_CODE (name) == SSA_NAME)
	  {
	    gimple *def_stmt = SSA_NAME_DEF_STMT (name);
	    if (def_stmt && is_gimple_call (def_stmt)
		&& gimple_call_internal_p (def_stmt))
	      {
		switch (gimple_call_internal_fn (def_stmt))
		  {
		  case IFN_ADD_OVERFLOW:
		  case IFN_SUB_OVERFLOW:
		  case IFN_MUL_OVERFLOW:
		  case IFN_ATOMIC_COMPARE_EXCHANGE:
		    r.set_varying (boolean_type_node);
		    range_cast (r, type);
		    res.intersect (r);
		  default:
		    break;
		  }
	      }
	  }
	break;
      }

    default:
      break;
    }
}

// ------------------------------------------------------------------------

// This function will calculate the "constant" range on edge E from switch SW
// returning it in R, and return the switch statement itself.
// THis is currently not very efficent as the way we represent switches in
// GIMPLE does not map well to this calculation.

static gimple *
calc_single_range (value_range_base &r, gswitch *sw, edge e)
{
  unsigned x, lim;
  lim = gimple_switch_num_labels (sw);
  tree type = TREE_TYPE (gimple_switch_index (sw));

  // ADA and FORTRAN currently have cases where the index is 64 bits and the
  // case arguments are 32 bit, causing a trap when we create a case_range.
  // Until this is resolved (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=87798)
  // punt on these switches.  
  // furthermore, cfamily fails during a bootstrap due to a signed index and
  // unsigned cases.  so punting unless types_compatible_p () for now.
  tree case_type = TREE_TYPE (CASE_LOW (gimple_switch_label (sw, 1)));
  if (lim > 1 && !types_compatible_p (type, case_type))
    return NULL;

  if (e != gimple_switch_default_edge (cfun, sw))
    {
      r.set_undefined ();
      // Loop through all the switches edges, ignoring the default edge.
      // unioning the ranges together.
      for (x = 1; x < lim; x++)
	{
	  if (gimple_switch_edge (cfun, sw, x) != e)
	    continue;
	  tree low = CASE_LOW (gimple_switch_label (sw, x));
	  tree high = CASE_HIGH (gimple_switch_label (sw, x));
	  if (!high)
	    high = low;
	  value_range_base case_range (low, high);
	  r.union_ (case_range);
	}
    }
  else
    {
      r.set_varying (type);
      // Loop through all the switches edges, ignoring the default edge.
      // intersecting the ranges not covered by the case.
      for (x = 1; x < lim; x++)
	{
	  tree low = CASE_LOW (gimple_switch_label (sw, x));
	  tree high = CASE_HIGH (gimple_switch_label (sw, x));
	  if (!high)
	    high = low;
	  value_range_base case_range (VR_ANTI_RANGE, low, high);
	  r.intersect (case_range);
	}
    }
  return sw;
}


// If there is a range control statment at the end of block BB, return it.

gimple_stmt_iterator
gsi_outgoing_range_stmt (basic_block bb)
{
  gimple_stmt_iterator gsi = gsi_last_nondebug_bb (bb);
  if (!gsi_end_p (gsi))
    {
      gimple *s = gsi_stmt (gsi);
      if (is_a<gcond *> (s) || is_a<gswitch *> (s))
	return gsi;
    }
  return gsi_none ();
}


// If there is a range control statment at the end of block BB, return it.

gimple *
gimple_outgoing_range_stmt_p (basic_block bb)
{
  // This will return NULL if there is not a branch statement.
  return gsi_stmt (gsi_outgoing_range_stmt (bb));
}


// Calculate the range forced on on edge E by control flow, return it in R.
// Return the statment which defines the range, otherwise return NULL

gimple *
gimple_outgoing_edge_range_p (value_range_base &r, edge e)
{
  // Determine if there is an outgoing edge.
  gimple *s = gimple_outgoing_range_stmt_p (e->src);
  if (!s)
    return NULL;

  if (is_a<gcond *> (s))
    {
      if (e->flags & EDGE_TRUE_VALUE)
	r = value_range_base (boolean_true_node, boolean_true_node);
      else if (e->flags & EDGE_FALSE_VALUE)
	r = value_range_base (boolean_false_node, boolean_false_node);
      else
	gcc_unreachable ();
      return s;
    }

  gcc_checking_assert (is_a<gswitch *> (s));
  gswitch *sw = as_a<gswitch *> (s);
  tree type = TREE_TYPE (gimple_switch_index (sw));

  if (!value_range_base::supports_type_p (type))
    return NULL;

  return calc_single_range (r, sw, e);
}



// Fold this unary statement using R1 as operand1's range, returning the
// result in RES.  Return false if the operation fails.

bool
gimple_range_fold (const gimple *s, value_range_base &res,
		   const value_range_base &r1)
{
  gcc_checking_assert (gimple_range_handler (s));

  tree type = gimple_expr_type (s);;
  value_range_base r2 (type);
  // Single ssa operations require the LHS type as the second range.

  return gimple_range_fold (s, res, r1, r2);
}


// Fold this binary statement using R1 and R2 as the operands ranges,
// returning the result in RES.  Return false if the operation fails.

bool
gimple_range_fold (const gimple *s, value_range_base &res,
		   const value_range_base &r1,
		   const value_range_base &r2)
{
  gcc_checking_assert (gimple_range_handler (s));

  value_range_base adj_range;
  res = gimple_range_handler (s)->fold_range (gimple_expr_type (s), r1, r2);

  // If there are any gimple lookups, do those now.
  gimple_range_adjustment (s, res);
  return true;
}


// Return the first operand of this statement if it is a valid operand 
// supported by ranges, otherwise return NULL_TREE. 
// Special case is &(SSA_NAME expr), return the SSA_NAME instead of the ADDR
// expr.

tree
gimple_range_operand1 (const gimple *s)
{
  gcc_checking_assert (gimple_range_handler (s));

  switch (gimple_code (s))
    {
      case GIMPLE_COND:
        return gimple_cond_lhs (s);
      case GIMPLE_ASSIGN:
        {
	  tree expr = gimple_assign_rhs1 (s);
	  if (gimple_assign_rhs_code (s) == ADDR_EXPR)
	    {
	      // If the base address is an SSA_NAME, we return it here.
	      // This allows processing of the range of that name, while the
	      // rest of the expression is simply ignored.  The code in
	      // range_ops will see the ADDR_EXPR and do the right thing.
	      tree base = get_base_address (TREE_OPERAND (expr, 0));
	      if (base != NULL_TREE && TREE_CODE (base) == MEM_REF)
	        {
		  // If the base address is an SSA_NAME, return it. 
		  tree b = TREE_OPERAND (base, 0);
		  if (TREE_CODE (b) == SSA_NAME)
		    return b;
		}
	    }
	  return expr;
	}
      default:
        break;
    }
  return NULL;
}


// Return the second operand of statement S, otherwise return NULL_TREE.

tree
gimple_range_operand2 (const gimple *s)
{
  gcc_checking_assert (gimple_range_handler (s));

  switch (gimple_code (s))
    {
    case GIMPLE_COND:
      return gimple_cond_rhs (s);
    case GIMPLE_ASSIGN:
      if (gimple_num_ops (s) >= 3)
	return gimple_assign_rhs2 (s);
    default:
      break;
    }
  return NULL_TREE;
}



// Calculate what we can determine of the range of this unary statement's
// operand if the lhs of the expression has the range LHS_RANGE.  Return false
// if nothing can be determined.

bool
gimple_range_calc_op1 (const gimple *s, value_range_base &r,
		       const value_range_base &lhs_range)
{  
  value_range_base type_range;
  gcc_checking_assert (gimple_num_ops (s) < 3);
  // An empty range is viral, so return an empty range.
  
  tree type = TREE_TYPE (gimple_range_operand1 (s));
  if (lhs_range.undefined_p ())
    {
      r.set_undefined ();
      return true;
    }
  // Unary operations require the type of the first operand in the second range
  // position.
  type_range.set_varying (type);
  return gimple_range_handler (s)->op1_range (r, type, lhs_range, type_range);
}


// Calculate what we can determine of the range of this statement's first 
// operand if the lhs of the expression has the range LHS_RANGE and the second
// operand has the range OP2_RANGE.  Return false if nothing can be determined.

bool
gimple_range_calc_op1 (const gimple *s, value_range_base &r,
		       const value_range_base &lhs_range,
		       const value_range_base &op2_range)
{  
  // Unary operation are allowed to pass a range in for second operand
  // as there are often additional restrictions beyond the type which can
  // be imposed.  See operator_cast::op1_range.()
  tree type = TREE_TYPE (gimple_range_operand1 (s));
  // An empty range is viral, so return an empty range.
  if (op2_range.undefined_p () || lhs_range.undefined_p ())
    {
      r.set_undefined ();
      return true;
    }
  return gimple_range_handler (s)->op1_range (r, type, lhs_range, op2_range);
}


// Calculate what we can determine of the range of this statement's second
// operand if the lhs of the expression has the range LHS_RANGE and the first
// operand has the range OP1_RANGE.  Return false if nothing can be determined.

bool
gimple_range_calc_op2 (const gimple *s, value_range_base &r,
		       const value_range_base &lhs_range,
		       const value_range_base &op1_range)
{  
  tree type = TREE_TYPE (gimple_range_operand2 (s));
  // An empty range is viral, so return an empty range.
  if (op1_range.undefined_p () || lhs_range.undefined_p ())
    {
      r.set_undefined ();
      return true;
    }
  return gimple_range_handler (s)->op2_range (r, type, lhs_range, op1_range);
}
