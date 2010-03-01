/* Implement UPC PTS 'struct' representation
   Copyright (C) 2008,2009 Free Software Foundation, Inc.
   Written by: Gary Funck <gary@intrepid.com>

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "config.h"
#include "coretypes.h"
#include "system.h"
#include "tree.h"
#include "ggc.h"
#include "hashtab.h"
#include "input.h"
#include "c-tree.h"
#include "langhooks.h"
#include "flags.h"
#include "opts.h"
#include "options.h"
#include "output.h"
#include "toplev.h"
#include "tm.h"
#include "function.h"
#include "target.h"
#include "upc-act.h"
#include "upc-pts.h"
#include "cgraph.h"
#include "gimple.h"
#include "c-common.h"
#include "c-pragma.h"
/* define decl_default_tls_model() prototype */
#include "rtl.h"

/*
 * Build the internal representation of UPC's shared pointer type.
 */
void
upc_pts_init_type (void)
{
  tree fields = NULL_TREE;
  tree name = NULL_TREE;
  tree ref;
  tree shared_void_type;
  const location_t loc = UNKNOWN_LOCATION;
  struct c_struct_parse_info *null_struct_parse_info = NULL;
  int save_pedantic = pedantic;
  /* name = get_identifier ("upc_pts_struct"); */
  ref = start_struct (loc, RECORD_TYPE, name, &null_struct_parse_info);
  /* Ensure that shared pointers have twice the alignment of a pointer.  */
  TYPE_ALIGN (ref) = 2 * TYPE_ALIGN (ptr_type_node);
  upc_vaddr_field_node = build_decl (loc, FIELD_DECL, get_identifier ("vaddr"),
				build_pointer_type (char_type_node));
  fields = chainon (fields, upc_vaddr_field_node);
  DECL_NONADDRESSABLE_P (upc_vaddr_field_node) = 0;
  DECL_INITIAL (upc_vaddr_field_node) = NULL_TREE;
  upc_thread_field_node = build_decl (loc, FIELD_DECL, get_identifier ("thread"),
			     c_common_type_for_size(UPC_PTS_THREAD_SIZE, 1));
  fields = chainon (fields, upc_thread_field_node);
#if UPC_PTS_THREAD_SIZE == 8 || UPC_PTS_THREAD_SIZE == 16 || UPC_PTS_THREAD_SIZE == 32
  DECL_NONADDRESSABLE_P (upc_thread_field_node) = 0;
  DECL_INITIAL (upc_thread_field_node) = NULL_TREE;
#else
  DECL_NONADDRESSABLE_P (upc_thread_field_node) = 1;
  DECL_INITIAL (upc_thread_field_node) = size_int (UPC_PTS_THREAD_SIZE);
#endif
  upc_phase_field_node = build_decl (loc, FIELD_DECL, get_identifier ("phase"),
			   c_common_type_for_size(UPC_PTS_PHASE_SIZE, 1));
  fields = chainon (fields, upc_phase_field_node);
#if UPC_PTS_PHASE_SIZE == 8 || UPC_PTS_PHASE_SIZE == 16 || UPC_PTS_PHASE_SIZE == 32
  DECL_NONADDRESSABLE_P (upc_phase_field_node) = 0;
  DECL_INITIAL (upc_phase_field_node) = NULL_TREE;
#else
  DECL_NONADDRESSABLE_P (upc_phase_field_node) = 1;
  DECL_INITIAL (upc_phase_field_node) = size_int (UPC_PTS_PHASE_SIZE);
#endif
#if !UPC_PTS_VADDR_FIRST
  fields = nreverse (fields);
#endif
  /* avoid spurious complaints regarding the definition
   * `phase' and `thread'. */
  pedantic = 0;
  upc_pts_rep_type_node = finish_struct (loc, ref, fields, NULL_TREE,
                                         null_struct_parse_info);
  gcc_assert (TYPE_MODE (upc_pts_rep_type_node) != BLKmode);
  pedantic = save_pedantic;
  record_builtin_type (RID_SHARED, "upc_shared_ptr_t",
                       upc_pts_rep_type_node);
  shared_void_type = build_variant_type_copy (void_type_node);
  TYPE_SHARED (shared_void_type) = 1;
  upc_pts_type_node = build_pointer_type (shared_void_type);
  upc_null_pts_node = upc_pts_build_value (loc, upc_pts_type_node,
		        integer_zero_node, integer_zero_node, integer_zero_node);
}

/* Called to expand a UPC specific constant into somethng the
   backend can handle.  Upon return a shared pointer will be
   seen as the representation type of a shared pointer, with
   individual (thread, phase, and virtual address) fields.  */

tree
upc_pts_build_constant (location_t loc, tree c)
{
  tree result = c;
  if (is_valid_pts_p (c))
    {
      const enum tree_code code = TREE_CODE (c);
      if (!((code == VIEW_CONVERT_EXPR || code == NOP_EXPR)
             && (TREE_CODE (TREE_OPERAND (c, 0)) == CONSTRUCTOR)
             && (TREE_TYPE (TREE_OPERAND (c, 0)) == upc_pts_rep_type_node)))
        {
	  const tree val = build1 (VIEW_CONVERT_EXPR, upc_pts_rep_type_node,
	                           save_expr (c));
	  const tree p_t = TREE_TYPE (upc_phase_field_node);
	  const tree t_t = TREE_TYPE (upc_thread_field_node);
	  const tree v_t = TREE_TYPE (upc_vaddr_field_node);
	  const tree vaddr = build3 (COMPONENT_REF, v_t, val,
				 upc_vaddr_field_node, NULL_TREE);
	  const tree thread = build3 (COMPONENT_REF, t_t, val,
				 upc_thread_field_node, NULL_TREE);
	  const tree phase = build3 (COMPONENT_REF, p_t, val,
				 upc_phase_field_node, NULL_TREE);
	  result = upc_pts_build_value (loc, TREE_TYPE (c),
	                                vaddr, thread, phase);
	                                            
	}
    }
  return result;
}

/* Build a constructor of the form {phase, thread, vaddr}. */

tree
upc_pts_build_value (location_t loc ATTRIBUTE_UNUSED, tree type,
                     tree vaddr, tree thread, tree phase)
{
  tree elts, result;
  const int is_const = TREE_CONSTANT (vaddr)
                       && TREE_CONSTANT (thread)
                       && TREE_CONSTANT (phase);
  vaddr = fold_convert (TREE_TYPE (upc_vaddr_field_node), vaddr);
  thread = fold_convert (TREE_TYPE (upc_thread_field_node), thread);
  phase = fold_convert (TREE_TYPE (upc_phase_field_node), phase);
  elts = tree_cons (upc_phase_field_node, phase, NULL_TREE);
  elts = tree_cons (upc_thread_field_node, thread, elts);
  elts = tree_cons (upc_vaddr_field_node, vaddr, elts);
#if !UPC_PTS_VADDR_FIRST
  elts = nreverse (elts);
#endif
  result = build_constructor_from_list (upc_pts_rep_type_node, elts);
  TREE_CONSTANT (result) = is_const;

  /* wrap the constructor into the specified pointer to shared type */
  result = build1 (VIEW_CONVERT_EXPR, type, result);
  result = fold (result);
  TREE_CONSTANT (result) = is_const;
  /* force all shared constant pointer values to memory */
  TREE_STATIC (result) = is_const;
  return result;
}

/* return TRUE if EXP is a null pointer to shared. */

int
upc_is_null_pts_p (tree exp)
{
  int result = 0;
  if (exp && is_valid_pts_p (exp))
    {
      tree value;
      for (value = exp;
           TREE_CODE (value) == NOP_EXPR
	    || TREE_CODE (value) == CONVERT_EXPR
	    || TREE_CODE (value) == VIEW_CONVERT_EXPR
	    || TREE_CODE (value) == NON_LVALUE_EXPR;
           value = TREE_OPERAND (value, 0)) /* loop */ ;
      if ((TREE_CODE (value) == CONSTRUCTOR)
	  && (TREE_TYPE (value) == upc_pts_rep_type_node)
	  && TREE_CONSTANT (value))
	{
          VEC(constructor_elt, gc) *c = CONSTRUCTOR_ELTS(value);
	  const tree phase = VEC_index (constructor_elt, c, 0)->value;
	  const tree thread = VEC_index (constructor_elt, c, 1)->value;
	  const tree vaddr = VEC_index (constructor_elt, c, 2)->value;
	  result = integer_zerop (phase) && integer_zerop (thread) && integer_zerop (vaddr);
	}
    }
  return result;
}

tree
upc_pts_build_threadof (location_t loc ATTRIBUTE_UNUSED, tree exp)
{
  const tree uint_t = unsigned_type_node;
  tree affinity;
  gcc_assert (TREE_TYPE (exp) == upc_pts_rep_type_node);
  affinity = build3 (COMPONENT_REF, uint_t, exp,
		    upc_thread_field_node, NULL_TREE);
  return affinity;
}

tree
upc_pts_build_sum (location_t loc, tree exp)
{
  const tree op0 = TREE_OPERAND (exp, 0);
  const tree op1 = TREE_OPERAND (exp, 1);
  const enum tree_code op0_code = TREE_CODE (TREE_TYPE (op0));
  const tree targ_type = TREE_TYPE (TREE_TYPE (exp));
  const tree elem_type = strip_array_types (targ_type);
  const tree elem_size = !VOID_TYPE_P (elem_type)
                   ? size_in_bytes (elem_type) : integer_one_node;
  const tree block_factor = upc_get_block_factor (elem_type);
  const int has_phase =  !(integer_zerop (block_factor)
                           || integer_onep(block_factor));
  const tree elem_per_block = block_factor;
  const tree ptrop = (op0_code == POINTER_TYPE) ? op0 : op1;
  const tree intop = (op0_code == POINTER_TYPE) ? op1 : op0;
  const tree index = save_expr (intop);
  const tree ptrop_as_pts_rep = fold (build1 (VIEW_CONVERT_EXPR,
                                              upc_pts_rep_type_node, ptrop));
  const tree sptrop = save_expr (ptrop_as_pts_rep);
  const tree p_t = TREE_TYPE (upc_phase_field_node);
  const tree t_t = TREE_TYPE (upc_thread_field_node);
  const tree v_t = TREE_TYPE (upc_vaddr_field_node);
  tree n_threads = upc_num_threads ();
  tree old_phase, old_thread, old_vaddr;
  tree phase, thread, vaddr;
  tree tincr, t1, t2;
  tree result;

  old_phase  = build3 (COMPONENT_REF, p_t, sptrop,
                       upc_phase_field_node, NULL_TREE);
  old_thread = build3 (COMPONENT_REF, t_t, sptrop,
                       upc_thread_field_node, NULL_TREE);
  old_vaddr  = build3 (COMPONENT_REF, v_t, sptrop,
                       upc_vaddr_field_node, NULL_TREE);
  thread = old_thread;
  phase = old_phase;
  if (VOID_TYPE_P (targ_type) || integer_zerop (block_factor))
    {
      vaddr = build_binary_op (loc, PLUS_EXPR, old_vaddr,
		      build_binary_op (loc, MULT_EXPR,
		                       index, elem_size, 0), 0);
    }
  else
    {
      /* Make sure n_threads is a signed integer to ensure
         that the FlOOR_MOD and FLOOR_DIV operations below are performed
	 with signed operations. */
      if (TYPE_UNSIGNED (TREE_TYPE (n_threads)))
        n_threads = convert (integer_type_node, n_threads);
      /* tincr = old_thread * elem_per_block + old_phase + index; */
      tincr = build_binary_op (loc, PLUS_EXPR,
		build_binary_op (loc, PLUS_EXPR,
		  build_binary_op (loc, MULT_EXPR,
		                   old_thread, elem_per_block, 0),
		  old_phase, 0),
		index, 0); 
      if (TYPE_UNSIGNED (TREE_TYPE (tincr)))
	tincr = convert (integer_type_node, tincr);
      if (has_phase)
	{
          tree nt_elems;
	  tree phase_diff;
	  old_phase = save_expr (old_phase);
	  /* tincr = old_thread * elem_per_block + old_phase + index; */
	  tincr = build_binary_op (loc, PLUS_EXPR,
	            build_binary_op (loc, PLUS_EXPR,
		      build_binary_op (loc, MULT_EXPR, old_thread,
		                       elem_per_block, 0),
		      old_phase, 0),
		    index, 0); 
	  if (!TYPE_UNSIGNED (TREE_TYPE (index)))
	    tincr = convert (integer_type_node, tincr);
          /* nt_elems = n_threads * elem_per_block; */
          nt_elems = build_binary_op (loc, MULT_EXPR, n_threads,
	                              elem_per_block, 0);
	  if (TYPE_UNSIGNED (TREE_TYPE (nt_elems))
	      != TYPE_UNSIGNED (TREE_TYPE (tincr)))
	    nt_elems = convert (integer_type_node, nt_elems);
          /* floor_divmod (tincr, nt_elems, &t1, &t2);  */
	  t1 = build_binary_op (loc, FLOOR_DIV_EXPR, tincr, nt_elems, 0);
	  t2 = build_binary_op (loc, FLOOR_MOD_EXPR, tincr, nt_elems, 0);
	  t2 = save_expr (t2);
          /* thread = t2 / elem_per_block; */
	  thread = build_binary_op (loc, TRUNC_DIV_EXPR, t2,
	                            elem_per_block, 0);
          /* phase = t2 % elem_per_block; */
	  phase = build_binary_op (loc, TRUNC_MOD_EXPR, t2,
	                           elem_per_block, 0);
	  phase_diff = build_binary_op (loc, MINUS_EXPR, phase, old_phase, 0);
          /* vaddr = old_vaddr + (t1 * elem_per_block + phase_diff)
	                         * elem_size; */
          vaddr = build_binary_op (loc, PLUS_EXPR,
                    old_vaddr,
                    build_binary_op (loc, MULT_EXPR,
		       build_binary_op (loc, PLUS_EXPR,
		         build_binary_op (loc, MULT_EXPR,
			                  t1, elem_per_block, 0),
		         phase_diff, 0),
		       elem_size, 0), 0);
	}
      else
        {
	  /* tincr = old_thread * elem_per_block + index; */
	  tincr = build_binary_op (loc, PLUS_EXPR,
		    build_binary_op (loc, MULT_EXPR, old_thread,
		                     elem_per_block, 0),
		    index, 0); 
	  if (!TYPE_UNSIGNED (TREE_TYPE (index)))
	    tincr = convert (integer_type_node, tincr);
          /* floor_divmod (tincr, n_threads, &t1, &t2);  */
	  t1 = build_binary_op (loc, FLOOR_DIV_EXPR, tincr, n_threads, 0);
	  t2 = build_binary_op (loc, FLOOR_MOD_EXPR, tincr, n_threads, 0);
          /* vaddr = old_vaddr + t1 * elem_size; */
          vaddr = build_binary_op (loc, PLUS_EXPR, old_vaddr,
                    build_binary_op (loc, MULT_EXPR, t1, elem_size, 0), 0);
          /* thread = t2;  */
	  thread = t2;
        }
    }
  result = upc_pts_build_value (loc, TREE_TYPE (exp), vaddr, thread, phase);
  return result;
}

tree
upc_pts_build_diff (location_t loc, tree exp)
{
  tree op0 = TREE_OPERAND (exp, 0);
  tree op1 = TREE_OPERAND (exp, 1);
  const tree result_type = ptrdiff_type_node;
  const tree p_t = TREE_TYPE (upc_phase_field_node);
  const tree t_t = TREE_TYPE (upc_thread_field_node);
  const tree v_t = TREE_TYPE (upc_vaddr_field_node);
  const tree target_type = TREE_TYPE (TREE_TYPE (op0));
  const tree n_threads = upc_num_threads ();
  const tree elem_size = convert(ssizetype, size_in_bytes (target_type));
  const tree block_factor = upc_get_block_factor (target_type);
  tree thread0, thread1, thread_diff;
  tree phase_diff;
  tree off0, off1, offset_diff, elem_diff;
  tree result;

  /* The two pointers must both point to shared objects, and we
     have to perform the reverse of addition on shared pointers */
    
  if ( (upc_shared_type_p (target_type)
	&& !upc_shared_type_p (TREE_TYPE (TREE_TYPE (op1))))
      || (upc_shared_type_p (TREE_TYPE (TREE_TYPE (op1)))
	  && !upc_shared_type_p (target_type)))
    {
      error ("Attempt to take the difference of shared and nonshared pointers");
      return error_mark_node;
    }
  op0 = save_expr (op0);
  op1 = save_expr (op1);
  op0 = build1 (VIEW_CONVERT_EXPR, upc_pts_rep_type_node, op0);
  op1 = build1 (VIEW_CONVERT_EXPR, upc_pts_rep_type_node, op1);
  off0 = build3 (COMPONENT_REF, v_t, op0,
                 upc_vaddr_field_node, NULL_TREE);
  off1 = build3 (COMPONENT_REF, v_t, op1,
                 upc_vaddr_field_node, NULL_TREE);
  /* Convert offset fields into ptrdiff_t types so that the
     result of the difference comes out as a signed type.  */
  off0 = convert(result_type, off0);
  off1 = convert(result_type, off1);
  offset_diff = build_binary_op (loc, MINUS_EXPR, off0, off1, 0);
  elem_diff = build_binary_op (loc, EXACT_DIV_EXPR, offset_diff, elem_size, 0);
  if (integer_zerop (block_factor))
    {
      return elem_diff;
    }
  thread0 = convert (ssizetype,
                     build3 (COMPONENT_REF, t_t, op0,
		             upc_thread_field_node, NULL_TREE));
  thread1 = convert (ssizetype,
                     build3 (COMPONENT_REF, t_t, op1,
		             upc_thread_field_node, NULL_TREE));
  thread_diff = build_binary_op (loc, MINUS_EXPR, thread0, thread1, 0);
  phase_diff = integer_zero_node;
  if (!tree_int_cst_equal (block_factor, integer_one_node))
    {
      tree phase0 = convert (ssizetype,
                             build3 (COMPONENT_REF, p_t, op0,
			             upc_phase_field_node, NULL_TREE));
      tree phase1 = convert (ssizetype,
                             build3 (COMPONENT_REF, p_t, op1,
			             upc_phase_field_node, NULL_TREE));
      phase_diff = save_expr (build_binary_op (loc, MINUS_EXPR, phase0, phase1, 0));
    }
  /* The expression below calculates the following:
        (elem_diff - phase_diff) * THREADS
          + (thread_diff * block_factor) + phase_diff; */
  result = build_binary_op (loc, PLUS_EXPR,
             build_binary_op (loc, PLUS_EXPR,
	       build_binary_op (loc, MULT_EXPR,
	         build_binary_op (loc, MINUS_EXPR, elem_diff, phase_diff, 0),
		 n_threads, 0),
               build_binary_op (loc, MULT_EXPR, thread_diff, block_factor, 0), 0),
             phase_diff, 0);
  result = fold_convert (result_type, result);
  return result;
}

/* Add OFFSET into the address filed of shared pointer, PTR.  */

tree
upc_pts_build_add_offset (location_t loc, tree ptr, tree offset)
{
  const tree p_t = TREE_TYPE (upc_phase_field_node);
  const tree t_t = TREE_TYPE (upc_thread_field_node);
  const tree v_t = TREE_TYPE (upc_vaddr_field_node);
  const tree ptr_as_pts_rep = fold (build1 (VIEW_CONVERT_EXPR,
				            upc_pts_rep_type_node, ptr));
  const tree sptr = save_expr (ptr_as_pts_rep);
  tree result;
  result = upc_pts_build_value (loc, TREE_TYPE (ptr),
               build_binary_op (loc, PLUS_EXPR,
                       build3 (COMPONENT_REF, v_t, sptr,
                               upc_vaddr_field_node, NULL_TREE),
	               offset, 0),
               build3 (COMPONENT_REF, t_t, sptr,
                       upc_thread_field_node, NULL_TREE),
               build3 (COMPONENT_REF, p_t, sptr,
                       upc_phase_field_node, NULL_TREE));
  return result;
}

/* Handle conversions between pointers to shared objects and
   local pointers, or between pointers to shared objects which
   have differing block factors.  */

tree
upc_pts_build_cvt (location_t loc, tree exp)
{
  const tree type = TREE_TYPE (exp);
  const tree p_t = ptr_type_node;
  const tree t_t = TREE_TYPE (upc_thread_field_node);
  const tree ptr = TREE_OPERAND (exp, 0);
  tree tt1, tt2, b1, b2;
  tree result = exp;

  tt1 = TREE_TYPE (TREE_TYPE (exp));
  tt2 = TREE_TYPE (TREE_TYPE (TREE_OPERAND (exp, 0)));
  b1 = upc_get_block_factor (tt1);
  b2 = upc_get_block_factor (tt2);
  if (upc_shared_type_p (tt1) != upc_shared_type_p (tt2))
    {
      if (upc_shared_type_p (tt1))
	{
          /* Error: local -> shared */
	  result = error_mark_node;
	}
      else
	{
	  /* shared -> local */
	  tree libfunc = identifier_global_value (
	                     get_identifier (UPC_GETADDR_LIBCALL));
	  tree src = build1 (NOP_EXPR, upc_pts_rep_type_node,
	                     TREE_OPERAND (exp, 0));
	  tree lib_call;

	  if (!libfunc)
	    internal_error ("library function %s not found",
	                    UPC_GETADDR_LIBCALL);
	  lib_call = build_function_call (loc, libfunc,
	                   build_tree_list (NULL_TREE, src));
	  result = build1 (VIEW_CONVERT_EXPR, type, lib_call);
	}
    }
  else if ((upc_shared_type_p (tt1) && !VOID_TYPE_P (tt1))
           && !(integer_zerop (b1) && integer_zerop (b2)))
    {
      /* below, we handle the case of conversions to non-generic
         shared types. If the target is a generic type, we can
	 safely use the source value directly. */
      tree s1 = TYPE_SIZE (tt1);
      tree s2 = TYPE_SIZE (tt2);
      /* normalize blocksizes, so that [0] => NULL */
      if (integer_zerop (b1)) b1 = NULL;
      if (integer_zerop (b2)) b2 = NULL;
      /* normalize type size so that 0 => NULL */
      if (s1 && integer_zerop (s1)) s1 = NULL;
      if (s2 && integer_zerop (s2)) s2 = NULL;
      /* If the source type is a not a generic pointer to shared, and
         either its block size or type size differs from the target,
	 then the result must have zero phase.  If the source type is
	 a generic pointer to shared and the target type is a pointer
	 to a shared type with either an indefinite block size, or
	 a block size of one, then the resulting value must have a
	 phase of zero. */
      if ((!VOID_TYPE_P (tt2)
              && !(tree_int_cst_equal (b1, b2) && tree_int_cst_equal (s1, s2)))
          || (VOID_TYPE_P (tt2)
	      && ((b1 == NULL) || tree_int_cst_equal (b1, integer_one_node))))
        {
          const tree ptr_as_pts_rep = fold (build1 (VIEW_CONVERT_EXPR,
                                               upc_pts_rep_type_node, ptr));
	  const tree sptr = save_expr (ptr_as_pts_rep);
	  const tree ptr_with_zero_phase = upc_pts_build_value (loc, type,
		    build3 (COMPONENT_REF, p_t, sptr,
		            upc_vaddr_field_node, NULL_TREE),
		    build3 (COMPONENT_REF, t_t, sptr,
		            upc_thread_field_node, NULL_TREE),
		    integer_zero_node);
	  result = ptr_with_zero_phase;
        }
    }
  return result;
}

/* Rewrite op0 CMP op1 into a field by field
   comparison of the shared pointer operands
   in the following order: vaddr, thread, phase.  */

tree
upc_pts_build_cond_expr (location_t loc, tree exp)
{
  tree result;
  const enum tree_code code = TREE_CODE (exp);
  const int is_bitwise_cmp = (code == EQ_EXPR || code == NE_EXPR);
  tree op0 = TREE_OPERAND (exp, 0);
  tree op1 = TREE_OPERAND (exp, 1);
  const tree type0 = TREE_TYPE (op0);
  const tree type1 = TREE_TYPE (op1);
  gcc_assert (POINTER_TYPE_P (type0));
  gcc_assert (POINTER_TYPE_P (type1));
  {
    const tree ttype0 = TREE_TYPE (type0);
    const tree ttype1 = TREE_TYPE (type1);
    const tree elem_type0 = strip_array_types (ttype0);
    const tree elem_type1 = strip_array_types (ttype1);
    gcc_assert (TREE_SHARED (elem_type0));
    gcc_assert (TREE_SHARED (elem_type1));
    {
      const tree bs0 = upc_get_block_factor (ttype0);
      const tree bs1 = upc_get_block_factor (ttype1);
      const int has_phase0 = !(integer_zerop (bs0) || integer_onep(bs0));
      const int has_phase1 = !(integer_zerop (bs1) || integer_onep(bs1));
      const int has_phase = has_phase0 && has_phase1;
      if (is_bitwise_cmp)
        {
	  const tree t_t = TREE_TYPE (upc_thread_field_node);
	  const tree v_t = TREE_TYPE (upc_vaddr_field_node);
	  const enum tree_code code0 = TREE_CODE (op0);
	  const enum tree_code code1 = TREE_CODE (op1);
	  const enum tree_code tcode = (code == EQ_EXPR)
	                               ? TRUTH_ANDIF_EXPR : TRUTH_ORIF_EXPR;
	  if (code0 == VIEW_CONVERT_EXPR
	      && TREE_TYPE (TREE_OPERAND (op0, 0)) == upc_pts_rep_type_node)
	    op0 = TREE_OPERAND (op0, 0);
	  else
	    op0 = build1 (VIEW_CONVERT_EXPR, upc_pts_rep_type_node, op0);
	  if (code1 == VIEW_CONVERT_EXPR
	      && TREE_TYPE (TREE_OPERAND (op1, 0)) == upc_pts_rep_type_node)
	    op1 = TREE_OPERAND (op1, 0);
	  else
	    op1 = build1 (VIEW_CONVERT_EXPR, upc_pts_rep_type_node, op1);
	  op0 = save_expr (op0);
	  op1 = save_expr (op1);
	  {
	    const tree off0 = build3 (COMPONENT_REF, v_t, op0,
			              upc_vaddr_field_node, NULL_TREE);
	    const tree off1 = build3 (COMPONENT_REF, v_t, op1,
			              upc_vaddr_field_node, NULL_TREE);
	    const tree off_cmp = build_binary_op (loc, code, off0, off1, 0);
	    const tree thread0 = build3 (COMPONENT_REF, t_t, op0,
			                 upc_thread_field_node, NULL_TREE);
	    const tree thread1 = build3 (COMPONENT_REF, t_t, op1,
			                 upc_thread_field_node, NULL_TREE);
	    const tree thread_cmp = build_binary_op (loc, code, thread0, thread1, 0);
	    result = build_binary_op (loc, tcode, off_cmp, thread_cmp, 0);
	    if (has_phase)
	      {
	        const tree p_t = TREE_TYPE (upc_phase_field_node);
		const tree phase0 = build3 (COMPONENT_REF, p_t, op0,
					    upc_phase_field_node, NULL_TREE);
		const tree phase1 = build3 (COMPONENT_REF, p_t, op1,
					    upc_phase_field_node, NULL_TREE);
		const tree phase_cmp = build_binary_op (loc, code, phase0, phase1, 0);
		result = build_binary_op (loc, tcode, result, phase_cmp, 0);
	      }
	    /* Remove possible C_MAYBE_EXPR operands. */
	    result = c_fully_fold (result, 0, NULL);
	    result = gimple_boolify (result);
	    result = fold_convert (TREE_TYPE (exp), result);
	  }
	}
      else
        {
	  const tree ptr_diff = build_binary_op (loc, MINUS_EXPR, op0, op1, 0);
          op0 = ptr_diff;
          op1 = build_int_cst (TREE_TYPE (op0), 0);
	  TREE_OPERAND (exp, 0) = op0;
	  TREE_OPERAND (exp, 1) = op1;
	  result = exp;
	}
    }
  }
  return result;
}
