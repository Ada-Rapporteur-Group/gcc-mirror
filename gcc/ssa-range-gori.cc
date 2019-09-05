/* SSA range GORI functions.
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
   Contributed by Andrew MacLeod <amacleod@redhat.com>.

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
#include "ssa.h"
#include "gimple-pretty-print.h"
#include "diagnostic-core.h"
#include "wide-int.h"
#include "grange.h"
#include "ssa-range-gori.h"
#include "fold-const.h"
#include "ssa-range.h"

// Construct a range_def_chain

range_def_chain::range_def_chain ()
{
  m_def_chain.create (0);
  m_def_chain.safe_grow_cleared (num_ssa_names);
  m_terminal.create (0);
  m_terminal.safe_grow_cleared (num_ssa_names);
}

// Destruct a range_def_chain

range_def_chain::~range_def_chain ()
{
  unsigned x;
  for (x = 0; x < m_def_chain.length (); ++x)
    if (m_def_chain[x])
      BITMAP_FREE (m_def_chain[x]);
  m_def_chain.release ();
  m_terminal.release ();
}

// Return true if NAME is in the def chain of DEF.  If BB is provided, only
// return true if the defining statement of DEF is in BB.

bool
range_def_chain::in_chain_p (tree name, tree def)
{
  gcc_checking_assert (valid_range_ssa_p (def));
  gcc_checking_assert (valid_range_ssa_p (name));

  // Get the defintion chain for DEF
  bitmap chain = get_def_chain (def);

  if (chain == NULL)
    return false;
  return bitmap_bit_p (chain, SSA_NAME_VERSION (name));
}

// If NAME has a definition chain, and the chain has a single import into
// the block, return the name of that import.

tree
range_def_chain::terminal_name (tree name)
{
  // Ensure the def chain has been calculated.
  get_def_chain (name);
  return m_terminal[SSA_NAME_VERSION (name)];
}

// Given up to 3 ssa names, return the common name or NULL_TREE.   NULL_TREE's
// passed in can be ignored, but all specified ssa-names must be the same name.

static inline tree
pick_import (tree ssa1, tree ssa2, tree ssa3)
{
  if (ssa1)
    {
      if (ssa2 && ssa1 != ssa2)
        return NULL_TREE;	// No match.
      // Either ssa2 is NULL, or it is the same as ssa1.
      if (!ssa3 || ssa1 == ssa3)
        return ssa1;	// ssa1 is the import.
      return NULL_TREE;
    }
  if (ssa2)
    {
      // If there is no ssa3 or ssa3 is the same as ssa2, thats the import.
      if (!ssa3 || ssa2 == ssa3)
        return ssa2;
      // They must both be different, so no import.
      return NULL_TREE;
    }
  return ssa3;
}

// Build def_chains for NAME if it is in BB.. copy the def chain into RESULT.
// Return the import for name, or NAME if it is an import.

tree
range_def_chain::build_def_chain (tree name, bitmap result, basic_block bb)
{
  bitmap b;
  gimple *def_stmt = SSA_NAME_DEF_STMT (name);
  // Add this operand into the result.
  bitmap_set_bit (result, SSA_NAME_VERSION (name));

  if (gimple_bb (def_stmt) == bb && !is_a<gphi *>(def_stmt))
    {
      // Get the def chain for the operand
      b = get_def_chain (name);
      // If there was one, copy it into result and retuirn the terminal name.
      if (b)
        {
	  bitmap_ior_into (result, b);
	  return m_terminal [SSA_NAME_VERSION (name)];
	}
      // If there is no def chain, this terminal is within the same BB.
    }
  return name;	// This is an import.
}

// Return TRUE if NAME has been processed for a def_chain.

inline bool
range_def_chain::has_def_chain (tree name)
{
  unsigned v = SSA_NAME_VERSION (name);
  if (v >= m_def_chain.length ())
    {
      m_def_chain.safe_grow_cleared (num_ssa_names + 1);
      m_terminal.safe_grow_cleared (num_ssa_names + 1);
    }
  return (m_def_chain[v] != NULL);
}

// Calculate the def chain for NAME and all of its dependent operands. Only
// using names in the same BB.  Return the bitmap of all names in the 
// m_def_chain.   This only works for supported range statements.

bitmap
range_def_chain::get_def_chain (tree name)
{
  tree ssa1, ssa2, ssa3;
  unsigned v = SSA_NAME_VERSION (name);

  // If it has already been processed, just return the cached value.
  if (has_def_chain (name))
    return m_def_chain[v];

  // No definition chain for default defs.
  if (SSA_NAME_IS_DEFAULT_DEF (name))
    return NULL;

  gimple *s = SSA_NAME_DEF_STMT (name);
  if (is_a<grange *> (s))
    { 
      grange *stmt = as_a<grange *> (s);
      ssa1 = valid_range_ssa_p (gimple_range_operand1 (stmt));
      ssa2 = valid_range_ssa_p (gimple_range_operand2 (stmt));
      ssa3 = NULL_TREE;
    }
  else if (is_a<gassign *> (s) && gimple_assign_rhs_code (s) == COND_EXPR)
    {
      gassign *st = as_a<gassign *> (s);
      ssa1 = valid_range_ssa_p (gimple_assign_rhs1 (st));
      ssa2 = valid_range_ssa_p (gimple_assign_rhs2 (st));
      ssa3 = valid_range_ssa_p (gimple_assign_rhs3 (st));
    }
  else
    return NULL;

  basic_block bb = gimple_bb (s);

  // Allocate a new bitmap and initialize it.
  m_def_chain[v] = BITMAP_ALLOC (NULL);

  // build_def_chain returns the terminal name. If we have more than one unique
  // terminal name, then this statement will have no terminal.
  bool has_term = true;
  m_terminal[v] = NULL_TREE;
  if (ssa1)
    {
      ssa1 = build_def_chain (ssa1, m_def_chain[v], bb);
      // if this chain has no terminal, root cannot either.
      if (!ssa1)
        has_term = false;
    }
  if (ssa2)
    {
      ssa2 = build_def_chain (ssa2, m_def_chain[v], bb);
      if (!ssa2)
        has_term = false;
    }
  if (ssa3)
    {
      ssa3 = build_def_chain (ssa3, m_def_chain[v], bb);
      if (!ssa3)
        has_term = false;
    }

  if (has_term)
    m_terminal[v] = pick_import (ssa1, ssa2, ssa3);
  else
    m_terminal[v] = NULL_TREE;
    
  // If we run into pathological cases where the defintion chains are huge
  // (I'm thinking fppp for instance.. huge basic block fully unrolled)
  // we might be able to limit this by deciding here that if there is no
  // import AND 2 or more ssa names, we change the def_chain back to be
  // just the ssa-names.  that should prevent  a_2 = b_6 + a_8 from creating
  // a pathological case yet allow us to still handle it when b_6 and a_8 are
  // derived from the same base name.
  // thoughts?
  return m_def_chain[v];
}


// Initialize a gori-map structure.

gori_map::gori_map ()
{
  m_outgoing.create (0);
  m_outgoing.safe_grow_cleared (last_basic_block_for_fn (cfun));
  m_incoming.create (0);
  m_incoming.safe_grow_cleared (last_basic_block_for_fn (cfun));

}

// Free any memory the GORI map allocated.

gori_map::~gori_map ()
{
  unsigned bb;
  for (bb = 0; bb < m_outgoing.length (); ++bb)
    if (m_outgoing[bb])
      BITMAP_FREE (m_outgoing[bb]);
  m_outgoing.release ();

  for (bb = 0; bb < m_incoming.length (); ++bb)
    if (m_incoming[bb])
      BITMAP_FREE (m_incoming[bb]);
  m_incoming.release ();

}

// Return the bitmap vector of all imports to BB. Calculate if necessary

bitmap
gori_map::imports (basic_block bb)
{
  if (!m_incoming[bb->index])
    calculate_gori (bb);
  return m_incoming[bb->index];
}

// Return true if NAME is an import to basic block BB

bool
gori_map::is_import_p (tree name, basic_block bb)
{
  return bitmap_bit_p (imports (bb), SSA_NAME_VERSION (name));
}

// Return the bitmap vector of all export from BB. Calculate if necessary

bitmap
gori_map::exports (basic_block bb)
{
  if (!m_outgoing[bb->index])
    calculate_gori (bb);
  return m_outgoing[bb->index];
}

// Return true if NAME is can have ranges generated for it from basic block BB.

bool
gori_map::is_export_p (tree name, basic_block bb)
{
  return bitmap_bit_p (exports (bb), SSA_NAME_VERSION (name));
}

// Return true if any element in the def chain of NAME is in the export list
// for BB.

bool
gori_map::def_chain_in_export_p (tree name, basic_block bb)
{
  bitmap a = exports (bb);
  bitmap b = get_def_chain (name);
  if (a && b)
    return bitmap_intersect_p (a, b);
  return false;
}

// If NAME is non-NULL and defined in block BB, calculate the def chain
// and add it to m_outgoing, and any imports to m_incoming.

void
gori_map::maybe_add_gori (tree name, basic_block bb)
{
  if (name)
    {
      bitmap r = get_def_chain (name);
      if (r)
        {
	  bitmap_copy (m_outgoing[bb->index], r);
	  tree im = terminal_name (name);
	  if (im)
	    bitmap_set_bit (m_incoming[bb->index], SSA_NAME_VERSION (im));
	}
      else
        {
	  // IF there is no def chain, and name originates outside this block
	  // then this name is also an import.
	  if (gimple_bb (SSA_NAME_DEF_STMT (name)) != bb)
	    bitmap_set_bit (m_incoming[bb->index], SSA_NAME_VERSION (name));
	}
      // Def chain doesn't include itself, and even if there isn't a def
      // chain, this name should be added to exports.
      bitmap_set_bit (m_outgoing[bb->index], SSA_NAME_VERSION (name));
    }
}

// Calculate all the required information for BB.

void
gori_map::calculate_gori (basic_block bb)
{
  tree name;
  gcc_assert (m_outgoing[bb->index] == NULL);
  m_outgoing[bb->index] = BITMAP_ALLOC (NULL);
  m_incoming[bb->index] = BITMAP_ALLOC (NULL);

  // If this block's last statement may generate range informaiton, 
  // go calculate it.
  gimple *s = gimple_outgoing_range_stmt_p (bb);
  if (!s)
    return;
  if (is_a<gcond *> (s))
    {
      gcond *gc = as_a<gcond *>(s);
      name = valid_range_ssa_p (gimple_cond_lhs (gc));
      maybe_add_gori (name, gimple_bb (s));

      name = valid_range_ssa_p (gimple_cond_rhs (gc));
      maybe_add_gori (name, gimple_bb (s));
    }
  else
    {
      gswitch *gs = as_a<gswitch *>(s);
      name = valid_range_ssa_p (gimple_switch_index (gs));
      maybe_add_gori (name, gimple_bb (s));
    }
}

// Dump the table information for BB to file F.

void
gori_map::dump(FILE *f, basic_block bb)
{
  tree t;
  bool header = false;
  const char *header_string = "bb%-4d ";
  const char *header2 = "       ";
  bool printed_something = false;;
  unsigned x, y;
  bitmap_iterator bi;

  if (!m_outgoing[bb->index])
    {
      fprintf (f, "bb%d was not processed.\n", bb->index);
      return;
    }

  // Dump the def chain for each SSA_NAME defined in BB.
  for (x = 1; x < num_ssa_names; x++)
    {
      tree name = ssa_name (x);
      if (!name)
	continue;
      gimple *stmt = SSA_NAME_DEF_STMT (name);
      bitmap chain = (has_def_chain (name) ? get_def_chain (name) : NULL);
      if (stmt && gimple_bb (stmt) == bb && chain && !bitmap_empty_p (chain))
        {
	  fprintf (f, header_string, bb->index);
	  header_string = header2;
	  header = true;
	  print_generic_expr (f, name, TDF_SLIM);
	  if ((t = terminal_name (name)))
	    {
	      fprintf (f, "  : (terminal ");
	      print_generic_expr (f, t, TDF_SLIM);
	      fprintf (f, ")");
	    }
	  fprintf (f, " : ");
	  EXECUTE_IF_SET_IN_BITMAP (chain, 0, y, bi)
	    {
	      print_generic_expr (f, ssa_name (y), TDF_SLIM);
	      fprintf (f, "  ");
	    }
	  fprintf (f, "\n");
	}
    }

  printed_something |= header;
  // Now dump the incoming vector.
  header = false;
  EXECUTE_IF_SET_IN_BITMAP (m_incoming[bb->index], 0, y, bi)
    {
      if (!header)
        {
	  fprintf (f, header_string, bb->index);
	  fprintf (f, "imports: ");
	  header_string = header2;
	  header = true;
	}
      print_generic_expr (f, ssa_name (y), TDF_SLIM);
      fprintf (f, "  ");
    }

  if (header)
    fputc ('\n', f);

  // Now dump the export vector.
  printed_something |= header;
  header = false;
  EXECUTE_IF_SET_IN_BITMAP (m_outgoing[bb->index], 0, y, bi)
    {
      if (!header)
        {
	  fprintf (f, header_string, bb->index);
	  fprintf (f, "exports: ");
	  header_string = header2;
	  header = true;
	}
      print_generic_expr (f, ssa_name (y), TDF_SLIM);
      fprintf (f, "  ");
    }
  if (header)
    fputc ('\n', f);

  printed_something |= header;
  if (printed_something)
    fprintf (f, "\n");
}

// Dump the entire GORI map structure to file F.
//
void
gori_map::dump(FILE *f)
{
  basic_block bb;
  FOR_EACH_BB_FN (bb, cfun)
    {
      dump (f, bb);
      fprintf (f, "\n");
    }
}

// Same but perform substitution of NAME with RANGE_OF_NAME if expr
// happens to match it.

static irange
get_tree_range (tree expr, tree name, irange *range_of_name)
{
  static stmt_ranger sr;
  if (expr != name || !range_of_name)
    {
      irange r;
      gcc_assert (sr.range_of_expr (r, expr));
      return r;
    }

  return *range_of_name;
}

// Calculate the range for NAME if the lhs of statement S has the range LHS.
// If present, NAME_RANGE is any known range for NAME coming into this stmt.
// Return the result in R. Return false if no range can be calculated.

static bool
compute_operand_range_on_stmt (irange &r, grange *s, const irange &lhs,
			       tree name, irange *name_range)
{
  irange op1_range, op2_range;

  tree op1 = gimple_range_operand1 (s);
  tree op2 = gimple_range_operand2 (s);

  // Operand 1 is the name being looked for, evaluate it.
  if (op1 == name)
    { 
      if (!op2)
	{
	  // The second parameter to a unary operation is the range for the type
	  // of operand1, but if it can be reduced further, the results will
	  // be better.  Start with what we know of the range of OP1.
	  op1_range = get_tree_range (op1, name, name_range);
	  return gimple_range_calc_op1 (s, r, lhs, op1_range);
	}
      // If we need the second operand, get a value and evaluate.
      op2_range = get_tree_range (op2, name, name_range);
      if (gimple_range_calc_op1 (s, r, lhs, op2_range))
	{
	  // If op1 also has a range, intersect the 2 ranges.
	  if (name_range)
	    r.intersect (*name_range);
	  return true;
	}
      return false;
    }

  if (op2 == name)
    {
      op1_range = get_tree_range (op1, name, name_range);
      if (gimple_range_calc_op2 (s, r, lhs, op1_range))
	{
	  // If op2 also has a range, intersect the 2 ranges.
	  if (name_range)
	    r.intersect (*name_range);
	  return true;
	}
    }
  return false;
}


// External entry point to calculate the range of NAME on statement S assuming
// the lhs's range is LHS.  Return TRUE and the result in R if it is possible
// to calculate, otherwise return FALSE.
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
compute_operand_range_on_stmt (irange &r, gimple *s, const irange &lhs,
			       tree name, irange *name_range)
{
  if (is_a<grange *> (s))
    return compute_operand_range_on_stmt (r, as_a<grange *> (s),  lhs, name,
					  name_range);
  if (is_a<gswitch *> (s))
    {
      if (gimple_switch_index (as_a<gswitch *>(s)) == name)
        {
	  r = get_tree_range (name, name, name_range);
	  r.intersect (lhs);
	  return true;
	}
    }
  return false;
}

// Construct a gori_compute object.

gori_compute::gori_compute ()
{
  // Create a boolean_type true and false range.
  m_bool_zero = irange (boolean_false_node, boolean_false_node);
  m_bool_one = irange (boolean_true_node, boolean_true_node);
}

// Destruct a gori_compute_object

gori_compute::~gori_compute ()
{
}

// Given the statement S, return an evaluation in R for NAME
// when the lhs evaluates to LHS.  Returning false means the name being
// looked for was not resolvable. 
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_operand_range (irange &r, gimple *s, const irange &lhs,
				     tree name, irange *name_range)
{
  if (is_a<grange *> (s))
    return compute_operand_range_op (r, as_a<grange *> (s), lhs, name,
				     name_range);
  if (is_a<gswitch *> (s))
    return compute_operand_range_switch (r, as_a<gswitch *> (s), lhs, name,
					 name_range);
  return false;
}
    
// Given the switch S, return an evaluation in R for NAME
// when the lhs evaluates to LHS.  Returning false means the name being
// looked for was not resolvable. 
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_operand_range_switch (irange &r, gswitch *s,
					    const irange &lhs, tree name,
					    irange *name_range)
{
  tree op1 = gimple_switch_index (s);

  // If name matches, the range is simply the range from the edge.
  // Empty ranges are viral as they are on a path which isn't executable.
  if (op1 == name || lhs.undefined_p ())
    {
      r = lhs;
      // If this is also the terminal
      if (name && name_range)
        r.intersect (*name_range);
      return true;
    }

  // If op1 is in the defintion chain, pass lhs back.
  if (valid_range_ssa_p (op1) && in_chain_p (name, op1))
    return compute_operand_range (r, SSA_NAME_DEF_STMT (op1), lhs, name,
				  name_range);

  return false;
}

// Return TRUE if GS is a logical && or || expression.

static inline bool
is_gimple_logical_p (const gimple *gs)
{
  /* Look for boolean and/or condition.  */
  if (gimple_code (gs) == GIMPLE_ASSIGN)
    switch (gimple_expr_code (gs))
      {
	case TRUTH_AND_EXPR:
	case TRUTH_OR_EXPR:
	  return true;

	case BIT_AND_EXPR:
	case BIT_IOR_EXPR:
	  // Bitwise operations on single bits are logical too.
	  if (types_compatible_p (TREE_TYPE (gimple_assign_rhs1 (gs)),
				  boolean_type_node))
	    return true;
	  break;

	default:
	  break;
      }
  return false;
}

// Given the range_op S, return an evaluation in R for NAME
// when the lhs evaluates to LHS.  Returning false means the name being
// looked for was not resolvable. 
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_operand_range_op (irange &r, grange *stmt, 
					const irange &lhs, tree name,
					irange *name_range)
{
  tree op1, op2;
  bool op1_in_chain, op2_in_chain;

  // Empty ranges are viral as they are on a path which isn't executable.
  if (lhs.undefined_p ())
    {
      r.set_undefined ();
      return true;
    }

  op1 = valid_range_ssa_p (gimple_range_operand1 (stmt));
  op2 = valid_range_ssa_p (gimple_range_operand2 (stmt));

  // The base ranger handles NAME on this statement.
  if (op1 == name || op2 == name)
    return compute_operand_range_on_stmt (r, stmt, lhs, name, name_range);

  // Check for logical combination cases which require developing ranges 
  // and combining the results based on the operation. 
  if (is_gimple_logical_p (stmt))
    return compute_logical_operands (r, stmt, lhs, name, name_range);

  // Reaching this point means NAME is not in this stmt, but one of the
  // names in it ought to be derived from it. 
  op1_in_chain = op1 && in_chain_p (name, op1);
  op2_in_chain = op2 && in_chain_p (name, op2);

  if (op2_in_chain)
    { 
      if (op1_in_chain)
	return compute_operand1_and_operand2_range (r, stmt, lhs, name,
						    name_range);
      else
	return compute_operand2_range (r, stmt, lhs, name, name_range);
    }
  else
    if (op1_in_chain)
      return compute_operand1_range (r, stmt, lhs, name, name_range);

  // If neither operand is derived, then this stmt tells us nothing.
  return false;
}

// Evaluate a binary logical expression by combining the true and false
// ranges for each of the operands based on the result value in the LHS. 

bool
gori_compute::logical_combine (irange &r, enum tree_code code,
			       const irange &lhs,
			       const irange &op1_true, const irange &op1_false,
			       const irange &op2_true, const irange &op2_false)
{
  // This is not a simple fold of a logical expression, rather it determines
  // ranges which flow through the logical expression.
  // Assuming x_8 is an unsigned char, and relational statements:
  //	      b_1 = x_8 < 20
  //	      b_2 = x_8 > 5
  // consider the logical expression and branch:
  //          c_2 = b_1 && b_2
  //          if (c_2)
  // To determine the range of x_8 on either edge of the branch,
  // one must first determine what the range of x_8 is when the boolean
  // values of b_1 and b_2 are both true and false.
  //    b_1 TRUE      x_8 = [0, 19]
  //    b_1 FALSE     x_8 = [20, 255]
  //    b_2 TRUE      x_8 = [6, 255]
  //    b_2 FALSE     x_8 = [0,5]. 
  //
  // These ranges are then combined based on the expected outcome of the branch
  // The range on the TRUE side of the branch must satisfy 
  //     b_1 == true && b_2 == true
  // in terms of x_8, that means both x_8 == [0, 19] and x_8 = [6, 255]
  // must be true.  The range of x_8 on the true side must be the intersection
  // of both ranges since both must be true.  Thus the range of x_8
  // on the true side is [6, 19]
  // 
  // To determine the ranges on the FALSE side, all 3 combinations of
  // failing ranges must be considered, and combined as any of them can cause
  // the false result.
  
  // If the LHS can be TRUE OR FALSE, then evaluate both a TRUE and FALSE
  // results and combine them.  If we fell back to VARYING any range
  // restrictions that have been discovered up to this point would be lost.  */
  if (!lhs.singleton_p ())
    {
      irange r1;
      if (logical_combine (r1, code, m_bool_zero, op1_true, op1_false, op2_true,
			   op2_false) &&
	  logical_combine (r, code, m_bool_one, op1_true, op1_false, op2_true,
			   op2_false))
	{
	  r.union_ (r1);
	  return true;
	}
      return false;

    }

  switch (code)
    {
      //  A logical AND combines ranges from 2 boolean conditions.
      //       c_2 = b_1 && b_2
      case TRUTH_AND_EXPR:
      case BIT_AND_EXPR:
        if (!lhs.zero_p ())
	  // The TRUE side is the intersection of the the 2 true ranges.
	  r = range_intersect (op1_true, op2_true);
	else
	  {
	    // The FALSE side is the union of the other 3 cases. 
	    irange ff = range_intersect (op1_false, op2_false);
	    irange tf = range_intersect (op1_true, op2_false);
	    irange ft = range_intersect (op1_false, op2_true);
	    r = range_union (ff, tf);
	    r.union_ (ft);
	  }
        break;

      //  A logical OR combines ranges from 2 boolean conditons.
      // 	c_2 = b_1 || b_2
      case TRUTH_OR_EXPR:
      case BIT_IOR_EXPR:
        if (lhs.zero_p ())
	  // An OR operation will only take the FALSE path if both operands
	  // are false. so [20, 255] intersect [0, 5] is the 
	  // union: [0,5][20,255].  */
	  r = range_intersect (op1_false, op2_false);
	else
	  {
	    // The TRUE side of an OR operation will be the union of the other
	    // three combinations.
	    irange tt = range_intersect (op1_true, op2_true);
	    irange tf = range_intersect (op1_true, op2_false);
	    irange ft = range_intersect (op1_false, op2_true);
	    r = range_union (tt, tf);
	    r.union_ (ft);
	  }
	break;

      default:
        gcc_unreachable ();
    }

  return true;
}

// Given a logical STMT, calculate true and false for each potential path 
// using NAME and resolve the outcome based on the logical operator.  
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_logical_operands (irange &r, grange *s, 
				        const irange &lhs, tree name,
					irange *name_range)
{
  irange op1_range, op2_range;
  tree op1, op2;
  bool op1_in_chain, op2_in_chain;
  bool ret = true;
  const unsigned depth_limit = 6;	// Max depth of logical recursion.
  static unsigned depth = 0;		// Current depth of recursion.

  irange op1_true, op1_false, op2_true, op2_false;

  // Reaching this point means NAME is not in this stmt, but one of the
  // names in it ought to be derived from it.  */
  op1 = gimple_range_operand1 (s);
  op2 = gimple_range_operand2 (s);
  gcc_checking_assert (op1 != name && op2 != name);

  op1_in_chain = valid_range_ssa_p (op1) && in_chain_p (name, op1);
  op2_in_chain = valid_range_ssa_p (op2) && in_chain_p (name, op2);

  /* If neither operand is derived, then this stmt tells us nothing. */
  if (!op1_in_chain && !op2_in_chain)
    return false;

  // Long chains of nested logical expressions rarely produce good ranges
  // but can take exponential times to compute since we are recursively
  // evaluating them for the true and false result.  If the depth is too great 
  // simply terminate the calculation.  See gcc testcase rvrp-logic-1.c.
  if (depth > depth_limit)
    {
      r.set_varying (TREE_TYPE (name));
      return true;
    }
  depth++;

  /* The false path is not always a simple inversion of the true side.
     Calulate ranges for true and false on both sides. */
  if (op1_in_chain)
    {
      ret = compute_operand_range (op1_true, SSA_NAME_DEF_STMT (op1), 
				   m_bool_one, name, name_range);
      ret &= compute_operand_range (op1_false, SSA_NAME_DEF_STMT (op1),
				    m_bool_zero, name, name_range);
    }
  else
    {
      // Otherwise just get the value for name in operand 1 position
      op1_true = get_tree_range (name, name, name_range);
      op1_false = op1_true;
    }

  /* If operand1 evaluated OK, move on to operand 2.  */
  if (ret)
    {
      if (op2_in_chain)
	{
	  ret &= compute_operand_range (op2_true, SSA_NAME_DEF_STMT (op2),
					m_bool_one, name, name_range);
	  ret &= compute_operand_range (op2_false, SSA_NAME_DEF_STMT (op2),
					m_bool_zero, name, name_range);
	}
      else
	{
	  // Otherwise just get the value for name in operand 2 position
	  op2_true = get_tree_range (name, name, name_range);
	  op2_false = op2_true; 
	}
    }
  if (!ret || !logical_combine (r, gimple_expr_code (s), lhs, op1_true,
				op1_false, op2_true, op2_false))
    r.set_varying (TREE_TYPE (name));

  depth--;
  return true;
}


// Calculate a range for NAME from the operand 1 position of S assuming the 
// result of the statement is LHS.  Return the range in R, or false if no
// range could be calculated.
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_operand1_range (irange &r, grange *s, 
				      const irange &lhs, tree name, 
				      irange *name_range)
{
  irange op1_range, op2_range;
  tree op1 = gimple_range_operand1 (s);
  tree op2 = gimple_range_operand2 (s);

  // Determine a known range for operand1 ().
  op1_range = get_tree_range (op1, name, name_range);

  // Now calcuated the operand and put that result in r.
  if (!op2)
    {
      // we pass op1_range to the unary operation. Nomally it's a hidden
      // range_for_type parameter, but sometimes having the actual range
      // can result in better information.
      if (!gimple_range_calc_op1 (s, r, lhs, op1_range))
	return false;
    }
  else
    {
      op2_range = get_tree_range (op2, name, name_range);
      if (!gimple_range_calc_op1 (s, r, lhs, op2_range))
	return false;
    }

  // Intersect the calculated result with the known result.
  op1_range.intersect (r);

  // Then feed this range back as the LHS of the defining statement.
  return compute_operand_range (r, SSA_NAME_DEF_STMT (op1), op1_range, name,
				name_range);
}


// Calculate a range for NAME from the operand 2 position of S assuming the 
// result of the statement is LHS.  Return the range in R, or false if no
// range could be calculated.
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_operand2_range (irange &r, grange *s,
				      const irange &lhs, tree name,
				      irange *name_range)
{
  irange op1_range, op2_range;
  tree op1 = gimple_range_operand1 (s);
  tree op2 = gimple_range_operand2 (s);

  // Get a range for op1.
  op1_range = get_tree_range (op1, name, name_range);

  // calculate the range for op2 based on lhs and op1.
  if (!gimple_range_calc_op2 (s, op2_range, lhs, op1_range))
    return false;

  // Also pick up what is known about op2's range at this point
  r = get_tree_range (op2, name, name_range);

  // And intersect it with the calculated result.
  op2_range.intersect (r);

  // Then feed this range back as the LHS of the defining statement.
  return compute_operand_range (r, SSA_NAME_DEF_STMT (op2), op2_range, name,
				name_range);
}

// Calculate a range for NAME from both operand positions of S assuming the 
// result of the statement is LHS.  Return the range in R, or false if no
// range could be calculated.
// If present, NAME_RANGE is any known range for NAME coming into S.

bool
gori_compute::compute_operand1_and_operand2_range (irange &r, grange *s,
						   const irange &lhs, tree name,
						   irange *name_range)
{
  irange op_range;

  // Calculate a good a range for op2. Since op1 == op2, this will have
  // already included whatever the actual range of name is.
  if (!compute_operand2_range (op_range, s, lhs, name, name_range))
    return false;

  // Now get the range thru op1... 
  if (!compute_operand1_range (r, s, lhs, name, name_range))
    return false;

  // Whichever range is the most permissive is the one we need to use. (?)
  // OR is that true?  Maybe this should be intersection?
  r.union_ (op_range);
  return true;
}
 
bool
gori_compute::has_edge_range_p (edge e, tree name)
{
  return (is_export_p (name, e->src) || def_chain_in_export_p (name, e->src));
}


// If the src block of edge E defines an outgoing range for a name that is
// is in the def_chain for NAME, get the outgoing range for that ssa_name
// and re-evaluate NAME using this value. If NAME_RANGE is supplied (normally
// the current value of NAME), intersect this with the edge range to produce 
// and accurate outgoing range on edge E for NAME. Return the results in R.
// Return false if nothing can be re-evaluated, or if NAME is actually exported
// and doesnt need redefining.

#include "ssa-range.h"

bool
gori_compute::reevaluate_definition (irange &r, tree name, edge e,
				     irange *name_range)
{
  basic_block bb = e->src;
  gimple *def_stmt;
  ssa_op_iter iter;
  use_operand_p use_p;

  // Ensure there is no outgoing range for NAME.
  gcc_checking_assert (!is_export_p (name, bb));

  // If nothing in the def chain is exported, there is no evaluation.
  if (!def_chain_in_export_p (name, bb))
    return false;

  def_stmt = SSA_NAME_DEF_STMT (name);
  gcc_checking_assert (def_stmt);

  // We know its possible to evaluate NAME from SOMETHING in its defintion.
  FOR_EACH_SSA_USE_OPERAND (use_p, def_stmt, iter, SSA_OP_USE)
    {
      tree use = valid_range_ssa_p (USE_FROM_PTR (use_p));
      if (use)
        {
	  irange use_range;
	  if (is_export_p (use, bb))
	    {
	      if (!outgoing_edge_range_p (use_range, e, use))
	        continue;
	    }
	  // Try reevaluating USE. we have no range on entry for USE.
	  else if (!reevaluate_definition (use_range, use, e, NULL))
	    continue;
	  // Invoke basic range calculator for the statement so we dont
	  // get any dynamic calls to range_of_expr which could cause another
	  // iterative evaluation to fill a cache.
	  ssa_ranger eval;
	  gcc_assert (eval.range_of_stmt_with_range (r, def_stmt, use,
						     use_range));
	  // If this is the root def and it has a range, combine them.
	  if (name_range)
	    r.intersect (*name_range);
	  return true;
        }
    }
  return false;
}

// Calculate a range on edge E and return it in R.  Try to evaluate a range
// for NAME on this edge.  Return FALSE if this is either not a control edge
// or NAME is not defined by this edge.

bool
gori_compute::outgoing_edge_range_p (irange &r, edge e, tree name,
				     irange *name_range)
{
  irange lhs;

  gcc_checking_assert (valid_range_ssa_p (name));
  // Determine if there is an outgoing edge.
  gimple *s = gimple_outgoing_edge_range_p (lhs, e);
  if (!s)
    return false;

  // If NAME can be calculated on the edge, use that.
  if (is_export_p (name, e->src))
    return compute_operand_range (r, s, lhs, name, name_range);
  
  // Otherwise see if NAME is derived from something that can be calculated.
  // This performs no dynamic lookups whatsover, so it is low cost.
  return reevaluate_definition (r, name, e, name_range);
}

// Calculate a range for NAME given an import range of IMPORT_RANGE and
// return it in r.  Return true if successful.

bool
gori_compute::range_from_import (irange &r, tree name, irange &import_range)
{
  irange r1, r2;
  bool res = true;
  tree import = terminal_name (name);

  gcc_checking_assert
    (import
     && (import_range.undefined_p ()
	 || useless_type_conversion_p (TREE_TYPE (import),
				       import_range.type ())));

  // Only handling range_ops until we find a cond-expr that matters.
  // We process this specially so we can handle self-referencing chains. ie:
  //   b_3 = b_1 + 10
  //   b_4 = b_3 + b_1  // b_4 = b_1 * 2 + 10 really
  //   if (b_4 < 20)
  //
  // import b_1 = [0,0]
  // we want to make sure b_4 evaluates both b_3 and b_1 with this import value
  // Due to the nature of def chains, there can only be one import in the chain.
  // its possible 2 different chains occur in one stmt, ie:
  // if (b_4 < d_6), but there is no DEF for this stmt, so it can't happen.
  // f_5 = b_4 + d_6 would have no import since there are 2 symbolics.
  
  grange *s = dyn_cast<grange *> (SSA_NAME_DEF_STMT (name));
  if (!s)
    return false;

  tree op1 = gimple_range_operand1 (s);
  tree op2 = gimple_range_operand2 (s);

  // Evaluate op1
  if (valid_range_ssa_p (op1))
    {
      if (op1 == import)
	r1 = import_range;
      else
	res = range_from_import (r1, op1, import_range);
    }
  else
    r1 = get_tree_range (op1, NULL_TREE, NULL);

  if (!res)
    return false;
  if (!op2)
    return gimple_range_fold (s, r, r1);

  // Now evaluate op2.
  if (valid_range_ssa_p (op2))
    {
      if (op2 == import)
	r2 = import_range;
      else
	res = range_from_import (r2, op2, import_range);
    }
  else
    r2 = get_tree_range (op2, NULL_TREE, NULL);

  if (res)
    return gimple_range_fold (s, r, r1, r2);

  return false;
}

