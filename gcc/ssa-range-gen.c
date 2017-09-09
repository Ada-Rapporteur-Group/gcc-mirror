/* On-demand ssa range generator.
   Copyright (C) 2017 Free Software Foundation, Inc.
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
#include "ssa-range-gen.h"
#include "ssa-range-stmt.h"
#include "domwalk.h"

//#define trace_output dump_file
#define trace_output ((FILE *)0)

//#define trace_path  dump_file
#define trace_path  ((FILE *)0)


bool
ranger::combine_range (range_stmt& stmt, irange& r, tree name,
		       const irange& lhs, bool op1_in_chain, bool op2_in_chain)
{
  tree op1, op2;
  irange r1, r2;
  irange op1_range, op2_range;

  irange op1_true, op1_false, op2_true, op2_false;

  /* Look for boolean and/or condition.  */
  switch (stmt.get_code ())
    {
      case TRUTH_AND_EXPR:
      case TRUTH_OR_EXPR:
        break;

      case BIT_AND_EXPR:
      case BIT_IOR_EXPR:
        if (!types_compatible_p (TREE_TYPE (stmt.operand1 ()),
				 boolean_type_node))
	  return false;
	break;

      default:
        return false;
    }


  if (trace_output)
    {
      fprintf (dump_file, "\nIn Combine_range for ");
      print_gimple_stmt (dump_file, stmt.get_gimple (), 0 ,0);
    }
  /* If the LHS can be TRUE OR FALSE, then we cant really tell anything.  */
  if (!wi::eq_p (lhs.lower_bound(), lhs.upper_bound()))
    {
      r.set_range_for_type (TREE_TYPE (name));
      if (trace_output)
	fprintf (dump_file, " : LHS can be true or false, know nothing.\n");
      return true;
    }

  op1 = stmt.operand1 ();
  op2 = stmt.operand2 ();

  irange bool_zero (boolean_type_node, 0, 0);
  irange bool_one (boolean_type_node, 1, 1);

  /* The false path is not always a simple inversion of the true side.
     Calulate ranges for true and false on both sides. */

  if (op1_in_chain)
    {
      get_range_from_stmt (SSA_NAME_DEF_STMT (op1), op1_true, name, bool_one);
      get_range_from_stmt (SSA_NAME_DEF_STMT (op1), op1_false, name, bool_zero);
    }
  else
    {
      get_operand_range (op1_true, TREE_TYPE (name));
      get_operand_range (op1_false, TREE_TYPE (name));
    }

  if (op2_in_chain)
    {
      get_range_from_stmt (SSA_NAME_DEF_STMT (op2), op2_true, name, bool_one);
      get_range_from_stmt (SSA_NAME_DEF_STMT (op2), op2_false, name, bool_zero);
    }
  else
    {
      get_operand_range (op2_true, TREE_TYPE (name));
      get_operand_range (op2_false, TREE_TYPE (name));
    }

  if (trace_output)
    {
      fprintf (dump_file, "  combining following 4 ranges:\n");
      fprintf (dump_file, "op1_true : ");
      op1_true.dump (dump_file);
      fprintf (dump_file, "op1_false : ");
      op1_false.dump (dump_file);
      fprintf (dump_file, "op2_true : ");
      op2_true.dump (dump_file);
      fprintf (dump_file, "op2_false : ");
      op2_false.dump (dump_file);
    }
  /* Now combine based on the result.  */
  switch (stmt.get_code ())
    {

      /* A logical AND of two ranges is executed when we are walking forward
	 with ranges that have been determined.   x_8 is an unsigned char.
	       b_1 = x_8 < 20
	       b_2 = x_8 > 5
	       c_2 = b_1 && b_2
	 if we are looking for the range of x_8, the ranges on each side 
	 will be:   b_1 carries x_8 = [0, 19],   b_2 carries [6, 255]
	 the result of the AND is the intersection of the 2 ranges, [6, 255]. */
      case TRUTH_AND_EXPR:
      case BIT_AND_EXPR:
        if (lhs != bool_zero)
	  r = irange_intersect (op1_true, op2_true);
	else
	  {
	    irange ff = irange_intersect (op1_false, op2_false);
	    irange tf = irange_intersect (op1_true, op2_false);
	    irange ft = irange_intersect (op1_false, op2_true);
	    r = irange_union (ff, tf);
	    r.union_ (ft);
	  }
        break;

      /* A logical OR of two ranges is executed when we are walking forward with
	 ranges that have been determined.   x_8 is an unsigned char.
	       b_1 = x_8 > 20
	       b_2 = x_8 < 5
	       c_2 = b_1 || b_2
	 if we are looking for the range of x_8, the ranges on each side
	 will be:   b_1 carries x_8 = [21, 255],   b_2 carries [0, 4]
	 the result of the OR is the union_ of the 2 ranges, [0,4][21,255].  */
      case TRUTH_OR_EXPR:
      case BIT_IOR_EXPR:
        if (lhs == bool_zero)
	  r = irange_intersect (op1_false, op2_false);
	else
	  {
	    irange tt = irange_intersect (op1_true, op2_true);
	    irange tf = irange_intersect (op1_true, op2_false);
	    irange ft = irange_intersect (op1_false, op2_true);
	    r = irange_union (tt, tf);
	    r.union_ (ft);
	  }
	break;

      default:
        gcc_unreachable ();
    }

  if (trace_output)
    {
      fprintf (dump_file, "result range is ");
      r.dump (dump_file);
    }
  return true;
}


bool
ranger::get_operand_range (irange& r, tree op)
{
  /* This check allows unary operations to be handled without having to 
     make an explicit check for the existence of a second operand.  */
  if (!op)
    return false;

  if (TREE_CODE (op) == INTEGER_CST)
    {
      r.set_range (TREE_TYPE (op), op, op);
      return true;
    }
  else
    if (TREE_CODE (op) == SSA_NAME)
      {
	/* Eventually we may go look for an on-demand range... */
	/* But at least should look for what we currently know. */
	r.set_range_for_type (TREE_TYPE (op));
	return true;
      }

  /* Unary expressions often set the type for the operand, get that range.  */
  if (TYPE_P (op))
    r.set_range_for_type (op);
  else
    r.set_range_for_type (TREE_TYPE (op));
  return true;
}

/* Given the expression in STMT, return an evaluation in R for NAME.
   Returning false means the name being looked for is NOT resolvable, and
   can be removed from the GORI map to qavoid future searches.  */
bool
ranger::get_range (range_stmt& stmt, irange& r, tree name,
			     const irange& lhs)
{
  range_stmt op_stmt;
  irange op1_range, op2_range;
  tree op1, op2;
  bool op1_in_chain, op2_in_chain;

  op1 = stmt.operand1 ();
  op2 = stmt.operand2 ();

  if (op1 == name)
    { 
      if (get_operand_range (op2_range, op2))
	return stmt.op1_irange (r, lhs, op2_range, trace_output);
      else
        return false;
    }

  if (op2 == name)
    {
      if (get_operand_range (op1_range, op1))
	return stmt.op2_irange (r, lhs, op1_range, trace_output);
      else
        return false;
    }

  /* Reaching this point means NAME is not in this stmt, but one of the
     names in it ought to be derived from it.  */
  op1_in_chain = def_chain.in_chain_p (op1, name);
  op2_in_chain = def_chain.in_chain_p (op2, name);

  /* If neither operand is derived, then this stmt tells us nothing. */
  if (!op1_in_chain && !op2_in_chain)
    return false;
  
  /* Check for boolean cases which require developing ranges and combining.  */
  if (combine_range (stmt, r, name, lhs, op1_in_chain, op2_in_chain))
    return true;

  /* Don't look thru expressions with more than one in_chain argument.  */
  if (op1_in_chain && op2_in_chain)
    return false;

  if (op1_in_chain)
    {
      get_operand_range (op2_range, op2);
      stmt.op1_irange (op1_range, lhs, op2_range, trace_output);
      return get_range_from_stmt (SSA_NAME_DEF_STMT (op1), r, name, op1_range);
    }

  get_operand_range (op1_range, op1);
  stmt.op2_irange (op2_range, lhs, op1_range, trace_output);
  return get_range_from_stmt (SSA_NAME_DEF_STMT (op2), r, name, op2_range);
}
 
/* Given the expression in STMT, return an evaluation in R for NAME. */
bool
ranger::get_range_from_stmt (gimple *stmt, irange& r, tree name,
			     const irange& lhs)
{
  range_stmt rn;
  rn = stmt;

  /* If it isnt an expression that is understood, we know nothing.  */
  if (!rn.valid())
    return false;

  /* If the lhs has no range, ie , it cannot be executed, then the query
     has no range either.  */
  if (lhs.empty_p ())
    {
      r = lhs;
      return true;
    }

  return get_range (rn, r, name, lhs);
}

/*  ---------------------------------------------------------------------  */


gori::gori () : range_generator (def_chain)
{
  gori_map.create (0);
  gori_map.safe_grow_cleared (last_basic_block_for_fn (cfun));
}

gori::~gori ()
{
  gori_map.release ();
}

/* Is the last stmt in a block interesting to look at for range info.  */

gimple *
gori::last_stmt_gori (basic_block bb)
{
  gimple *stmt;

  stmt = last_stmt (bb);
  if (stmt && gimple_code (stmt) == GIMPLE_COND)
    return stmt;
  return NULL;
}

void
gori::build (basic_block bb)
{
  gimple *stmt;

  /* Non-NULL means its already been processed.  */
  if (gori_map[bb->index])
    return;

  gori_map[bb->index] = BITMAP_ALLOC (NULL);

  /* Look for a branch of some sort at the end of the block, and build the
     GORI map and definition dependcies for it.  */
  stmt = last_stmt_gori (bb);
  if (stmt)
    {
      range_stmt rn (stmt);
      if (rn.valid())
	{
	  tree ssa1,ssa2;
	  if (rn.ssa_required (&ssa1, &ssa2))
	    {
	      if (ssa1)
	        {
		  bitmap_copy (gori_map[bb->index],
			       def_chain[SSA_NAME_VERSION (ssa1)]);
		  bitmap_set_bit (gori_map[bb->index], SSA_NAME_VERSION (ssa1));
		}
	      if (ssa2)
	        {
		  bitmap_ior_into (gori_map[bb->index],
				   def_chain[SSA_NAME_VERSION (ssa2)]);
		  bitmap_set_bit (gori_map[bb->index], SSA_NAME_VERSION (ssa2));
		}
	      return;
	    }
	}
    }
}


void
gori::build ()
{
  basic_block bb;

  FOR_EACH_BB_FN (bb, cfun)
    {
      build (bb);
    }
}

void
gori::dump (FILE *f)
{
  basic_block bb;
  bitmap_iterator bi;
  unsigned y;

  if (!f)
    return;

  fprintf (f, "\nDUMPING DEF_CHAIN\n");
  def_chain.dump (f);

  fprintf (f, "\nDUMPING GORI MAP\n");
  FOR_EACH_BB_FN (bb, cfun)
    {
      if (gori_map[bb->index])
        {
          fprintf (f, "basic block %3d  : ", bb->index);
	  EXECUTE_IF_SET_IN_BITMAP (gori_map[bb->index], 0, y, bi)
	    {
	      print_generic_expr (f, ssa_name (y), TDF_SLIM);
	      fprintf (f, "  ");
	    }
	  fprintf (f, "\n");
	}
    }
  fprintf (f, "\n");

}

bool 
gori::remove_from_gori_map (basic_block bb, tree name)
{
  bitmap_clear_bit (gori_map[bb->index], SSA_NAME_VERSION (name));
  return false;
}


/* Name is not directly mentioned in the gori map, but if one of the
   compnents it is built from are, we can derive the value from that. ie
	 a_3 = c_2 * 2
	 b_6 = a_3 + 5
	 if (a_3 > 10)
   The GORI map will only have c_2 and a_3 since they comprise the
   calculation of a_3.   b_6 will not be there as the only way to know
   that b_6 can be calculated from a_3 would be to visit all the uses of
   a_3 and see whether it is used to help define b_6.
   Far easier now that b_6 is requested would be to simply check now
   if a_3 is used to construct b_6. If it is get the expression for a_3
   and adjust it to b_6.  */
   
bool
gori::get_derived_range_stmt (range_stmt& stmt, tree name, basic_block bb)
{
  gimple *s;
  tree n1,n2;
  unsigned name_v = SSA_NAME_VERSION (name);

  s = last_stmt_gori (bb);
  gcc_assert (s);

  stmt = s;
  if (!stmt.valid ())
    return false;

  if (!stmt.ssa_required (&n1, &n2))
    return false;

  if (n1 && !bitmap_bit_p (def_chain[name_v], SSA_NAME_VERSION (n1)))
    n1 = NULL_TREE;
    
  if (n2 && !bitmap_bit_p (def_chain[name_v], SSA_NAME_VERSION (n2)))
    n2 = NULL_TREE;
  
  /* Non-null n1 or n2 indicates it is used in the calculating name.  */

  /* Used on both sides too complicated.  */
  if (n1 && n2)
    return false;

  /* Well we aren't actually DOING it yet... :-)  */
  return false;
}



bool
gori::range_p (basic_block bb, tree name)
{
  gcc_checking_assert (TREE_CODE (name) == SSA_NAME);

  if (!gori_map[bb->index])
    build (bb);

  return bitmap_bit_p (gori_map[bb->index], SSA_NAME_VERSION (name));
}


/* Known range on an edge.  */
bool
gori::range_on_edge (irange& r, tree name, edge e)
{
  gimple *stmt;
  basic_block bb = e->src;

  gcc_checking_assert (TREE_CODE (name) == SSA_NAME);

  if (!INTEGRAL_TYPE_P (TREE_TYPE (name)) && !POINTER_TYPE_P (TREE_TYPE (name)))
    return false;

  if (!range_p (bb, name))
    return false;

  stmt = last_stmt_gori (bb);
  gcc_assert (stmt);

  if (e->flags & EDGE_TRUE_VALUE)
    {
      irange bool_true (boolean_type_node,  1 , 1);
      return range_generator.get_range_from_stmt (stmt, r, name, bool_true);
    }

  if (e->flags & EDGE_FALSE_VALUE)
    {
      irange bool_false (boolean_type_node,  0 , 0);
      return range_generator.get_range_from_stmt (stmt, r, name, bool_false);
    }

  return false;
}




void
gori::exercise (FILE *output)
{

  basic_block bb;
  irange range;
  
  FOR_EACH_BB_FN (bb, cfun)
    {
      edge_iterator ei;
      edge e;
      bool printed = false;
      FOR_EACH_EDGE (e, ei, bb->succs)
        {
	  unsigned x;
	  for (x = 1; x < num_ssa_names; x++)
	    {
	      tree name = ssa_name (x);
	      if (name && range_p (bb, name))
		{
		  if (range_on_edge (range, name, e))
		    {
		      if (output)
			{
			  printed = true;
			  fprintf (output, "BB%3d: ", bb->index);
			  if (e->flags & EDGE_TRUE_VALUE)
			    fprintf (output, " T: ");
			  else if (e->flags & EDGE_FALSE_VALUE)
			    fprintf (output, " F: ");
			  print_generic_expr (output, name, TDF_SLIM);
			  fprintf(output, "  \t");
			  range.dump(output);
			}
		    }
		}
	    }
	}
      if (printed)
        fprintf (output, "\n");

    }
    
  if (output)
    dump (output);

}



bool
gori::range_on_stmt (irange& r, tree name, gimple *g)
{
  range_stmt rn (g);
  irange lhs;

  /* If we don't understand the stmt... */
  if (!rn.valid())
    return false;

  /* If both operands are the same, we know nothing.  */
  if (rn.operand1 () == rn.operand2 ())
    return false;

  /* If neither operand is what we are looking for, then return nothing.  */
  if (rn.operand1 () != name && rn.operand2 () != name)
    return false;

  /* So far only understand LHS if its an assignment.  */
  if (gimple_code (g) != GIMPLE_ASSIGN)
    return false;

  if (range_generator.get_operand_range (lhs, gimple_get_lhs (g)))
    return range_generator.get_range (rn, r, name, lhs);

  return false;
}

bool
gori::range_of_def (irange& r, gimple *g)
{
  range_stmt rn (g);

  /* If we don't understand the stmt... */
  if (!rn.valid())
    return false;
  
  return rn.fold (r);
}

// -------------------------------------------------------------------------

range_cache::range_cache ()
{
  tab.create (0);
  tab.safe_grow_cleared (last_basic_block_for_fn (cfun));
}

range_cache::~range_cache ()
{
  tab.release ();
}

void
range_cache::reset ()
{
  memset (tab.address () , 0, tab.length () * sizeof (irange *));
  unsigned x;
  for (x = 0; x < tab.length (); x++)
    gcc_assert (tab[x] == NULL);
}

void
range_cache::set_range (basic_block bb, irange_storage *r)
{
  tab[bb->index] = r;
}

irange_storage *
range_cache::operator[] (const basic_block bb)
{
  return tab[bb->index];
}

void
range_cache::dump (FILE *f, tree type)
{
   basic_block bb;

   FOR_EACH_BB_FN (bb, cfun)
    if (tab[bb->index] != NULL)
      {
        irange r(tab[bb->index], type);
	fprintf (f, "BB%d  -> ", bb->index);
	r.dump (f);
      }
}


// -------------------------------------------------------------------------

path_ranger::path_ranger () 
{
  // Just a marker.
  processing = irange_storage::ggc_alloc (1);
  type_range = NULL;
}

bool
path_ranger::init (tree name)
{
  tree type;
  if (TREE_CODE (name) != SSA_NAME)
    return false;

  type = TREE_TYPE (name);
  if (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
    return false;

  def_stmt = SSA_NAME_DEF_STMT (name);
  if (!def_stmt)
    return false;

  ssa_name = name;
  def_bb = gimple_bb (def_stmt);
  if (!def_bb)
    def_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);

  irange tr;
  tr.set_range_for_type (type);
  type_range = irange_storage::ggc_alloc_init (tr);

  block_cache.reset ();
  block_cache.set_range (ENTRY_BLOCK_PTR_FOR_FN (cfun), type_range);
  return true;

}


void
path_ranger::range_for_bb (irange &r, basic_block bb)
{
  determine_block (bb);
  irange tmp (block_cache[bb], TREE_TYPE (ssa_name));
  r = tmp;
}

bool
path_ranger::path_range_entry (irange& r, tree name, basic_block bb)
{
  if (!init (name))
    return false;

  if (trace_path)
    {
      fprintf (dump_file, "path_range_entry BB%d on path for ", bb->index);
      print_generic_expr (dump_file, name, 0);
      fprintf (dump_file,"\n");
    }

  /* Start with any known range.  */
  r.set_range (name);

  /* If its defined in this basic block, then there is no range on entry,
     otherwise, go figure out what is known in predecessor blocks.  */
  if (def_bb != bb)
    {
      irange block_range;
      range_for_bb (block_range, bb);
      r.intersect (block_range);
    }

  if (trace_path)
    {
      fprintf (dump_file, "range on entry query for");
      print_generic_expr (dump_file, name, 0);
      fprintf (dump_file, " in BB%d : returns ",bb->index);
      r.dump (dump_file);
      block_cache.dump (dump_file, TREE_TYPE (name));
      fprintf(dump_file, "\n");
    }

  return true;
}


/* Known range on an edge on the path back to the DEF of name.  */
bool
path_ranger::path_range_edge (irange& r, tree name, edge e)
{
  basic_block bb = e->src;

  /* Get the range for the def and possible basic block.  */
  if (!path_range_entry (r, name, bb))
    return false;

  /* Now intersect it with what we know about this edge.  */
  irange edge_range;
  if (range_on_edge (edge_range, name, e))
    r.intersect (edge_range);
  return true;

}

void
path_ranger::determine_block (basic_block bb)
{
  edge_iterator ei;
  edge e;
  irange er;
  irange block_result;

  if (bb == ENTRY_BLOCK_PTR_FOR_FN (cfun)
      || bb == EXIT_BLOCK_PTR_FOR_FN (cfun))
    return;

  if (trace_path)
    fprintf (dump_file, "determine_block for BB%d\n", bb->index);

  /* If the block cache is set, then we've already visited this block.  */
  if (block_cache[bb] != NULL)
    return;

  /* Avoid infinite recursion by marking this block.  */
  block_cache.set_range (bb, processing);

  if (trace_path)
    fprintf (dump_file, "Visiting preds of BB%d\n", bb->index);

  /* Visit each predecessor to reseolve them.  */
  FOR_EACH_EDGE (e, ei, bb->preds)
    {
      determine_block (e->src);
    }

  if (trace_path)
    fprintf (dump_file, "Re-Visiting preds of BB%d\n", bb->index);

  block_result.clear (TREE_TYPE (ssa_name));
  /* Now Union all the ranges on the incoming edges.  */
  FOR_EACH_EDGE (e, ei, bb->preds)
    {
      basic_block src = e->src;
      if (trace_path)
        fprintf (dump_file, " processing pred BB%d ", src->index);
      /* If a block is still unprocessed, we know nothing.  */
      if (block_cache[src] == processing)
        {
	  if (trace_path)
	    fprintf (dump_file, " Cycle visit.  range_for_type.\n");
	  block_cache.set_range (bb, type_range);
	  return;
	}

      if (range_on_edge (er, ssa_name, e))
        {
	  irange pred_bb_range (block_cache[src], TREE_TYPE (ssa_name));
	  if (trace_path)
	    {
	      fprintf (dump_file, " edge has range : ");
	      er.dump (dump_file);
	      fprintf (dump_file, " Pred has range : ");
	      pred_bb_range.dump (dump_file);

	    }
	  er.intersect (pred_bb_range);
	  block_result.union_ (er);
	  if (trace_path)
	    {
	      fprintf (dump_file, " result union range : ");
	      block_result.dump (dump_file);
	    }
	}
      else
        {
	  /* If there is no range on the edge, it is the predecessor range.  */
	  irange pred_range (block_cache[src], TREE_TYPE (ssa_name));
	  if (trace_path)
	    {
	      fprintf (dump_file, " No range on edge  pred block range is: ");
	      pred_range.dump (dump_file);
	    }
	  block_result.union_ (pred_range);
	  if (trace_path)
	    {
	      fprintf (dump_file, " result union range : ");
	      block_result.dump (dump_file);
	    }
	}
      if (block_result.range_for_type_p ())
        break;
    }

  if (trace_path)
    {
      fprintf (dump_file, "Finished processing preds.  final result: ");
      block_result.dump (dump_file);
    }
  if (block_result.range_for_type_p ())
    block_cache.set_range (bb, type_range);
  else
    {
      irange_storage *mem = irange_storage::ggc_alloc_init (block_result);
      block_cache.set_range (bb, mem);
    }
}

bool
path_ranger::path_range_stmt (irange& r, tree name, gimple *g)
{
  return range_on_stmt (r, name, g);
}

void
path_ranger::dump(FILE *f)
{
  gori::dump (f);
}


void
path_ranger::exercise (FILE *output)
{

  basic_block bb;
  irange range;

  FOR_EACH_BB_FN (bb, cfun)
    {
      unsigned x;
      edge_iterator ei;
      edge e;
      bool printed = false;

      /* This dramatically slows down builds, so only when printing.  */
      if (output)
        {
	  fprintf (output, "----- BB%d -----\n", bb->index);
	  for (x = 1; x < num_ssa_names; x++)
	    {
	      tree name = ssa_name (x);
	      if (name && path_range_entry (range, name, bb))
		{
		  if (output && !range.range_for_type_p ())
		    {
		      if (!printed)
			fprintf (output,"   Ranges on entry :\n");
		      printed = true;
		      fprintf (output, "     ");
		      print_generic_expr (output, name, 0);
		      fprintf (output, " : ");
		      range.dump (output);
		    }
		}
	    }
	  if (printed)
	    fprintf (output, "\n");
	  dump_bb (output, bb, 2, 0);
	  printed = false;
	}

      FOR_EACH_EDGE (e, ei, bb->succs)
        {
	  for (x = 1; x < num_ssa_names; x++)
	    {
	      tree name = ssa_name (x);
	      if (name && range_p (bb, name))
		{
		  if (path_range_edge (range, name, e))
		    {
		      if (output)
			{
			  printed = true;
			  fprintf (output, "     %d->%d ", e->src->index,
				   e->dest->index);
			  if (e->flags & EDGE_TRUE_VALUE)
			    fprintf (output, " (T) ");
			  else if (e->flags & EDGE_FALSE_VALUE)
			    fprintf (output, " (F) ");
			  else
			    fprintf (output, "     ");
			  print_generic_expr (output, name, TDF_SLIM);
			  fprintf(output, "  \t");
			  range.dump(output);
			}
		    }
		}
	    }
	}
      if (printed)
        fprintf (output, "\n");

    }

  if (output)
    dump (output);

}

