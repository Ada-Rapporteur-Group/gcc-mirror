/* IPA Type Escape Analysis and Dead Field Elimination
   Copyright (C) 2019-2020 Free Software Foundation, Inc.

  Contributed by Erick Ochoa <erick.ochoa@theobroma-systems.com>

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

#ifndef GCC_IPA_TYPE_ESCAPE_ANALYSIS_H
#define GCC_IPA_TYPE_ESCAPE_ANALYSIS_H

#include <string>
#include <map>
#include <set>

/* Logging function, useful for debugging.  */
inline void
log (const char *const fmt, ...)
{
  if (!dump_file)
    return;

  va_list args;
  va_start (args, fmt);
  vfprintf (dump_file, fmt, args);
  fflush (dump_file);
  va_end (args);
}

/* Asserts expected gimple code is observed gimple code.  */
inline void
is_gimple_code (const gimple *stmt, const enum gimple_code ex_code)
{
  gcc_assert (stmt);
  const enum gimple_code ob_code = gimple_code (stmt);
  const bool succeeds = ex_code == ob_code;
  gcc_assert (succeeds);
}

/* Determine if type A is complete.  */
inline bool
is_complete (const_tree a)
{
  gcc_assert (a);
  const_tree type_size = TYPE_SIZE (a);
  const bool _is_complete = NULL_TREE != type_size;
  return _is_complete;
}

/* Asserts type A is complete.  */
inline void
assert_is_complete (const_tree a)
{
  const bool _is_complete = is_complete (a);
  gcc_assert (_is_complete);
}

/* Determine if type A is incomplete.  */
inline bool
is_incomplete (const_tree a)
{
  return !is_complete (a);
}

/* Assert type A has is EXPECTED_CODE.  */
inline void
assert_is_type (const_tree a, const enum tree_code expected_code)
{
  gcc_assert (a);
  const enum tree_code observed_code = TREE_CODE (a);
  const bool eq_codes = observed_code == expected_code;
  gcc_assert (eq_codes);
}

/* Assert STMT is of EX_CLASS enum gimple_rhs_class.  */
inline void
assert_is_gimple_rhs_class (const gimple *stmt,
			    const enum gimple_rhs_class ex_class)
{
  gcc_assert (stmt);
  is_gimple_code (stmt, GIMPLE_ASSIGN);
  const enum gimple_rhs_class ob_class = gimple_assign_rhs_class (stmt);
  const bool succeeds = ex_class == ob_class;
  gcc_assert (succeeds);
}

/* There are some cases where I need to change a const_tree to a tree.
 * Some of these are part of the way the API is written.  To avoid
 * warnings, always use this function for casting away const-ness.
 */
inline static tree
const_tree_to_tree (const_tree t)
{
  return (tree) t;
}

// TODO: Rename?
// TSET_T stands for type set.
typedef std::set<const_tree> tset_t;

/* Base class used for visiting tree nodes starting with root T.
 * It can handle recursive cases in the tree graph by holding
 * a set of previously seen nodes and checking before walking
 * a node.

 * Unlike walk_tree, TypeWalker allows users to create post-order
 * callbacks for each type of tree.
 */
class TypeWalker
{
public:
  TypeWalker ()
  {};

  /* Main interface to type walker.
   * Walk type T.
   */
  void walk (const_tree t);

protected:

  /* Typeset holds previously visited nodes.  */
  tset_t tset;

  /* Inner walking method, used to recurse.  */
  void _walk (const_tree t);

  /* Common walking method for REFERENCE_TYPE, ARRAY_TYPE, and POINTER_TYPE.  */
  void _walk_wrapper (const_tree t);

  /* Common walking method for RECORD_TYPE and UNION_TYPE.  */
  void _walk_record_or_union (const_tree t);

  /* Common walking method for FUNCTION_TYPE and METHOD_TYPE.  */
  virtual void _walk_function_or_method (const_tree t);

  /* If the type is memoized and we don't need to walk further down.  */
  virtual bool is_memoized (__attribute__ ((unused)) const_tree t)
  {
    return false;
  }

  /* Function definitions for different TYPEs callbacks.
     _pre is the pre-order callback.
     _post is the post-order callback.
     If you want to find a specific type in a specific order,
     (e.g. RECORD_TYPE and preorder)
     you can create a derived class and implement the function
     void _walk_RECORD_TYPE_pre (const_tree).

     walk_##code is the function that calls
     the preorder callback
     walking subtrees
     and the postorder callback.
     This is for each specific tree code.

     _walk_##code is the function that walks subtrees for that
     specific tree code.
   */
#define TypeWalkerFuncDecl(code) \
  virtual void _walk_##code##_pre (__attribute__((unused)) const_tree t) \
  {}; \
  virtual void _walk_##code (const_tree t); \
  virtual void _walk_##code##_post (__attribute__((unused)) const_tree t) \
  {}; \
  virtual void walk_##code (const_tree t)

// NOTE the lack of semicolon here.
// This is so that when using the macro we can use a semi-colon
// and formatting doesn't break.

  /* These are the types for which we can define a pre-order
   * and post-order functions.  */
  TypeWalkerFuncDecl (VOID_TYPE);
  TypeWalkerFuncDecl (INTEGER_TYPE);
  TypeWalkerFuncDecl (REAL_TYPE);
  TypeWalkerFuncDecl (FIXED_POINT_TYPE);
  TypeWalkerFuncDecl (COMPLEX_TYPE);
  TypeWalkerFuncDecl (ENUMERAL_TYPE);
  TypeWalkerFuncDecl (BOOLEAN_TYPE);
  TypeWalkerFuncDecl (OFFSET_TYPE);
  TypeWalkerFuncDecl (RECORD_TYPE);
  TypeWalkerFuncDecl (POINTER_TYPE);
  TypeWalkerFuncDecl (REFERENCE_TYPE);
  TypeWalkerFuncDecl (ARRAY_TYPE);
  TypeWalkerFuncDecl (UNION_TYPE);
  TypeWalkerFuncDecl (FUNCTION_TYPE);
  TypeWalkerFuncDecl (METHOD_TYPE);

  /* These are not types, but are still trees that
   * can be reached from a tree type.  Therefore, these
   * trees also need to be walked.
   */
  TypeWalkerFuncDecl (field);
  TypeWalkerFuncDecl (return);
  TypeWalkerFuncDecl (args);
  TypeWalkerFuncDecl (arg);
};

/* Base class for the implementation of the visitor pattern for
 * trees which are "expressions".  This might be a misnomer.
 * What it means is that it walks whatever can be the result of
 * the trees returned by gimple_assign_rhs{1,2,3}, gimple_return,
 * gimple_call...
 * TODO: The expressions visited here might not be the whole set
 * but it is what was found while experimentally running some C
 * programs.
 */
class ExprWalker
{
public:
  ExprWalker ()
  {};

  /* Walk tree E.  */
  void walk (const_tree e);

private:

  /* Virtual function to be implemented.  Callback for all E in preorder.  */
  virtual void _walk_pre (__attribute__ ((unused)) const_tree e)
  {};

  /* Inner method that will recurse for walking subtrees in E.  */
  void _walk (const_tree e);

  /* Virtual function to be implemented.  Callback for all E in postorder.  */
  virtual void _walk_post (__attribute__ ((unused)) const_tree e)
  {};

  /* Walking subtrees generically.  Either it is a leaf node,
     (i.e., it does not have subtrees), or it has some operands.
     TODO: This can probably be changed to be more general
     by finding out how many operands an expression has.

     tree_code C is used to assert that we are visiting an operand
     of a specific tree code.
   */
  inline void _walk_leaf (const_tree e, const enum tree_code c);
  inline void _walk_op_n (const_tree e, unsigned n);
  inline void _walk_op_0 (const_tree e, const enum tree_code c);
  inline void _walk_op_1 (const_tree e, const enum tree_code c);

  /* Virtual function declarations for the pre-order and post-order callbacks.
   * _walk_##code##_pre is the preorder callback
   * walk_##code will call the preorder, subtree walker, and postorder
   * _walk_##code is the subtree walker
   * _walk_##code##_post is the post-order callback.
   */
#define ExprWalkerFuncDecl(code) 					   \
  virtual void _walk_##code##_pre (__attribute__ ((unused)) const_tree e)  \
  {};									   \
  void walk_##code (const_tree e);					   \
  void _walk_##code (const_tree e);					   \
  virtual void _walk_##code##_post (__attribute__ ((unused)) const_tree e) \
  {}

  // Some of these are not "EXPR" codes, but they are reachable
  // from gimple_assign_rhs{1,2,3} and others.
  ExprWalkerFuncDecl (CONSTRUCTOR);
  ExprWalkerFuncDecl (INTEGER_CST);
  ExprWalkerFuncDecl (REAL_CST);
  ExprWalkerFuncDecl (STRING_CST);
  ExprWalkerFuncDecl (BIT_FIELD_REF);
  ExprWalkerFuncDecl (ARRAY_REF);
  ExprWalkerFuncDecl (MEM_REF);
  ExprWalkerFuncDecl (COMPONENT_REF);
  ExprWalkerFuncDecl (SSA_NAME);
  ExprWalkerFuncDecl (ADDR_EXPR);
  ExprWalkerFuncDecl (VIEW_CONVERT_EXPR);
  ExprWalkerFuncDecl (IMAGPART_EXPR);
  ExprWalkerFuncDecl (FIELD_DECL);
  ExprWalkerFuncDecl (VAR_DECL);
  ExprWalkerFuncDecl (RESULT_DECL);
  ExprWalkerFuncDecl (PARM_DECL);
  ExprWalkerFuncDecl (FUNCTION_DECL);
  ExprWalkerFuncDecl (LE_EXPR);
  ExprWalkerFuncDecl (LT_EXPR);
  ExprWalkerFuncDecl (EQ_EXPR);
  ExprWalkerFuncDecl (GT_EXPR);
  ExprWalkerFuncDecl (GE_EXPR);
  ExprWalkerFuncDecl (NE_EXPR);
};

/* Base class for applying the visitor pattern to gimple_stmts.
 * This class visits everything it cans during LTO.
 * That includes global variables, and all function declarations that
 * are in the current partition.
 */
class GimpleWalker
{
public:
  GimpleWalker () : _deleted (false)
  {};

  /* Walk the entire code, therefore no input is needed.  */
  void walk ();

protected:
  /* _DELETED is set by overwritten functions that
   * delete a specific gimple stmt.  This tells the
   * gimple walker to remove the gimple stmt.
   */
  bool _deleted;

  /* Walk global variables.  */
  void _walk_globals ();

  /* Walk individual global variable V.  */
  virtual void _walk_global (varpool_node *v);

  /* Will walk declarations, locals, ssa names, and basic blocks.  */
  void _walk_cnode (cgraph_node *cnode);

  /* This will walk the CNODE->decl.  */
  void _walk_decl (cgraph_node *cnode);

  /* Walk ssa_names in CNODE.  */
  void _walk_ssa_names (cgraph_node *cnode);

  /* Walk local variables in CNODE.  */
  void _walk_locals (cgraph_node *cnode);

  /* Iterate over all basic blocks in CNODE.  */
  void _walk_bb (cgraph_node *cnode);

  /* Iterate over all gimple_stmt in BB.  */
  void _walk (basic_block bb);

  /* Function declarations for virtual functions.
   * These include the pre-order callbacks, walk subtrees,
   * and post-order callbacks.
   */
  virtual void _walk_pre_tree (__attribute__((unused)) const_tree t)
  {};
  void walk_tree2 (const_tree t);
  void _walk_tree (const_tree t);
  virtual void _walk_post_tree (__attribute__((unused)) const_tree t)
  {};

  virtual void _walk_pre_gimple (__attribute__((unused)) gimple* g)
  {};
  void walk_gimple (gimple* g);
  void _walk_gimple (gimple* g);
  virtual void _walk_post_gimple (__attribute__((unused)) gimple* g)
  {};

  virtual void _walk_pre_gassign (__attribute__((unused)) gassign* g)
  {};
  void walk_gassign (gassign* g);
  void _walk_gassign (gassign* g);
  virtual void _walk_post_gassign (__attribute__((unused)) gassign* g)
  {};

  virtual void _walk_pre_greturn (__attribute__((unused)) greturn* g)
  {};
  void walk_greturn (greturn* g);
  void _walk_greturn (greturn* g);
  virtual void _walk_post_greturn (__attribute__((unused)) greturn* g)
  {};

  virtual void _walk_pre_gcond (__attribute__((unused)) gcond* g)
  {};
  void walk_gcond (gcond* g);
  void _walk_gcond (gcond* g);
  virtual void _walk_post_gcond (__attribute__((unused)) gcond* g)
  {};

  virtual void _walk_pre_glabel (__attribute__((unused)) glabel* g)
  {};
  void walk_glabel (glabel* g);
  void _walk_glabel (glabel* g);
  virtual void _walk_post_glabel (__attribute__((unused)) glabel* g)
  {};

  virtual void _walk_pre_gcall (__attribute__((unused)) gcall *g)
  {};
  void walk_gcall (gcall *g);
  void _walk_gcall (gcall *g);
  virtual void _walk_post_gcall (__attribute__((unused)) gcall *g)
  {};

  virtual void _walk_pre_gswitch (__attribute__((unused)) gswitch* g)
  {};
  void walk_gswitch (gswitch* g);
  void _walk_gswitch (gswitch* g);
  virtual void _walk_post_gswitch (__attribute__((unused)) gswitch* g)
  {};

  virtual void _walk_pre_gphi (__attribute__((unused)) gphi* g)
  {};
  void walk_gphi (gphi* g);
  void _walk_gphi (gphi* g);
  virtual void _walk_post_gphi (__attribute__((unused)) gphi* g)
  {};

};

/* TYPE_PARTITIONS_S is a structure that is shared
 * across most of the type escape analysis.  It holds
 * 4 different partitions.

 * 1. points to record
 * 2. complement of points to record
 * 3. escaping trees
 * 4. non escaping trees

 * It also has a set of all types seen so far called universe.

 * Ideally 1 union 2 should be universe and 3 union 4 should be universe.
 */
struct type_partitions_s
{
  /* The set of all types which have been seen.  */
  tset_t universe;

  /* The set of all types which somehow refer to a RECORD_TYPE.  */
  tset_t points_to_record;

  /* The complement of points_to_record.  */
  tset_t complement;

  /* The set of all escaping types.  */
  tset_t escaping;

  /* The set of all non escaping types.  */
  tset_t non_escaping;

  /* Determine if we have seen this type before.  */
  bool in_universe (const_tree) const;

  /* Determine if tree points to a record.  */
  bool in_points_to_record (const_tree) const;

  /* Determine if tree does not point to a record.  */
  bool in_complement (const_tree) const;

  /* Insert either in points to record or complement.  */
  void insert (const_tree, bool);
};

typedef struct type_partitions_s tpartitions_t;

/* TypeCollector is a derived class from TypeWalker
 * that collects all types reachable from T into the partitions
 * points_to_record or not points to record.
 */
class TypeCollector : public TypeWalker
{
public:
  TypeCollector ()
  {};

  /* Main interface.  */
  void collect (const_tree t);

  /* Collect the result after walking all trees.  */
  tpartitions_t get_record_reaching_trees ()
  {
    _sanity_check ();
    return ptrset;
  }

private:
  /* PTR stands for points to record.  Before walking into a RECORD_TYPE
   * tree, the value is always false.  Once a RECORD_TYPE is visited,
   * update all values on map to be true.  At post-order keys
   * will be erased.
   * Invariants:
   * before pre-order of root T map is empty
   * after post-order of root T map is empty

   * In other words, the contents are reset after every
   * call to collect.
   */
  std::map<const_tree, bool> ptr;

  /* The type partition set that will hold partitions for
   * points to record or does not point to record.
   * Will be updated during post-order with the keys and values
   * from PTR.
   * This datastructure persists across calls to collect.
   */
  tpartitions_t ptrset;

  /* Sanity check determines that the partitions are mutually
   * exclusive.
   */
  void _sanity_check ();

  /* Store T into partition depending on PTR.  */
  void _collect_simple (const_tree t);

  /* If the value is in PTRSET, no need to visit the lower nodes.  */
  virtual bool is_memoized (const_tree t);

  /* These functions insert and erase elements in PTR.

   * We probably don't need to create a _pre and _post
   * function for all of them.  We could probably substitute
   * one for a general *_pre and *_post method that triggers
   * for all different type T.  However, we want to avoid
   * collecting FIELD_DECL, ARGS, and some other none-types.
   */
  virtual void _walk_VOID_TYPE_pre (const_tree t);
  virtual void _walk_VOID_TYPE_post (const_tree t);
  virtual void _walk_INTEGER_TYPE_pre (const_tree t);
  virtual void _walk_INTEGER_TYPE_post (const_tree t);
  virtual void _walk_REAL_TYPE_pre (const_tree t);
  virtual void _walk_REAL_TYPE_post (const_tree t);
  virtual void _walk_FIXED_POINT_TYPE_pre (const_tree t);
  virtual void _walk_FIXED_POINT_TYPE_post (const_tree t);
  virtual void _walk_COMPLEX_TYPE_pre (const_tree t);
  virtual void _walk_COMPLEX_TYPE_post (const_tree t);
  virtual void _walk_ENUMERAL_TYPE_pre (const_tree t);
  virtual void _walk_ENUMERAL_TYPE_post (const_tree t);
  virtual void _walk_BOOLEAN_TYPE_pre (const_tree t);
  virtual void _walk_BOOLEAN_TYPE_post (const_tree t);
  virtual void _walk_ARRAY_TYPE_pre (const_tree t);
  virtual void _walk_ARRAY_TYPE_post (const_tree t);
  virtual void _walk_POINTER_TYPE_pre (const_tree t);
  virtual void _walk_POINTER_TYPE_post (const_tree t);
  virtual void _walk_REFERENCE_TYPE_pre (const_tree t);
  virtual void _walk_REFERENCE_TYPE_post (const_tree t);
  virtual void _walk_UNION_TYPE_pre (const_tree t);
  virtual void _walk_UNION_TYPE_post (const_tree t);
  virtual void _walk_FUNCTION_TYPE_pre (const_tree t);
  virtual void _walk_FUNCTION_TYPE_post (const_tree t);
  virtual void _walk_METHOD_TYPE_pre (const_tree t);
  virtual void _walk_METHOD_TYPE_post (const_tree t);

  /* When a RECORD_TYPE is found, update all values in PTR to true.  */
  virtual void _walk_RECORD_TYPE_pre (const_tree t);
  virtual void _walk_RECORD_TYPE_post (const_tree t);
};

/* Derived class from TypeWalker.  This class
 * will recursively print all type trees unlike just printing
 * the identifier.
 * TODO: Is this already implemented with debug_tree / print_tree?
 * If so, we can probably delete this...
 */
class TypeStringifier : public TypeWalker
{
public:
  TypeStringifier ()
  {};

  /* Main method, returns a stringified version of T.  */
  std::string stringify (const_tree t);

  /* Only get type identifier.  */
  static std::string get_type_identifier (const_tree t);

  /* If field is not anonymous, return field identifier.  */
  static std::string get_field_identifier (const_tree t);

private:
  /* Working string... will hold result for stringify.  */
  std::string _stringification;

  /* Append get_tree_code_name.  */
  void _stringify_simple (const_tree t);

  /* Append identifier and "{".  */
  void _stringify_aggregate_pre (const_tree t);

  /* Append "}".  */
  void _stringify_aggregate_post (const_tree t);

  /* Append "function {".  */
  // TODO: For C++ we will need to change this for methods.
  void _stringify_fm_pre (const_tree t);
  virtual void _walk_METHOD_TYPE_pre (const_tree t);
  virtual void _walk_METHOD_TYPE_post (const_tree t);
  virtual void _walk_FUNCTION_TYPE_pre (const_tree t);
  virtual void _walk_FUNCTION_TYPE_post (const_tree t);

  /* Append "}".  */
  void _stringify_fm_post (const_tree t);

  /* Most of the pre-order walk can probably be replaced by
   * a catch all pre-order call back.
   * TODO: implement that...
   */
  virtual void _walk_VOID_TYPE_pre (const_tree t);
  virtual void _walk_INTEGER_TYPE_pre (const_tree t);
  virtual void _walk_REAL_TYPE_pre (const_tree t);
  virtual void _walk_FIXED_POINT_TYPE_pre (const_tree t);
  virtual void _walk_COMPLEX_TYPE_pre (const_tree t);
  virtual void _walk_BOOLEAN_TYPE_pre (const_tree t);
  virtual void _walk_OFFSET_TYPE_pre (const_tree t);
  virtual void _walk_return_pre (const_tree t);
  virtual void _walk_args_pre (const_tree t);

  /* Append "*".  */
  virtual void _walk_POINTER_TYPE_post (const_tree t);

  /* Append "&".  */
  virtual void _walk_REFERENCE_TYPE_post (const_tree t);

  /* Append "[]".  */
  virtual void _walk_ARRAY_TYPE_post (const_tree t);

  /* Append "record" */
  virtual void _walk_RECORD_TYPE_pre (const_tree t);
  virtual void _walk_RECORD_TYPE_post (const_tree t);

  /* Append "union" */
  virtual void _walk_UNION_TYPE_pre (const_tree t);
  virtual void _walk_UNION_TYPE_post (const_tree t);

  /* Append "," */
  virtual void _walk_field_post (const_tree t);
  virtual void _walk_return_post (const_tree t);

  /* Append "," */
  virtual void _walk_args_post (const_tree t);
  virtual void _walk_arg_post (const_tree t);
};

/* ExprCollector is an implementation of ExprWalker.  It walks
 * all trees in an expression and calls type collector on
 * the types for all types of nested expressions.
 */
class ExprCollector : public ExprWalker
{
public:
  ExprCollector ()
  {};

  /* Holds the result after collecting from all trees.  */
  tpartitions_t get_record_reaching_trees ()
  {
    return typeCollector.get_record_reaching_trees ();
  }

private:
  TypeCollector typeCollector;

  /* Catch all callback for all nested expressions E.  */
  virtual void _walk_pre (const_tree e);
};

/* Derived from GimpleWalker.  Its purpose is to walk all gimple
 * possible and call expression collector to collect types
 * on global variables, assign statement, return statement,
 * condition statement, and call statements.
 */
class GimpleTypeCollector : public GimpleWalker
{
public:
  GimpleTypeCollector ()
  {};

  /* This holds the result after walking the whole program.  */
  tpartitions_t get_record_reaching_trees ()
  {
    return exprCollector.get_record_reaching_trees ();
  }

  // Print final results.
  // TODO: I believe this could be made const.
  void print_collected ();

private:
  ExprCollector exprCollector;

  /* Call back for global variables.  */
  virtual void _walk_pre_tree (const_tree);

  /* Call back for gassign.  */
  virtual void _walk_pre_gassign (gassign *s);

  /* Call back for greturn.  */
  virtual void _walk_pre_greturn (greturn *s);

  /* Call back for gcond.  */
  virtual void _walk_pre_gcond (gcond *s);

  /* Call back for gcall.  */
  virtual void _walk_pre_gcall (gcall *s);
};

// Reason for why a type is escaping
// Used in a map with corresponding trees as keys.
// TODO: Add bit_field
// TODO: Add has function pointer
// TODO: Add has constructor
struct Reason
{
  // Determines whether a type is escaping.
  inline bool is_escaping () const
  {
    return this->global_is_visible || this->parameter_is_visible
	   || this->return_is_visible || this->type_is_casted
	   || this->type_is_volatile || this->type_is_in_union
	   || this->is_indirect;
  }

  // Escapes because a global variable is visible.
  bool global_is_visible : 1;

  // Escapes because a parameter is used in an
  // externally visible function.
  bool parameter_is_visible : 1;

  // Escapes because return value is from
  // an externally visible function.
  bool return_is_visible : 1;

  // Escapes because of casting.
  bool type_is_casted : 1;

  // Escapes because it is volatile.
  bool type_is_volatile : 1;

  // Escapes because it is in union.
  bool type_is_in_union : 1;

  // Escapes because is in indirect function call.
  bool is_indirect : 1;

  // Merge two reason.
  Reason operator| (const Reason &);
  Reason &operator|= (const Reason &);

  // Print reasons a type is escaping.
  void print () const;

  // Initialize as non-escaping by default.
  Reason ()
    : global_is_visible (0), parameter_is_visible (0), return_is_visible (0),
      type_is_casted (0), type_is_volatile (0), type_is_in_union (0),
      is_indirect (0)
{};
};

typedef std::map<const_tree, Reason> typemap;

/* Type Escaper propagates information on whether a type escapes
 * to all types reachable by a root type.  It also propagates
 * information up if a union is found.  At the moment
 * we don't transform types which point to unions.
 * We also don't transform RECORD_TYPEs which have function pointers.
 * This can possible be removed.  But it is future work.
 * Do not also modify types with bit fields.
 */
class TypeEscaper : public TypeWalker
{
public:
  TypeEscaper (tpartitions_t &p)
    : _ptrset (p), _inside_union (0), _inside_record (0)
  {};

  // Hold the partitions for escaping non escaping.
  tpartitions_t &_ptrset;

  // Have information that matches a tree type with
  // why a type is escaping.
  typemap calc;

  // Get partitions after calculating escaping types.
  tpartitions_t get_sets ();

  // Print reasons why a type is escaping.
  void print_reasons ();

  // Update type T with escaping reason R.
  void update (const_tree t, Reason r);

private:
  // TODO: we can probably reduce the amount of functions
  // by adding a catch all pre-order callback...
  virtual void _walk_POINTER_TYPE_pre (const_tree t);
  virtual void _walk_POINTER_TYPE_post (const_tree t);
  virtual void _walk_REFERENCE_TYPE_pre (const_tree t);
  virtual void _walk_ARRAY_TYPE_pre (const_tree t);
  virtual void _walk_ARRAY_TYPE_post (const_tree t);
  virtual void _walk_RECORD_TYPE_pre (const_tree t);
  virtual void _walk_RECORD_TYPE_post (const_tree t);
  virtual void _walk_field_pre (const_tree t);
  virtual bool is_memoized (const_tree t);

  /* Mark escaping reason as having a function pointer in a structure,
   * propagate up and down.  */
  virtual void _walk_METHOD_TYPE_pre (const_tree t);
  virtual void _walk_FUNCTION_TYPE_pre (const_tree t);

  /* Mark escaping reason as having a union and propagate up and down.  */
  virtual void _walk_UNION_TYPE_pre (const_tree t);
  virtual void _walk_UNION_TYPE_post (const_tree t);

  // Record how many nested unions the current context is in.
  unsigned _inside_union;

  // Record how many nested records the current context is in.
  unsigned _inside_record;

  // Reason to be propagated to all trees reachable by root T
  // Can be updated during the walk.
  Reason _reason;

  // Recursive inner function.
  void _update (const_tree t);

  // Final method that places types from calc to partitions.
  void place_escaping_types_in_set ();
};

/* Visit all expressions and update reasons why they might be deleted.  */
class ExprEscaper : public ExprWalker
{
public:
  ExprEscaper (tpartitions_t &types) : typeEscaper (types)
  {};

  /* Main interface: T escapes because R.  */
  void update (const_tree t, Reason r);

  /* Will be used to propagate escaping reasons to Types.  */
  TypeEscaper typeEscaper;

  /* Holds the end result.  */
  tpartitions_t get_sets ();

  /* Print end result.  */
  void print_reasons ();

private:
  // Keep track of the current expressions.  The top of the stack
  // is the subexpression being examined.
  // The bottom of the stack is the expression called on the update
  // function.
  std::stack<const_tree> _stack;

  // Reason to propagate across all subexpressions.
  Reason _r;

  // push to stack.
  virtual void _walk_pre (const_tree e);

  // pop to stack.
  virtual void _walk_post (const_tree e);

  // Check if there is a cast between the
  // expression (MEM_REF (SSA_NAME))
  // SSA_NAME is the subexpression of MEM_REF.
  virtual void _walk_SSA_NAME_pre (const_tree e);

  // If the expression E is a constructor then we need
  // to mark these types as escaping because we cannot
  // deal with constructors at the moment.
  virtual void _walk_CONSTRUCTOR_pre (const_tree e);
};

// Do a type structural equality for two types.
class TypeStructuralEquality
{
public:
  TypeStructuralEquality ()
  {};

  // Return TRUE if A and B have equal structures
  bool equal (const_tree a, const_tree b);

protected:
  // Recursive _equal
  virtual bool _equal (const_tree a, const_tree b);

private:
  // Use to limit recursion if we are revisiting a node
  typedef std::set<const_tree> tset_t;

  // Limit recursion for LHS
  tset_t set_l;

  // Limit recursion for RHS
  tset_t set_r;

  // Determine if the code is equal
  bool _equal_code (const_tree a, const_tree b);

  // Wrapper around POINTER_TYPE, ARRAY_TYPE and REFERENCE_TYPE
  bool _equal_wrapper (const_tree a, const_tree b);

  // Different types we are comparing
#define TSE_FUNC_DECL(code)					\
  virtual bool _walk_##code (const_tree l, const_tree r)

  // Current types that can be compared.
  TSE_FUNC_DECL (VOID_TYPE);
  TSE_FUNC_DECL (COMPLEX_TYPE);
  TSE_FUNC_DECL (INTEGER_TYPE);
  TSE_FUNC_DECL (REAL_TYPE);
  TSE_FUNC_DECL (FIXED_POINT_TYPE);
  TSE_FUNC_DECL (POINTER_TYPE);
  TSE_FUNC_DECL (ENUMERAL_TYPE);
  TSE_FUNC_DECL (BOOLEAN_TYPE);
  TSE_FUNC_DECL (OFFSET_TYPE);
  TSE_FUNC_DECL (RECORD_TYPE);
  TSE_FUNC_DECL (REFERENCE_TYPE);
  TSE_FUNC_DECL (ARRAY_TYPE);
  TSE_FUNC_DECL (UNION_TYPE);
  TSE_FUNC_DECL (FUNCTION_TYPE);
  TSE_FUNC_DECL (METHOD_TYPE);
};

// Check for equality even when a type is incomplete.
// When one type is incomplete and MAIN_VARIANTS are different
// compare only with identifiers.
// Unsound but it is as sound as it can be.
class TypeIncompleteEquality : public TypeStructuralEquality
{
public:
  TypeIncompleteEquality ()
  {};

protected:
  virtual bool _equal (const_tree l, const_tree r);
};

/* Inspect gimple code and find reasons why types might escape given a gimple
 * stmt.  */
class GimpleEscaper : public GimpleWalker
{
public:
  GimpleEscaper (tpartitions_t &types) : exprEscaper (types)
  {
    _init ();
  };

  /* Propagate escaping reason to subexpressions.  */
  ExprEscaper exprEscaper;

  /* Obtain final result.  */
  tpartitions_t get_sets ();

  /* Print final result.  */
  void print_reasons ();

protected:
  /* Set of undefined functions, this set is filled with
   * functions obtained via FOR_EACH_FUNCTION_WITH_GIMPLE_BODY.  */
  typedef std::set<const_tree> undefset;
  undefset undefined;

  /* Initializes undefined.  */
  void _init ();

  /* Return true if it is a known builtin function.  */
  static bool filter_known_function (cgraph_node *);
  static bool filter_known_function (const_tree);

  /* Return true if function is externally visible.  */
  static bool is_function_escaping (cgraph_node *);
  static bool is_function_escaping (const_tree);

  /* Return true if variable is externally visible.  */
  static bool is_variable_escaping (varpool_node *);

  /* Marks global variables with CONSTRUCTORS and ERROR_MARKs as escaping.  */
  virtual void _walk_global (varpool_node *);

  /* Do not escape on assignments.  */
  virtual void _walk_pre_gassign (gassign *s);

  /* Do not escape return values.  */
  virtual void _walk_pre_greturn (greturn *s);

  /* Do not escape gcond.  */
  virtual void _walk_pre_gcond (gcond *s);

  /* Mark arguments and return type as escaping
   * if callsite is undefined, indirect or externally visible.  */
  virtual void _walk_pre_gcall (gcall *s);

  /* Mark T as escaping if is in UNKNOWN_LOCATION.
   * This is a way of finding
   * types introduced by profiling and mark them as escaping.
   * TODO: Improve this.
   */
  virtual void _walk_pre_tree (const_tree t);
};

/*
 * GimpleCaster is intended to walk gimple
 * and update a map that will hold information
 * on whether a type was casted or not.
 */
class GimpleCaster : public GimpleEscaper
{
public:
  GimpleCaster (tpartitions_t &types) : GimpleEscaper (types)
{};

private:
  /* Determine if cast comes from a known function.  */
  static bool follow_def_to_find_if_really_cast (const_tree);

  /* If arguments are casted, mark them as escaping.
   * Assignments from malloc and other known functions
   * are allowed.
   * */
  virtual void _walk_pre_gcall (gcall *s);

  /* If assignment is casted, mark them as escaping.
   * Assignments from malloc and other known functions
   * are allowed.
   */
  virtual void _walk_pre_gassign (gassign *s);
};

// Bitflags used for determining if a field is
// never accessed, read or written.
// TODO: Place on their own namespace?
const unsigned Empty = 0x0u;
const unsigned Read = 0x01u;
const unsigned Write = 0x02u;

// maps FIELD_DECL -> bitflag.
typedef std::map<const_tree, unsigned> field_access_map_t;

// maps RECORD_TYPE -> (FIELD_DECL -> bitflag).
typedef std::map<const_tree, field_access_map_t> record_field_map_t;

// Class used to determine if a FIELD is read, written or never accessed.
class TypeAccessor : public TypeWalker
{
public:
  TypeAccessor (record_field_map_t &map) : _map (map)
  {};

private:
  // maps RECORD -> (FIELD_DECL -> bitflag).
  record_field_map_t &_map;

  // set of trees which are memoized and we don't need to look into them.
  std::set<const_tree> memoized_map;

  // If a RECORD_TYPE is walked into, add all fields in struct to
  // record_field_map.
  virtual void _walk_RECORD_TYPE_pre (const_tree t);
  void add_all_fields_in_struct (const_tree t);

  bool is_memoized (const_tree t);
};

// Determine if a FIELD is read, written or never accessed from
// an expression.
class ExprAccessor : public ExprWalker
{
public:
  ExprAccessor () : _typeAccessor (record_field_map)
  {};

  // Expr E is accessed in A manner.
  void update (const_tree e, unsigned a);

  // Print results.
  void print_accesses ();

  // Add all fields to map.  Initialize with empty.
  void add_all_fields_in_struct (const_tree t);

  // Get final results.
  record_field_map_t get_map ();

private:
  // Access {"Read", "Write", "Neither"} to propagate to all subexpressions.
  unsigned _access;

  // Stack to keep track of how current subexpression was reached.
  std::stack<const_tree> _stack;

  // Holds main results.
  record_field_map_t record_field_map;

  // Aids expr-accessor in updating types.
  TypeAccessor _typeAccessor;

  // Mark FIELD_DECL as read.
  // If ADDR_EXPR is parent expression that means
  // The address of a field is taken.  Mark
  // all fields as possibly read.
  virtual void _walk_COMPONENT_REF_pre (const_tree e);

  // Check if parent expression is MEM_REF.
  // This means that an optimization was made
  // and a FIELD_DECL is accessed via pointer
  // arithmetic.  Mark all fields from start to the one
  // accessed as read.
  // TODO: We don't necessarily need to mark them as
  // possibly read if we update these expressions to
  // point to the correct address in the future.
  virtual void _walk_ADDR_EXPR_pre (const_tree e);

  // Push to stack.
  virtual void _walk_pre (const_tree t);

  // Pop from stack.
  virtual void _walk_post (const_tree t);
};

/* Walk all gimple and determine if fields were accessed.  */
class GimpleAccesser : public GimpleWalker
{
public:
  GimpleAccesser ()
  {};

  /* Print final results.  */
  void print_accesses ();

  /* Get final results.  */
  record_field_map_t get_map ();

protected:
  /* Navigate expressions in gimple statements.  */
  ExprAccessor exprAccessor;

private:
  /* Mark all RHS expressions reachable from S as Read.
     all all LHS expressions reachable from S as Written.  */
  virtual void _walk_pre_gcall (gcall *s);

  /* Mark all RHS expressions reachable from S as Read.
     Mark all LHS expressions reachable from S as Written.  */
  virtual void _walk_pre_gassign (gassign *s);

  /* Mark all all expressions reachable from S as read.  */
  virtual void _walk_pre_greturn (greturn *s);

  /* Mark all expressions reachable from S as read.  */
  virtual void _walk_pre_gcond (gcond *s);

  // Do we need a glabel? I don't think so...
  // But we might need a gswitch.
};

typedef std::set<unsigned> field_offsets_t;

typedef std::map<const_tree, field_offsets_t> record_field_offset_map_t;

// Partition types into escaping or non escaping sets.
tpartitions_t
partition_types_into_escaping_nonescaping ();

// Compute set of not escaping unaccessed fields
record_field_offset_map_t
obtain_nonescaping_unaccessed_fields (tpartitions_t casting,
				      record_field_map_t record_field_map,
				      int warning);

#endif /* GCC_IPA_TYPE_ESCAPE_ANALYSIS_H */
