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

/* Interprocedural dead field analysis (IPA-DFA)

   The goal of this analysis is to

   1) discover RECORD_TYPEs which do not escape the current linking unit.

   2) discover fields in RECORD_TYPEs that are never read.

   3) merge the results from 1 and 2 to determine which fields are not needed.

   The algorithm basically consists of the following stages:

   1) Partition all TYPE_P trees into two sets: those trees which reach a
   tree of RECORD_TYPE.

   2.a) Analyze callsites to determine if arguments and return types are
   escaping.
   2.b) Analyze casts to determine if it would be safe to mark a field as dead.
   2.c) Analyze for constructors and static initialization and mark this as
   TYPE_P trees as unable to be modified
   2.d) Analyze if FIELD_DECL are accessed via pointer arithmetic and mark
   FIELD_DECLs before as unable to be modified.
   2.e) Analyze if an address of a FIELD_DECL is taken and mark the whole
   RECORD_TYPE as unable to be modified.
   2.f) Propagate this information to nested TYPE_P trees.
   2.g) Propagate this information across different TYPE_P trees that represent
   equivalent TYPE_P types.

   3.a) Analyze FIELD_DECL to determine whether they are read,
   written or neither.
   3.b) Unify this information across different RECORD_TYPE trees that
   represent equivalent types
   3.c) Determine which FIELD_DECL can be deleted.

   4) Calculate the intersection of non-escaping RECORD_TYPEs with RECORD_TYPEs
   that have a field that can be deleted.

   First stage - Determining if a TYPE_P points to a RECORD_TYPE
   =============================================================

   This stage is computed through the *Collector classes.  Those are
   TypeCollector, ExprCollector and GimpleTypeCollector which walk up and down
   types, expressions, and gimple respectively and propagate information about
   TYPE_P trees and mantain information on the type partitions.

   Second stage - Determining if a TYPE_P escapes
   ==============================================

   This stage is computed through the *Escaper classes.  Those are
   TypeEscaper, ExprEscaper, GimpleEscaper, GimpleCaster classes.  These
   classes walk up and down types, expressions and gimple respectively and
   propagate reasons why a TYPE_P tree might be escaping.
   Reasons are always ORed and equivalent TYPE_P trees might hold different
   results up to when equivalence is computed for all TYPE_P trees and reasons
   are propagated until a fixedpoint is achieved.

   Third stage - Calculating FIELD_DECL accesses
   =============================================

   This stage is computed through the *Accessor classes.  Those are
   TypeAccessor, ExprAccessor, and GimpleAccessor.  These classes walk up and
   down TYPE_P, expressions, and gimple respectively and propagate access
   information.  If an expression occurs in the LHS, it is marked as written
   and if it occurs on the RHS, it is marked as read.  Special cases where
   addresses of a FIELD_DECLs are taken mark all FIELD_DECL in a RECORD_TYPE
   as read.

   Fourth stage - Intersection of accesses and non_escaping
   ========================================================

   This stage happens in the function obtain_unescaped_and_unaccessed_fields.
   First all FIELD_DECLs are translated to their respective field offset.
   Then all field offsets for FIELD_DECLs which are READ are stored
   in a set.  We then compute the complement of this set and these are the
   offsets of FIELD_DECLs which are never read.

   Offsets are needed if we are to find dead fields for anonymous fields.
*/



#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "tree.h"
#include "gimple-expr.h"
#include "predict.h"
#include "alloc-pool.h"
#include "tree-pass.h"
#include "cgraph.h"
#include "diagnostic.h"
#include "fold-const.h"
#include "gimple-fold.h"
#include "symbol-summary.h"
#include "tree-vrp.h"
#include "ipa-prop.h"
#include "tree-pretty-print.h"
#include "tree-inline.h"
#include "ipa-fnsummary.h"
#include "ipa-utils.h"
#include "tree-ssa-ccp.h"
#include "stringpool.h"
#include "attribs.h"
#include "basic-block.h" //needed for gimple.h
#include "function.h"    //needed for gimple.h
#include "gimple.h"
#include "stor-layout.h"
#include "cfg.h" // needed for gimple-iterator.h
#include "gimple-iterator.h"
#include "gimplify.h"      //unshare_expr
#include "value-range.h"   // make_ssa_name dependency
#include "tree-ssanames.h" // make_ssa_name
#include "ssa.h"
#include "tree-into-ssa.h"
#include "gimple-ssa.h" // update_stmt
#include "tree.h"
#include "gimple-expr.h"
#include "predict.h"
#include "alloc-pool.h"
#include "tree-pass.h"
#include "cgraph.h"
#include "diagnostic.h"
#include "fold-const.h"
#include "gimple-fold.h"
#include "symbol-summary.h"
#include "tree-vrp.h"
#include "ipa-prop.h"
#include "tree-pretty-print.h"
#include "tree-inline.h"
#include "ipa-fnsummary.h"
#include "ipa-utils.h"
#include "tree-ssa-ccp.h"
#include "stringpool.h"
#include "attribs.h"
#include "tree-ssa-alias.h"
#include "tree-ssanames.h"
#include "gimple.h"
#include "cfg.h"
#include "gimple-iterator.h"
#include "gimple-ssa.h"
#include "gimple-pretty-print.h"
#include "tree-cfg.h"
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>

#include "ipa-type-escape-analysis.h"
#include "ipa-dfe.h"

#define ABORT_IF_NOT_C true

bool detected_incompatible_syntax = false;

// Main function that drives dfe.
static unsigned int
lto_dfe_execute ();

// Partition types into reching record or non reaching record sets.
static tpartitions_t
partition_types_into_record_reaching_or_non_record_reaching ();

// Perform dead field elimination.
static void
lto_dead_field_elimination ();

// Fixed point calculating to determine escaping types.
static void
fix_escaping_types_in_set (tpartitions_t &types);

// Find which fields are accessed.
static record_field_map_t
find_fields_accessed ();

// TODO:
// This was copy pasted from tree-ssa-structalias.c
// Maybe delete this and make the function visible?
static HOST_WIDE_INT
bitpos_of_field (const tree fdecl)
{
  if (!tree_fits_shwi_p (DECL_FIELD_OFFSET (fdecl))
      || !tree_fits_shwi_p (DECL_FIELD_BIT_OFFSET (fdecl)))
    return -1;

  return (tree_to_shwi (DECL_FIELD_OFFSET (fdecl)) * BITS_PER_UNIT
	  + tree_to_shwi (DECL_FIELD_BIT_OFFSET (fdecl)));
}


namespace {
const pass_data pass_data_ipa_type_escape_analysis = {
  SIMPLE_IPA_PASS,
  "type-escape-analysis",
  OPTGROUP_NONE,
  TV_NONE,
  (PROP_cfg | PROP_ssa),
  0,
  0,
  0,
  0,
};

class pass_ipa_type_escape_analysis : public simple_ipa_opt_pass
{
public:
  pass_ipa_type_escape_analysis (gcc::context *ctx)
    : simple_ipa_opt_pass (pass_data_ipa_type_escape_analysis, ctx)
  {}

  virtual bool gate (function *)
  {
    return in_lto_p && flag_ipa_type_escape_analysis;
  }
  virtual unsigned execute (function *)
  {
    return lto_dfe_execute ();
  }
};
} // namespace

/* Top level function.  */
static unsigned int
lto_dfe_execute ()
{
  lto_dead_field_elimination ();
  log ("finished!\n");
  return 0;
}

/* Heuristic to determine if casting is allowed in a function.
 * This heuristic attempts to allow casting in functions which follow the
 * pattern where a struct pointer or array pointer is casted to void* or 
 * char*.  The heuristic works as follows:
 *
 * There is a simple per-function analysis that determines whether there
 * is more than 1 type of struct referenced in the body of the method.
 * If there is more than 1 type of struct referenced in the body,
 * then the layout of the structures referenced within the body
 * cannot be casted.  However, if there's only one type of struct referenced
 * in the body of the function, casting is allowed in the function itself.
 * The logic behind this is that the if the code follows good programming
 * practices, the only way the memory should be accessed is via a singular
 * type. There is also another requisite to this per-function analysis, and
 * that is that the function can only call colored functions or functions
 * which are available in the linking unit.
 *
 * Using this per-function analysis, we then start coloring leaf nodes in the
 * call graph as ``safe'' or ``unsafe''.  The color is propagated to the 
 * callers of the functions until a fixed point is reached.
 */
std::map<tree, bool>
get_whitelisted_nodes ()
{
  cgraph_node *node = NULL;
  std::set<cgraph_node *> nodes;
  std::set<cgraph_node *> leaf_nodes;
  std::set<tree> leaf_nodes_decl;
  FOR_EACH_FUNCTION_WITH_GIMPLE_BODY (node)
  {
    node->get_untransformed_body ();
    nodes.insert(node);
    if (node->callees) continue;

    leaf_nodes.insert (node);
    leaf_nodes_decl.insert (node->decl);
  }

  std::queue<cgraph_node *> worklist;
  for (std::set<cgraph_node*>::iterator i = leaf_nodes.begin (),
    e = leaf_nodes.end (); i != e; ++i)
  {
    if (dump_file) fprintf (dump_file, "is a leaf node %s\n", (*i)->name ());
    worklist.push (*i);
  }

  for (std::set<cgraph_node*>::iterator i = nodes.begin (),
    e = nodes.end (); i != e; ++i)
  {
    worklist.push (*i);
  }

  std::map<tree, bool> map;
  while (!worklist.empty ())
  {

    if (detected_incompatible_syntax) return map;
    cgraph_node *i = worklist.front ();
    worklist.pop ();
    if (dump_file) fprintf (dump_file, "analyzing %s %p\n", i->name (), i);
    GimpleWhiteLister whitelister;
    whitelister._walk_cnode (i);
    bool no_external = whitelister.does_not_call_external_functions (i, map);
    bool before_in_map = map.find (i->decl) != map.end ();
    bool place_callers_in_worklist = !before_in_map;
    if (!before_in_map)
    {
      map.insert(std::pair<tree, bool>(i->decl, no_external));
    } else
    {
      map[i->decl] = no_external;
    }
    bool previous_value = map[i->decl];
    place_callers_in_worklist |= previous_value != no_external;
    if (previous_value != no_external)
    {
       // This ensures we are having a total order
       // from no_external -> !no_external
       gcc_assert (!previous_value);
       gcc_assert (no_external);
    }

    for (cgraph_edge *e = i->callers; place_callers_in_worklist && e;
      e = e->next_caller)
    {
      worklist.push (e->caller);
    }
  }

  return map;

}

/*
 * Perform dead field elimination at link-time.
 * This transformation is composed of two main stages:
 *   * Finding out which fields are non escaping and unaccessed.
 *   * Creating new types and substituting their mention throughout the
 *   program.
 */
static void
lto_dead_field_elimination ()
{
  // Analysis.
  detected_incompatible_syntax = false;
  std::map<tree, bool> whitelisted = get_whitelisted_nodes ();
  tpartitions_t escaping_nonescaping_sets
    = partition_types_into_escaping_nonescaping (whitelisted);
  if (detected_incompatible_syntax) return;
  record_field_map_t record_field_map = find_fields_accessed ();
  if (detected_incompatible_syntax) return;
  record_field_offset_map_t record_field_offset_map
    = obtain_nonescaping_unaccessed_fields (escaping_nonescaping_sets, 
					    record_field_map, OPT_Wdfa);
  if (detected_incompatible_syntax || record_field_offset_map.empty ())
    return;

    // Prepare for transformation.
  std::set<const_tree> to_modify
    = get_all_types_pointing_to (record_field_offset_map,
				 escaping_nonescaping_sets);
  reorg_maps_t replacements
    = get_types_replacement (record_field_offset_map, to_modify);
  reorg_record_map_t map = replacements.first;
  reorg_field_map_t field_map = replacements.second;
  // Transformation.
  substitute_types_in_program (map, field_map, true);
}

/* Iterate all gimple bodies and collect trees
 * which are themselves RECORD_TYPE or which
 * somehow reach a RECORD_TYPE tree (e.g., via a
 * pointer, array, reference, union, field, etc...).
 * Let's call these trees record_reaching_trees.
 */
static tpartitions_t
partition_types_into_record_reaching_or_non_record_reaching ()
{
  GimpleTypeCollector collector;
  collector.walk ();
  tpartitions_t partitions = collector.get_record_reaching_trees ();
  return partitions;
}

/* Iterate over all gimple bodies and find out
 * which types are escaping AND are being casted.
 */
tpartitions_t
partition_types_into_escaping_nonescaping (std::map<tree, bool> &whitelisted)
{
  tpartitions_t partitions
    = partition_types_into_record_reaching_or_non_record_reaching ();
  if (detected_incompatible_syntax) return partitions;
  GimpleCaster caster (partitions, whitelisted);
  caster.walk ();

  // Dump for debugging.
  if (flag_print_cast_analysis)
    caster.print_reasons ();

  partitions = caster.get_sets ();
  // Unify results from different trees representing the same type
  // until a fixed point is reached.
  fix_escaping_types_in_set (partitions);
  return partitions;
}

/* Iterate over all gimple bodies and find out
 * which fields are accessed for all RECORD_TYPE
 * types.
 */
record_field_map_t static find_fields_accessed ()
{
  GimpleAccesser accesser;
  accesser.walk ();

  // Dump for debugging.
  if (flag_print_access_analysis)
    accesser.print_accesses ();

  // This record_field_map holds
  // RECORD_TYPE -> (FIELD_DECL -> how field is accessed)
  record_field_map_t record_field_map = accesser.get_map ();
  return record_field_map;
}

/* Find equivalent RECORD_TYPE trees to const_tree r_i.
 * This equivalence will be used for merging the results of field accesses
 * across all equivalent RECORD_TYPE trees.

 * r_i should exists in the points_to_record set
 * and it is a tree for which this method is going to find the rest of
 * equivalent trees found in record_field_map.
 */
static std::vector<const_tree>
find_equivalent_trees (const_tree r_i, record_field_map_t record_field_map,
		       tpartitions_t casting)
{
  TypeIncompleteEquality equality;
  std::vector<const_tree> equivalence;
  bool is_rin_record = casting.in_points_to_record (r_i);
  if (!is_rin_record)
    return equivalence;

  for (std::map<const_tree, field_access_map_t>::const_iterator j
       = record_field_map.begin (),
       f = record_field_map.end ();
       j != f; j++)
    {
      const_tree r_j = j->first;
      const bool pointer_equal = r_i == r_j;
      if (pointer_equal)
	continue;

      bool is_p_record = casting.in_points_to_record (r_i)
			 && casting.in_points_to_record (r_j);
      if (!is_p_record)
	continue;

      const bool are_equal = equality.equal (r_i, r_j);
      if (!are_equal)
	continue;

      equivalence.push_back (r_j);
    }
  return equivalence;
}

/*
 * FIELD is a FIELD_DECL tree, ACCESSED is a a bitflag that marks whether the
 * field is read, written or neither.  FIELD_OFFSET will hold the following map:
 * tree (RECORD_TYPE) -> unsigned (bitpos_of_field for read fields).
 */
static void
add_offset_only_if_read (const_tree field, unsigned access,
			 field_offsets_t &field_offset)
{
  assert_is_type (field, FIELD_DECL);
  const bool is_read = access & Read;
  if (!is_read)
    return;

  tree _field = const_tree_to_tree (field);
  unsigned f_offset = bitpos_of_field (_field);
  field_offset.insert (f_offset);
}

/*
 * FIELD_MAP holds the following map:
 * tree (FIELD_DECL) -> access type
 * FIELD_OFFSET is being built here.
 * It should hold
 * tree (RECORD_TYPE) -> bitpos_of_field for read fields).
 */
static void
keep_only_read_fields_from_field_map (field_access_map_t &field_map,
				      field_offsets_t &field_offset)
{
  for (std::map<const_tree, unsigned>::iterator j = field_map.begin (),
						f = field_map.end ();
       j != f; ++j)
    {
      add_offset_only_if_read (j->first, j->second, field_offset);
    }
}

/*
 * EQUIVALENT holds equivalent trees of RECORD_TYPE
 * Update FIELD_OFFSET as the union of all READ FIELDS for the equivalent trees.
 */
static void
keep_only_read_fields_from_equivalent_field_maps (
  std::vector<const_tree> equivalent, record_field_map_t &record_field_map,
  field_offsets_t &field_offset)
{
  for (std::vector<const_tree>::iterator j = equivalent.begin (),
					 f = equivalent.end ();
       j != f; j++)
    {
      const_tree r_j = *j;
      field_access_map_t equivalent_field_map = record_field_map[r_j];
      keep_only_read_fields_from_field_map (equivalent_field_map, field_offset);
    }
}

/*
 * Whether RECORDS are escaping or can't be modified,
 * delete them from the set of candidate RECORDS to be modified.
 */
static void
erase_if_no_fields_can_be_deleted (
  record_field_offset_map_t &record_field_offset_map,
  std::set<const_tree> &to_keep, std::set<const_tree> &to_erase)
{
  for (std::map<const_tree, field_offsets_t>::iterator i
       = record_field_offset_map.begin (),
       e = record_field_offset_map.end ();
       i != e; ++i)
    {
      const_tree record = i->first;
      const bool keep = to_keep.find (record) != to_keep.end ();
      if (keep)
	continue;

      to_erase.insert (record);
    }

  for (std::set<const_tree>::iterator i = to_erase.begin (),
				      e = to_erase.end ();
       i != e; ++i)
    {
      const_tree record = *i;
      record_field_offset_map.erase (record);
    }
}

/*
 * Mark escaping RECORD_TYPEs as ready to be deleted from the
 * set of candidates to be modified.
 */
static void
mark_escaping_types_to_be_deleted (
  record_field_offset_map_t &record_field_offset_map,
  std::set<const_tree> &to_erase, tpartitions_t casting)
{
  const tset_t &non_escaping = casting.non_escaping;
  for (std::map<const_tree, field_offsets_t>::iterator i
       = record_field_offset_map.begin (),
       e = record_field_offset_map.end ();
       i != e; ++i)
    {
      const_tree record = i->first;
      const bool in_set = non_escaping.find (record) != non_escaping.end ();
      if (in_set)
	continue;

      to_erase.insert (record);
    }
}

// Obtain nonescaping unaccessed fields
record_field_offset_map_t
obtain_nonescaping_unaccessed_fields (tpartitions_t casting,
				      record_field_map_t record_field_map,
				      int _warning)
{
  bool has_fields_that_can_be_deleted = false;
  record_field_offset_map_t record_field_offset_map;
  for (std::map<const_tree, field_access_map_t>::iterator i
       = record_field_map.begin (),
       e = record_field_map.end ();
       i != e; ++i)
    {
      const_tree r_i = i->first;
      std::vector<const_tree> equivalence
	= find_equivalent_trees (r_i, record_field_map, casting);
      field_offsets_t field_offset;
      field_access_map_t original_field_map = record_field_map[r_i];
      keep_only_read_fields_from_field_map (original_field_map, field_offset);
      keep_only_read_fields_from_equivalent_field_maps (equivalence,
							record_field_map,
							field_offset);
      // These map holds the following:
      // RECORD_TYPE -> unsigned (bit_pos_offset which has been read)
      record_field_offset_map[r_i] = field_offset;
    }

  // So now that we only have the FIELDS which are read,
  // we need to compute the complement...

  // Improve: This is tightly coupled, I need to decouple it...
  std::set<const_tree> to_erase;
  std::set<const_tree> to_keep;
  mark_escaping_types_to_be_deleted (record_field_offset_map, to_erase,
				     casting);
  for (std::map<const_tree, field_offsets_t>::iterator i
       = record_field_offset_map.begin (),
       e = record_field_offset_map.end ();
       i != e; ++i)
    {
      const_tree record = i->first;
      const bool will_be_erased = to_erase.find (record) != to_erase.end ();
      // No need to compute which fields can be deleted if type is escaping
      if (will_be_erased)
	continue;

      field_offsets_t field_offset = i->second;
      for (tree field = TYPE_FIELDS (record); field; field = DECL_CHAIN (field))
	{
	  unsigned f_offset = bitpos_of_field (field);
	  bool in_set2 = field_offset.find (f_offset) != field_offset.end ();
	  if (in_set2)
	    {
	      field_offset.erase (f_offset);
	      continue;
	    }
	  to_keep.insert (record);
	  field_offset.insert (f_offset);
	  has_fields_that_can_be_deleted = true;
	  // NOTE: With anonymous fields this might be weird to print.
	  log ("%s.%s may be deleted\n",
	       TypeStringifier::get_type_identifier (record).c_str (),
	       TypeStringifier::get_field_identifier (field).c_str ());

	  if (_warning == 0)
	    continue;
	  // Anonymous fields? (Which the record can be!).
	  warning (_warning, "RECORD_TYPE %qE has dead field %qE in LTO.\n",
		   record, field);
	}
      record_field_offset_map[record] = field_offset;
    }

  // Improve: Make this more elegant.
  if (!has_fields_that_can_be_deleted)
    {
      record_field_offset_map_t empty;
      return empty;
    }

  erase_if_no_fields_can_be_deleted (record_field_offset_map, to_keep,
				     to_erase);

  return record_field_offset_map;
}

// Main interface to TypeWalker
// Start recursive walk
void
TypeWalker::walk (const_tree t)
{
  gcc_assert (t);
  this->tset.clear ();
  this->_walk (t);
}

void
TypeWalker::_walk (const_tree type)
{
  // Improve, verify that having a type is an invariant.
  // I think there was a specific example which didn't
  // allow for it
  if (detected_incompatible_syntax) return;
  if (!type)
    return;

  gcc_assert (type);

  // This is an optimization.
  const bool _is_memoized = is_memoized (type);
  if (_is_memoized)
    return;

  // This is for correctness
  // Some types are represented as a graph
  // of trees and therefore we need a way to
  // avoid loops in this graph.
  // Imrpove: Outline finding if it is recursive?
  const bool is_recursing = tset.find (type) != tset.end ();
  if (is_recursing)
    return;

  tset.insert (type);
  const enum tree_code code = TREE_CODE (type);
  switch (code)
    {
    case VOID_TYPE:
      this->walk_VOID_TYPE (type);
      break;
    case INTEGER_TYPE:
      this->walk_INTEGER_TYPE (type);
      break;
    case REAL_TYPE:
      this->walk_REAL_TYPE (type);
      break;
    case FIXED_POINT_TYPE:
      this->walk_FIXED_POINT_TYPE (type);
      break;
    case COMPLEX_TYPE:
      this->walk_COMPLEX_TYPE (type);
      break;
    case ENUMERAL_TYPE:
      this->walk_ENUMERAL_TYPE (type);
      break;
    case BOOLEAN_TYPE:
      this->walk_BOOLEAN_TYPE (type);
      break;
    case OFFSET_TYPE:
      this->walk_OFFSET_TYPE (type);
      break;
    case RECORD_TYPE:
      this->walk_RECORD_TYPE (type);
      break;
    case POINTER_TYPE:
      this->walk_POINTER_TYPE (type);
      break;
    //case REFERENCE_TYPE:
    //  this->walk_REFERENCE_TYPE (type);
    //  break;
    case ARRAY_TYPE:
      this->walk_ARRAY_TYPE (type);
      break;
    case UNION_TYPE:
      this->walk_UNION_TYPE (type);
      break;
    case FUNCTION_TYPE:
      this->walk_FUNCTION_TYPE (type);
      break;
    //case METHOD_TYPE:
      //this->walk_METHOD_TYPE (type);
      //break;
    // Since we are dealing only with C at the moment,
    // we don't care about QUAL_UNION_TYPE nor LANG_TYPEs
    // So fail early.
    case REFERENCE_TYPE:
    case METHOD_TYPE:
    case QUAL_UNION_TYPE:
    case LANG_TYPE:
    default:
      {
	log ("missing %s\n", get_tree_code_name (code));
#ifdef ABORT_IF_NOT_C
	detected_incompatible_syntax = true;
#else
	gcc_unreachable ();
#endif
      }
      break;
    }
  tset.erase (type);
}

// This is used to walk over subtrees.
// But before walking subtrees, we need to
// call the pre-order callback
// and after we need to
// call the post-order callback.
#define TypeWalkerFuncDef(code)						\
  void TypeWalker::walk_##code (const_tree t)				\
  {									\
    assert_is_type (t, code);						\
    _walk_##code##_pre (t);						\
    _walk_##code (t);							\
    _walk_##code##_post (t);						\
  }

#define TypeWalkerFuncDefInternal(code)					\
  void TypeWalker::_walk_##code (__attribute__ ((unused)) const_tree t) \
  {}

TypeWalkerFuncDef (VOID_TYPE)
TypeWalkerFuncDefInternal (VOID_TYPE)
TypeWalkerFuncDef (INTEGER_TYPE)
TypeWalkerFuncDefInternal (INTEGER_TYPE)
TypeWalkerFuncDef (REAL_TYPE)
TypeWalkerFuncDefInternal (REAL_TYPE)
TypeWalkerFuncDef (BOOLEAN_TYPE)
TypeWalkerFuncDefInternal (BOOLEAN_TYPE)
TypeWalkerFuncDef (OFFSET_TYPE)
TypeWalkerFuncDefInternal (OFFSET_TYPE)
TypeWalkerFuncDef (FIXED_POINT_TYPE)
TypeWalkerFuncDefInternal (FIXED_POINT_TYPE)
TypeWalkerFuncDef (COMPLEX_TYPE)
TypeWalkerFuncDefInternal (COMPLEX_TYPE)
TypeWalkerFuncDef (ENUMERAL_TYPE)
TypeWalkerFuncDefInternal (ENUMERAL_TYPE)

/* walk wrapper is used for unwrapping
 * REFERENCE_TYPE, POINTER_TYPE, ARRAY_TYPE.
 */
void TypeWalker::_walk_wrapper (const_tree t)
{
  const_tree inner_type = TREE_TYPE (t);
  // I think I encountered this code:
  // FIXME: Do we really need this?
  if (!inner_type)
    return;

  gcc_assert (inner_type);
  _walk (inner_type);
}

#define TypeWalkerFuncDefWrapper(code)		\
  void TypeWalker::_walk_##code (const_tree t)  \
  { _walk_wrapper (t); }

TypeWalkerFuncDef (POINTER_TYPE)
TypeWalkerFuncDefWrapper (POINTER_TYPE)
TypeWalkerFuncDefWrapper (REFERENCE_TYPE)
TypeWalkerFuncDef (REFERENCE_TYPE)
TypeWalkerFuncDef (ARRAY_TYPE)
TypeWalkerFuncDefWrapper (ARRAY_TYPE)
TypeWalkerFuncDef (RECORD_TYPE)

void
TypeWalker::_walk_RECORD_TYPE (const_tree t)
{
  _walk_record_or_union (t);
}

TypeWalkerFuncDef (UNION_TYPE)

void
TypeWalker::_walk_UNION_TYPE (const_tree t)
{
  _walk_record_or_union (t);
}

void
TypeWalker::_walk_record_or_union (const_tree t)
{
  for (tree field = TYPE_FIELDS (t); field; field = DECL_CHAIN (field))
    {
      gcc_assert (field);
      walk_field (field);
    }
}

void
TypeWalker::walk_field (const_tree t)
{
  _walk_field_pre (t);
  _walk_field (t);
  _walk_field_post (t);
}

void
TypeWalker::_walk_field (const_tree t)
{
  const_tree inner_type = TREE_TYPE (t);
  gcc_assert (inner_type);
  _walk (inner_type);
}

TypeWalkerFuncDef (FUNCTION_TYPE)

  void TypeWalker::_walk_FUNCTION_TYPE (const_tree t)
{
  _walk_function_or_method (t);
}

TypeWalkerFuncDef (METHOD_TYPE)

  void TypeWalker::_walk_METHOD_TYPE (const_tree t)
{
  _walk_function_or_method (t);
}

void
TypeWalker::_walk_function_or_method (const_tree t)
{
  const_tree ret_type = TREE_TYPE (t);
  walk_return (ret_type);
  walk_args (t);
}

void
TypeWalker::walk_return (const_tree t)
{
  _walk_return_pre (t);
  _walk_return (t);
  _walk_return_post (t);
}

void
TypeWalker::_walk_return (const_tree t)
{
  _walk (t);
}

void
TypeWalker::walk_args (const_tree t)
{
  _walk_args_pre (t);
  _walk_args (t);
  _walk_args_post (t);
}

void
TypeWalker::_walk_args (const_tree t)
{
  for (tree arg_node = TYPE_ARG_TYPES (t); NULL_TREE != arg_node;
       arg_node = TREE_CHAIN (arg_node))
    {
      const_tree arg_node_type = TREE_VALUE (arg_node);
      gcc_assert (arg_node_type);
      walk_arg (arg_node_type);
    }
}

void
TypeWalker::walk_arg (const_tree t)
{
  _walk_arg_pre (t);
  _walk_arg (t);
  _walk_arg_post (t);
}

void
TypeWalker::_walk_arg (const_tree t)
{
  _walk (t);
}

/* Main interface for the ExprWalker... */
void
ExprWalker::walk (const_tree e)
{
  if (detected_incompatible_syntax) return;
  _walk_pre (e);
  _walk (e);
  _walk_post (e);
}

void
ExprWalker::_walk (const_tree e)
{
  gcc_assert (e);
  const enum tree_code code = TREE_CODE (e);
  switch (code)
    {
    case INTEGER_CST:
      walk_INTEGER_CST (e);
      break;
    case REAL_CST:
      walk_REAL_CST (e);
      break;
    case STRING_CST:
      walk_STRING_CST (e);
      break;
    case BIT_FIELD_REF:
      walk_BIT_FIELD_REF (e);
      break;
    case ARRAY_REF:
      walk_ARRAY_REF (e);
      break;
    case MEM_REF:
      walk_MEM_REF (e);
      break;
    case COMPONENT_REF:
      walk_COMPONENT_REF (e);
      break;
    case SSA_NAME:
      walk_SSA_NAME (e);
      break;
    case ADDR_EXPR:
      walk_ADDR_EXPR (e);
      break;
    case VIEW_CONVERT_EXPR:
      walk_VIEW_CONVERT_EXPR (e);
      break;
    case IMAGPART_EXPR:
      walk_IMAGPART_EXPR (e);
      break;
    case VAR_DECL:
      walk_VAR_DECL (e);
      break;
    case FIELD_DECL:
      walk_FIELD_DECL (e);
      break;
    case RESULT_DECL:
      walk_RESULT_DECL (e);
      break;
    case PARM_DECL:
      walk_PARM_DECL (e);
      break;
    case FUNCTION_DECL:
      walk_FUNCTION_DECL (e);
      break;
    case CONSTRUCTOR:
      walk_CONSTRUCTOR (e);
      break;
    case LE_EXPR:
      walk_LE_EXPR (e);
      break;
    case LT_EXPR:
      walk_LT_EXPR (e);
      break;
    case EQ_EXPR:
      walk_EQ_EXPR (e);
      break;
    case GT_EXPR:
      walk_GT_EXPR (e);
      break;
    case GE_EXPR:
      walk_GE_EXPR (e);
      break;
    case NE_EXPR:
      walk_NE_EXPR (e);
      break;
    default:
      {
	log ("missing %s\n", get_tree_code_name (code));
#ifdef ABORT_IF_NOT_C
	detected_incompatible_syntax = true;
#else
	gcc_unreachable ();
#endif
      }
      break;
    }
}

/* call pre-order callback for everything
 * call pre-order callback for specific code
 * walk subtrees
 * call post-order callback for specific code
 * call post-order callback for everything.
 */
#define ExprWalkerFuncDef(code) 			\
  void ExprWalker::walk_##code (const_tree e)		\
  {							\
    assert_is_type (e, code);				\
    _walk_pre (e);					\
    _walk_##code##_pre (e);				\
    _walk_##code (e);					\
    _walk_##code##_post (e);				\
    _walk_post (e);					\
  }

ExprWalkerFuncDef (CONSTRUCTOR)
ExprWalkerFuncDef (INTEGER_CST)
ExprWalkerFuncDef (REAL_CST)
ExprWalkerFuncDef (STRING_CST)
ExprWalkerFuncDef (BIT_FIELD_REF)
ExprWalkerFuncDef (ARRAY_REF)
ExprWalkerFuncDef (MEM_REF)
ExprWalkerFuncDef (COMPONENT_REF)
ExprWalkerFuncDef (SSA_NAME)
ExprWalkerFuncDef (ADDR_EXPR)
ExprWalkerFuncDef (VIEW_CONVERT_EXPR)
ExprWalkerFuncDef (IMAGPART_EXPR)
ExprWalkerFuncDef (FIELD_DECL)
ExprWalkerFuncDef (VAR_DECL)
ExprWalkerFuncDef (RESULT_DECL)
ExprWalkerFuncDef (PARM_DECL)
ExprWalkerFuncDef (FUNCTION_DECL)
ExprWalkerFuncDef (LE_EXPR)
ExprWalkerFuncDef (LT_EXPR)
ExprWalkerFuncDef (EQ_EXPR)
ExprWalkerFuncDef (GT_EXPR)
ExprWalkerFuncDef (GE_EXPR)
ExprWalkerFuncDef (NE_EXPR)

void ExprWalker::_walk_leaf (const_tree e, const enum tree_code c)
{
  assert_is_type (e, c);
}

void
ExprWalker::_walk_op_n (const_tree e, unsigned n)
{
  gcc_assert (e);
  const_tree op_n = TREE_OPERAND (e, n);
  gcc_assert (op_n);
  walk (op_n);
}

void
ExprWalker::_walk_op_0 (const_tree e, const enum tree_code c)
{
  assert_is_type (e, c);
  _walk_op_n (e, 0);
}

void
ExprWalker::_walk_op_1 (const_tree e, const enum tree_code c)
{
  assert_is_type (e, c);
  _walk_op_n (e, 0);
  _walk_op_n (e, 1);
}

void
ExprWalker::_walk_CONSTRUCTOR (__attribute__ ((unused)) const_tree e)
{
  // Future-work: If we want to support rewriting CONSTRUCTORs
  // we will have to walk them
}

void
ExprWalker::_walk_LE_EXPR (const_tree e)
{
  _walk_op_1 (e, LE_EXPR);
}

void
ExprWalker::_walk_LT_EXPR (const_tree e)
{
  _walk_op_1 (e, LT_EXPR);
}

void
ExprWalker::_walk_EQ_EXPR (const_tree e)
{
  _walk_op_1 (e, EQ_EXPR);
}

void
ExprWalker::_walk_GT_EXPR (const_tree e)
{
  _walk_op_1 (e, GT_EXPR);
}

void
ExprWalker::_walk_GE_EXPR (const_tree e)
{
  _walk_op_1 (e, GE_EXPR);
}

void
ExprWalker::_walk_NE_EXPR (const_tree e)
{
  _walk_op_1 (e, NE_EXPR);
}

void
ExprWalker::_walk_INTEGER_CST (const_tree e)
{
  _walk_leaf (e, INTEGER_CST);
}

void
ExprWalker::_walk_REAL_CST (const_tree e)
{
  _walk_leaf (e, REAL_CST);
}

void
ExprWalker::_walk_STRING_CST (const_tree e)
{
  _walk_leaf (e, STRING_CST);
}

void
ExprWalker::_walk_BIT_FIELD_REF (__attribute__ ((unused)) const_tree e)
{
  // TODO:
  // We currently don't support bit_field_ref
  // but maybe we need to do something here?
}

void
ExprWalker::_walk_ARRAY_REF (const_tree e)
{
  _walk_op_1 (e, ARRAY_REF);
}

void
ExprWalker::_walk_MEM_REF (const_tree e)
{
  _walk_op_1 (e, MEM_REF);
}

void
ExprWalker::_walk_COMPONENT_REF (const_tree e)
{
  _walk_op_1 (e, COMPONENT_REF);
}

void
ExprWalker::_walk_SSA_NAME (const_tree e)
{
  _walk_leaf (e, SSA_NAME);
}

void
ExprWalker::_walk_ADDR_EXPR (const_tree e)
{
  _walk_op_0 (e, ADDR_EXPR);
}

void
ExprWalker::_walk_VIEW_CONVERT_EXPR (__attribute__ ((unused)) const_tree e)
{
  // TODO: I don't think we need to do anything here
}

void
ExprWalker::_walk_IMAGPART_EXPR (__attribute__ ((unused)) const_tree e)
{
  // TODO: I don't think we need to do anything here
}

void
ExprWalker::_walk_FIELD_DECL (const_tree e)
{
  _walk_leaf (e, FIELD_DECL);
}

void
ExprWalker::_walk_VAR_DECL (const_tree e)
{
  _walk_leaf (e, VAR_DECL);
}

void
ExprWalker::_walk_RESULT_DECL (const_tree e)
{
  _walk_leaf (e, RESULT_DECL);
}

void
ExprWalker::_walk_PARM_DECL (const_tree e)
{
  _walk_leaf (e, PARM_DECL);
}

void
ExprWalker::_walk_FUNCTION_DECL (const_tree e)
{
  _walk_leaf (e, FUNCTION_DECL);
  for (tree parm = DECL_ARGUMENTS (e); parm; parm = DECL_CHAIN (parm))
    {
      walk (parm);
    }
}

/* Main interface for GimpleWalker:
 * iterate over global variables and then for all functions
 * with gimple body.
 */
void
GimpleWalker::walk ()
{
  _walk_globals ();
  std::set<tree> fndecls;
  cgraph_node *node = NULL;
  FOR_EACH_FUNCTION_WITH_GIMPLE_BODY (node)
    {
      if (detected_incompatible_syntax) return;
      node->get_untransformed_body ();
      tree decl = node->decl;
      gcc_assert (decl);
      const bool already_in_set = fndecls.find (decl) != fndecls.end ();
      // I think it is possible for different nodes to point to the same
      // declaration.
      if (already_in_set)
	continue;

      if (dump_file)
	dump_function_to_file (node->decl, dump_file, TDF_NONE);

      _walk_cnode (node);
      fndecls.insert (decl);
    }
}

/* For each global variable.  */
void
GimpleWalker::_walk_globals ()
{
  varpool_node *vnode = NULL;
  FOR_EACH_VARIABLE (vnode)
    {
      _walk_global (vnode);
    }
}

/* Walk over global variable VNODE.  */
void
GimpleWalker::_walk_global (varpool_node *vnode)
{
  gcc_assert (vnode);
  struct ipa_ref *ref = NULL;
  for (unsigned i = 0; vnode->iterate_referring (i, ref); i++)
    {
      tree var_decl = vnode->decl;
      walk_tree2 (var_decl);
    }
}

/* Walk over SSA_NAMEs in CNODE.  */
void
GimpleWalker::_walk_ssa_names (cgraph_node *cnode)
{
  const_tree decl = cnode->decl;
  gcc_assert (decl);
  function *func = DECL_STRUCT_FUNCTION (decl);
  gcc_assert (func);
  size_t i = 0;
  tree ssa_name = NULL;
  push_cfun (func);
  FOR_EACH_SSA_NAME (i, ssa_name, cfun)
  {
    gcc_assert (ssa_name);
    walk_tree2 (ssa_name);
    tree ssa_name_var = SSA_NAME_VAR (ssa_name);
    if (!ssa_name_var)
      continue;
    walk_tree2 (ssa_name_var);
  }
  pop_cfun ();
}

/* Walk over declaration, locals, ssa_names, and basic blocks
 * in CNODE.  */
void
GimpleWalker::_walk_cnode (cgraph_node *cnode)
{
  gcc_assert (cnode);
  currently_walking = cnode;
  _walk_decl (cnode);
  _walk_locals (cnode);
  _walk_ssa_names (cnode);
  _walk_bb (cnode);
}

/* Walk over each local declaration in CNODE.  */
void
GimpleWalker::_walk_locals (cgraph_node *cnode)
{
  const_tree decl = cnode->decl;
  gcc_assert (decl);
  function *func = DECL_STRUCT_FUNCTION (decl);
  gcc_assert (func);
  int i = 0;
  tree var_decl = NULL;
  FOR_EACH_LOCAL_DECL (func, i, var_decl)
    {
      gcc_assert (var_decl);
      walk_tree2 (var_decl);
    }
}

/* Walk over all basic blocks in CNODE.  */
void
GimpleWalker::_walk_bb (cgraph_node *cnode)
{
  gcc_assert (cnode);
  cnode->get_untransformed_body ();
  const_tree decl = cnode->decl;
  gcc_assert (decl);
  function *func = DECL_STRUCT_FUNCTION (decl);
  gcc_assert (func);
  basic_block bb = NULL;
  push_cfun (func);
  FOR_EACH_BB_FN (bb, func)
    {
      _walk (bb);
    }
  pop_cfun ();
}

/* Walk over CNODE->decl.  */
void
GimpleWalker::_walk_decl (cgraph_node *cnode)
{
  const_tree decl = cnode->decl;
  gcc_assert (decl);
  walk_tree2 (decl);
}

/* Walk over each gimple statement in BB.  */
void
GimpleWalker::_walk (basic_block bb)
{
  gcc_assert (bb);
  gimple_stmt_iterator gsi = gsi_start_bb (bb);
  while (!gsi_end_p (gsi))
    {
      this->_deleted = false;
      gimple *stmt = gsi_stmt (gsi);
      walk_gimple (stmt);
      // If it is not deleted just continue.
      if (!this->_deleted)
	{
	  gsi_next (&gsi);
	  continue;
	}

      // Otherwise remove statement.
      unlink_stmt_vdef (stmt);
      gsi_remove (&gsi, true);
    }

  // TODO: Maybe outline to its own function?
  for (gimple_stmt_iterator gsi = gsi_start_phis (bb); !gsi_end_p (gsi);
       gsi_next (&gsi))
    {
      gimple *stmt = gsi_stmt (gsi);
      walk_gimple (stmt);
    }
}

// call preorder callback
// walk subtrees
// call postorder callback
void
GimpleWalker::walk_gimple (gimple *stmt)
{
  _walk_pre_gimple (stmt);
  _walk_gimple (stmt);
  _walk_post_gimple (stmt);
}

/* Switch for different gimple instruction types.  */
void
GimpleWalker::_walk_gimple (gimple *stmt)
{
// Do not use _walk_pre (s)
// Subtle but important distinction,
// we want to differentiate calling here stamtent from s
// TODO: Maybe delete though?
// This could also be the source for the double insertion to stack bug?
  if (gassign *_gassign = dyn_cast<gassign*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_gassign (_gassign);
    _walk_post_gimple (stmt);
    return;
  }

  if (greturn *_greturn = dyn_cast<greturn*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_greturn (_greturn);
    _walk_post_gimple (stmt);
    return;
  }

  if (gcond *_gcond = dyn_cast<gcond*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_gcond (_gcond);
    _walk_post_gimple (stmt);
    return;
  }

  if (gcall *_gcall = dyn_cast<gcall*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_gcall (_gcall);
    _walk_post_gimple (stmt);
    return;
  }

  if (glabel *_glabel = dyn_cast<glabel*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_glabel (_glabel);
    _walk_post_gimple (stmt);
    return;
  }

  if (gswitch *_gswitch = dyn_cast<gswitch*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_gswitch (_gswitch);
    _walk_post_gimple (stmt);
    return;
  }


  if (gphi *_gphi = dyn_cast<gphi*> (stmt))
  {
    _walk_pre_gimple (stmt);
    walk_gphi (_gphi);
    _walk_post_gimple (stmt);
    return;
  }

  const enum gimple_code code = gimple_code (stmt);
  switch (code)
    {
    case GIMPLE_DEBUG:
    case GIMPLE_PREDICT:
    case GIMPLE_NOP:
      // I think it is safe to skip these
      // but it would also be nice to walk their sub-trees
      return;
      break;
    default:
      break;
  }

  // Break if something is unexpected.
  const char *name = gimple_code_name[code];
  log ("gimple code name %s\n", name);
#ifdef ABORT_IF_NOT_C
  detected_incompatible_syntax = true;
#else
  gcc_unreachable ();
#endif
}

void
GimpleWalker::walk_tree2 (const_tree t)
{
  _walk_pre_tree (t);
  _walk_tree (t);
  _walk_post_tree (t);
}

void
GimpleWalker::_walk_tree (const_tree t)
{}

void
GimpleWalker::walk_gassign (gassign *g)
{
  _walk_pre_gassign (g);
  _walk_gassign (g);
  _walk_post_gassign (g);
}

void
GimpleWalker::_walk_gassign (gassign *g)
{}

void
GimpleWalker::walk_greturn (greturn *g)
{
  _walk_pre_greturn (g);
  _walk_greturn (g);
  _walk_post_greturn (g);
}

void
GimpleWalker::_walk_greturn (greturn *g)
{}

void
GimpleWalker::walk_gcond (gcond *g)
{
  _walk_pre_gcond (g);
  _walk_gcond (g);
  _walk_post_gcond (g);
}

void
GimpleWalker::_walk_gcond (gcond *g)
{}

void
GimpleWalker::walk_gcall (gcall *g)
{
  _walk_pre_gcall (g);
  _walk_gcall (g);
  _walk_post_gcall (g);
}

void
GimpleWalker::_walk_gcall (gcall *g)
{}

void
GimpleWalker::walk_glabel (glabel *g)
{
  _walk_pre_glabel (g);
  _walk_glabel (g);
  _walk_post_glabel (g);
}

void
GimpleWalker::_walk_glabel (glabel *g)
{}

void
GimpleWalker::walk_gswitch (gswitch *g)
{
  _walk_pre_gswitch (g);
  _walk_gswitch (g);
  _walk_post_gswitch (g);
}

void
GimpleWalker::_walk_gswitch (gswitch *g)
{
}

void
GimpleWalker::walk_gphi (gphi *g)
{
  _walk_pre_gphi (g);
  _walk_gphi (g);
  _walk_post_gphi (g);
}

void
GimpleWalker::_walk_gphi (gphi *g)
{
}

void
TypeCollector::collect (const_tree t)
{
  const bool in_set = ptrset.in_universe (t);
  // Early memoization...

  if (in_set)
    return;

  // TODO: Can we move this to the beginning
  // of the function.
  gcc_assert (t);

  // This is the map that holds the types
  // we will encounter in this walk.
  // It should be empty at the beginning.
  // It maps from tree -> bool.
  // The boolean will be updated to show
  // whether a record is reachable from
  // the type.
  gcc_assert (ptr.empty ());
  walk (t);
}

// Make sure partitions are mutually exclusive.
void
TypeCollector::_sanity_check ()
{
  for (tset_t::iterator i = ptrset.points_to_record.begin (),
	    e = ptrset.points_to_record.end ();
       i != e; ++i)
    {
      for (tset_t::iterator j = ptrset.complement.begin (),
	    f = ptrset.complement.end ();
	   j != f; ++j)
	{
	  const_tree type_ptr = *i;
	  gcc_assert (type_ptr);
	  const_tree type_com = *j;
	  gcc_assert (type_com);
	  const bool valid_sets = type_ptr != type_com;
	  if (valid_sets)
	    continue;

	  // Normally, we want a stronger type comparison
	  // that is not just the pointer address
	  // but this is the first sanity check and then we will need to
	  // determine the stronger type comparison.  But first we will need to
	  // fix the types...
	  gcc_unreachable ();
	}
    }
}

/* Determine if T is already memoized in the TypeCollector.  */
bool
TypeCollector::is_memoized (const_tree t)
{
  /* If we haven't seen it then no.  */
  const bool in_set = ptrset.in_universe (t);
  if (!in_set)
    return false;

  // If the memoized type points to a record
  // we must update all types that can refer
  // to memoized type.
  const bool points_to_record = ptrset.in_points_to_record (t);
  for (std::map<const_tree, bool>::iterator i = ptr.begin (),
	e = ptr.end (); i != e; ++i)
    {
      i->second |= points_to_record;
    }
  return true;
}

void
TypeCollector::_walk_VOID_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_VOID_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_INTEGER_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_INTEGER_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_REAL_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_REAL_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_FIXED_POINT_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_FIXED_POINT_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_COMPLEX_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_COMPLEX_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_ENUMERAL_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_ENUMERAL_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_BOOLEAN_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_BOOLEAN_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_collect_simple (const_tree t)
{
  // Insert into persistent set.
  ptrset.insert (t, ptr[t]);
  // erase from current working set.
  ptr.erase (t);
}

void
TypeCollector::_walk_ARRAY_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_ARRAY_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_POINTER_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_POINTER_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_REFERENCE_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_REFERENCE_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_RECORD_TYPE_post (const_tree t)
{
  // All in ptr point to record
  for (std::map<const_tree, bool>::iterator i = ptr.begin (),
	e = ptr.end (); i != e; ++i)
    {
      i->second = true;
    }
  _collect_simple (t);

}

void
TypeCollector::_walk_RECORD_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_UNION_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_UNION_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_FUNCTION_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_FUNCTION_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

void
TypeCollector::_walk_METHOD_TYPE_post (const_tree t)
{
  _collect_simple (t);
}

void
TypeCollector::_walk_METHOD_TYPE_pre (const_tree t)
{
  ptr[t] = false;
}

inline void
ExprCollector::_walk_pre (const_tree e)
{
  if (!e) return;
  const_tree t = TREE_TYPE (e);
  gcc_assert (t);
  typeCollector.collect (t);

  if (RECORD_TYPE != TREE_CODE (t)) return;

  if (typeCollector.ptrset.records.empty ()) {
    typeCollector.ptrset.records.insert (TYPE_MAIN_VARIANT (t));
    return;
  }

  for (std::set<const_tree>::iterator
	i = typeCollector.ptrset.records.begin (),
	e = typeCollector.ptrset.records.end (); i != e; ++i)
  {
    const_tree r = *i;
    TypeIncompleteEquality structuralEquality;
    bool is_same = structuralEquality.equal (TYPE_MAIN_VARIANT (r), TYPE_MAIN_VARIANT (t));
    if (is_same) continue;

    TypeStringifier stringifier;
    typeCollector.ptrset.records.insert (TYPE_MAIN_VARIANT (t));
  }
}

/*
 * For global variables T, this method will collect
 * and partition trees corresponding to types
 * into std::sets.  Concretely speaking, this class
 * partitions trees into two sets:
 * * reach a RECORD_TYPE
 * * does not reach a RECORD_TYPE.
 */
void
GimpleTypeCollector::_walk_pre_tree (const_tree t)
{
  if (!t) return;
  exprCollector.walk (t);
}

/*
 * For assignment statements S, this method will collect
 * and partition trees corresponding to types
 * into std::sets.  Concretely speaking, this class
 * partitions trees into two sets:
 * * reach a RECORD_TYPE
 * * does not reach a RECORD_TYPE
 * The types reachable from the lhs and rhs are placed
 * in these sets.
 */
void
GimpleTypeCollector::_walk_pre_gassign (gassign *s)
{
  const_tree lhs = gimple_assign_lhs (s);
  exprCollector.walk (lhs);

  const enum gimple_rhs_class gclass = gimple_assign_rhs_class (s);
  switch (gclass)
    {
    case GIMPLE_TERNARY_RHS:
      {
	const_tree rhs = gimple_assign_rhs3 (s);
	exprCollector.walk (rhs);
      }
    /* fall-through */
    case GIMPLE_BINARY_RHS:
      {
	const_tree rhs = gimple_assign_rhs2 (s);
	exprCollector.walk (rhs);
      }
    /* fall-through */
    case GIMPLE_UNARY_RHS:
    case GIMPLE_SINGLE_RHS:
      {
	const_tree rhs = gimple_assign_rhs1 (s);
	exprCollector.walk (rhs);
      }
      break;
    default:
      gcc_unreachable ();
      break;
    }
}

void
GimpleTypeCollector::_walk_pre_greturn (greturn *s)
{
  const_tree retval = gimple_return_retval (s);
  if (!retval)
    return;

  exprCollector.walk (retval);
}

void
GimpleTypeCollector::_walk_pre_gcall (gcall *s)
{
  // Walk over the arguments.
  unsigned n = gimple_call_num_args (s);
  for (unsigned i = 0; i < n; i++)
    {
      const_tree a = gimple_call_arg (s, i);
      exprCollector.walk (a);
    }

  // Walk over the return type if it exists.
  const_tree lhs = gimple_call_lhs (s);
  if (!lhs)
    return;

  exprCollector.walk (lhs);
}

void
GimpleTypeCollector::_walk_pre_gdebug (gdebug *s)
{
  if (!gimple_debug_bind_p(s)) return;
  tree var = gimple_debug_bind_get_var(s);
  if (var) {
	  gcc_assert(TREE_TYPE(var));
	  exprCollector.walk(var);
  }
}

// Print working set.
void
GimpleTypeCollector::print_collected ()
{
  tpartitions_t sets = get_record_reaching_trees ();
}

/* Walk over LHS and RHS of conditions.  */
void
GimpleTypeCollector::_walk_pre_gcond (gcond *s)
{
  const_tree lhs = gimple_cond_lhs (s);
  exprCollector.walk (lhs);
  const_tree rhs = gimple_cond_rhs (s);
  exprCollector.walk (rhs);
}

bool
TypeEscaper::is_memoized (__attribute__ ((unused)) const_tree t)
{
  // Can't memoize here because
  // information is propagated up and down
  // the type.
  return false;
}

tpartitions_t
TypeEscaper::get_sets ()
{
  place_escaping_types_in_set ();
  return _ptrset;
}

/* From a map of TREE -> BOOL, the key represents a tree type
 * and the value represents whether the tree escapes.
 * Partition this map into sets.
 */
void
TypeEscaper::place_escaping_types_in_set ()
{
  TypeStringifier stringifier;
  for (typemap::iterator i = calc.begin (), e = calc.end (); i != e; ++i)
    {
      const_tree type = i->first;

      // We should only track interesting types
      // Types which are not in points_to_record are the ones
      // that are pointed to by records.
      // I think it is possible to prune them ahead of time...
      if (!_ptrset.in_points_to_record (type))
	continue;

      const Reason reason = i->second;
      reason.is_escaping () ? _ptrset.escaping.insert (type)
			    : _ptrset.non_escaping.insert (type);
    }
}

void
TypeEscaper::update (const_tree t, Reason r)
{
  gcc_assert (t);
  _reason = r;
  walk (t);
}

void
TypeEscaper::_update (const_tree t)
{
  gcc_assert (t);
  const bool already_in_typemap = calc.find (t) != calc.end ();
  // Do we have to invalidate all types which point to a volatile type?
  // Or do we have to invalidate all types pointed to by a volatile type?
  // Or do we only invalidate all types which are volatile.
  // This is only the third option.
  const bool is_volatile = TYPE_VOLATILE (t);
  Reason _is_volatile;
  _is_volatile.type_is_volatile = is_volatile;
  Reason _inner = _reason | _is_volatile;
  // always OR
  already_in_typemap ? calc[t] |= _inner : calc[t] = _inner;
}

void
TypeEscaper::_walk_ARRAY_TYPE_pre (const_tree t)
{
  _update (t);
}

void
TypeEscaper::_walk_ARRAY_TYPE_post (const_tree t)
{
  _update (t);
}

void
TypeEscaper::_walk_POINTER_TYPE_pre (const_tree t)
{
  _update (t);
}

void
TypeEscaper::_walk_POINTER_TYPE_post (const_tree t)
{
  _update (t);
}

void
TypeEscaper::_walk_REFERENCE_TYPE_pre (const_tree t)
{
  _update (t);
}

void
TypeEscaper::_walk_RECORD_TYPE_pre (const_tree t)
{
  // we are entering a record
  _inside_record++;
  _update (t);
}

void
TypeEscaper::_walk_RECORD_TYPE_post (const_tree t)
{
  _update (t); // This is in case there was a union
  // we are exiting a record
  _inside_record--;
}

/* Mark as escaping because of union
 * and propagate up and down.
 */
void
TypeEscaper::_walk_UNION_TYPE_pre (const_tree t)
{
  _inside_union++;
  bool is_escaping = _inside_union > 0;
  _reason.type_is_in_union |= is_escaping;
  _update (t);
}

/* Mark bit fields as escaping and propagate up
 * and down.
 */
void
TypeEscaper::_walk_field_pre (const_tree t)
{
  _reason.type_is_in_union |= DECL_BIT_FIELD (t);
}

void
TypeEscaper::_walk_UNION_TYPE_post (const_tree t)
{
  _inside_union--;
  _update (t);
}

/* Mark as escaping because RECORD has a function pointer
 * propagate up and down.
 */
void
TypeEscaper::_walk_FUNCTION_TYPE_pre (__attribute__ ((unused)) const_tree t)
{
  _reason.type_is_in_union |= _inside_record > 0;
}

/* Mark as escaping because RECORD has a function pointer
 * propagate up and down.
 */
void
TypeEscaper::_walk_METHOD_TYPE_pre (__attribute__ ((unused)) const_tree t)
{
  _reason.type_is_in_union |= _inside_record > 0;
}

/* Print escaping reasons.  */
void
TypeEscaper::print_reasons ()
{
  TypeStringifier stringifier;
  for (typemap::iterator i = calc.begin (), e = calc.end (); i != e; ++i)
    {
      const_tree t = i->first;
      std::string name = stringifier.stringify (t);
      Reason r = i->second;
      log ("%s reason: ", name.c_str ());
      r.print ();
    }
}

tpartitions_t
ExprEscaper::get_sets ()
{
  return typeEscaper.get_sets ();
}

void
ExprEscaper::print_reasons ()
{
  typeEscaper.print_reasons ();
}

/* Propagate reason to subexpressions.  */
void
ExprEscaper::update (const_tree t, Reason r)
{
  gcc_assert (t);
  _r = r;
  walk (t);
}

/* Propagate reason to type of subexpressions.  */
void
ExprEscaper::_walk_pre (const_tree e)
{
  _stack.push (e);
  const_tree t = TREE_TYPE (e);

  gcc_assert (t);
  typeEscaper.update (t, _r);
}

void
ExprEscaper::_walk_post (__attribute__ ((unused)) const_tree e)
{
  _stack.pop ();
}

/* Capture casting on LHS.  */
void
ExprEscaper::_walk_SSA_NAME_pre (const_tree e)
{
  const_tree ssa_type = TREE_TYPE (e);

  if (_stack.size () < 4)
    return;

  // TODO:
  // It appears that we have a bug, where we are
  // storing expressions twice on the stack
  const_tree this_expr = _stack.top ();
  _stack.pop ();
  const_tree twice = _stack.top ();
  _stack.pop ();
  const_tree prev_expr = _stack.top ();
  _stack.push (twice);
  _stack.push (this_expr);
  if (TREE_CODE (prev_expr) != MEM_REF)
    return;

  tree op1 = TREE_OPERAND (prev_expr, 1);
  gcc_assert (TREE_CODE (op1) == INTEGER_CST);
  const_tree mref_type = TREE_TYPE (op1);

  Reason old_reason = _r;
  TypeIncompleteEquality structuralEquality;
  // we need to make sure that both of them point to structs?
  if (TREE_CODE (TREE_TYPE (mref_type)) == INTEGER_TYPE)
    return;

  _r.type_is_casted = !structuralEquality.equal (mref_type, ssa_type);
  typeEscaper.update (mref_type, _r);
  typeEscaper.update (ssa_type, _r);
  _r = old_reason;
}

/* Mark constructors as escaping.  */
void
ExprEscaper::_walk_CONSTRUCTOR_pre (const_tree e)
{
  if (TREE_CLOBBER_P (e))
    return;

  // TODO: Instead of overloading global_is_visible field
  // with has a constructor, make a field that denotes that
  // a this has a constructor.
  // Or better yet... modify the constructors!
  _r.global_is_visible = true;
  const_tree t = TREE_TYPE (e);
  typeEscaper.update (t, _r);
}

tpartitions_t
GimpleEscaper::get_sets ()
{
  return exprEscaper.get_sets ();
}

void
GimpleEscaper::print_reasons ()
{
  exprEscaper.print_reasons ();
}

/* Initialize undefined set of functions.  */
void
GimpleEscaper::_init ()
{
  cgraph_node *cnode = NULL;
  FOR_EACH_FUNCTION (cnode)
    {
      gcc_assert (cnode);
      const bool filter = GimpleEscaper::filter_known_function (cnode);
      if (filter)
	continue;

      const_tree decl = cnode->decl;
      gcc_assert (decl);
      undefined.insert (decl);
    }

  FOR_EACH_FUNCTION_WITH_GIMPLE_BODY (cnode)
    {
      gcc_assert (cnode);
      cnode->get_untransformed_body ();
      const_tree decl = cnode->decl;
      gcc_assert (decl);
      undefined.erase (decl);
    }
}

/* Mark cnode graphs escaping if they are externally visible.  */
bool
GimpleEscaper::is_function_escaping (cgraph_node *cnode)
{
  const bool filter = GimpleEscaper::filter_known_function (cnode);
  if (filter)
    return false;

  return cnode->externally_visible;
}

/* Mark fndecl as escaping is they are externally visible or
 * there is no fndecl.  */
bool
GimpleEscaper::is_function_escaping (const_tree fndecl)
{
  if (!fndecl)
    return true;

  if (!TREE_PUBLIC (fndecl) && !DECL_EXTERNAL (fndecl))
    return false;

  return true;
}

/* Mark variable as escaping if it is externally visible.  */
bool
GimpleEscaper::is_variable_escaping (varpool_node *vnode)
{
  gcc_assert (vnode);
  const bool retval = vnode->externally_visible;
  const bool retval2 = vnode->externally_visible_p ();
  log("%s externally_visible = %d %d\n", vnode->name (), retval, retval2);
  return retval;
}

/* Walk global variable VNODE.  */
void
GimpleEscaper::_walk_global (varpool_node *vnode)
{
  gcc_assert (vnode);
  const_tree var_decl = vnode->decl;
  Reason reason;
  const bool is_escaping = is_variable_escaping (vnode);
  reason.global_is_visible = is_escaping;

  // TODO: Instead of overloading the semantic meaning of global is visible
  // make different fields for CONSTRUCTOR and for CONSTRUCTOR is not in linking
  // unit
  // TODO: Once we are able to rewrite the CONSTRUCTOR we can get rid of marking
  // types with bracket constructors as illegal.
  tree initial = DECL_INITIAL (var_decl);
  const bool constructor = initial ? TREE_CODE (initial) == CONSTRUCTOR : false;
  const bool error_mark = initial ? TREE_CODE (initial) == ERROR_MARK : false;
  reason.global_is_visible
    |= constructor || error_mark; // static initialization...

  exprEscaper.update (var_decl, reason);
  GimpleWalker::_walk_global (vnode);
}

/* Return true if FNDECL is a known function.  */
bool
GimpleEscaper::filter_known_function (const_tree fndecl)
{
  assert_is_type (fndecl, FUNCTION_DECL);
  if (fndecl_built_in_p (fndecl))
    {
      switch (DECL_FUNCTION_CODE (fndecl))
	{
	case BUILT_IN_FREE:
	case BUILT_IN_MALLOC:
	case BUILT_IN_REALLOC:
	case BUILT_IN_CALLOC:
	case BUILT_IN_MEMSET:
	  return true;
	  break;
	default:
	  break;
	}
    }

  return false;
}

/* Return True if NODE points to a known FUNCTION_DECL.  */
bool
GimpleEscaper::filter_known_function (cgraph_node *node)
{
  if (!node)
    return false;
  return filter_known_function (node->decl);
}

/* Mark Variable declaration of unknown location as escaping.  */
void
GimpleEscaper::_walk_pre_tree (const_tree t)
{
  // Is any global variable escaping?
  Reason reason;
  if (TREE_CODE (t) == VAR_DECL)
    {
      if (DECL_SOURCE_LOCATION (t) == UNKNOWN_LOCATION)
	// Detecting some builtin types
	// I think fprofile-generate inserts some builtin types which
	// cannot be detected in any other way...
	// TODO: Maybe add a new reason instead of overloading is_indirect.
	reason.is_indirect = true;
    }
  exprEscaper.update (t, reason);
}

void
GimpleEscaper::_walk_pre_gassign (gassign *s)
{
  Reason reason;
  const enum gimple_rhs_class code = gimple_assign_rhs_class (s);
  switch (code)
    {
    case GIMPLE_TERNARY_RHS:
      {
	const_tree rhs3 = gimple_assign_rhs3 (s);
	exprEscaper.update (rhs3, reason);
      }
    /* fall-through */
    case GIMPLE_BINARY_RHS:
      {
	const_tree rhs2 = gimple_assign_rhs2 (s);
	exprEscaper.update (rhs2, reason);
      }
    /* fall-through */
    case GIMPLE_UNARY_RHS:
    case GIMPLE_SINGLE_RHS:
      {
	const_tree rhs1 = gimple_assign_rhs1 (s);
	exprEscaper.update (rhs1, reason);
	const_tree lhs = gimple_assign_lhs (s);
	if (!lhs)
	  break;
	exprEscaper.update (lhs, reason);
      }
      break;
    default:
      gcc_unreachable ();
      break;
    }
}

void
GimpleEscaper::_walk_pre_greturn (greturn *s)
{
  Reason reason;
  const_tree val = gimple_return_retval (s);
  if (!val)
    return;
  exprEscaper.update (val, reason);
}

void
GimpleEscaper::_walk_pre_gcond (gcond *s)
{
  Reason reason;
  const_tree lhs = gimple_cond_lhs (s);
  const_tree rhs = gimple_cond_rhs (s);
  gcc_assert (lhs && rhs);
  exprEscaper.update (lhs, reason);
  exprEscaper.update (rhs, reason);
}

void
GimpleEscaper::_walk_pre_gcall (gcall *s)
{
  const_tree fn = gimple_call_fndecl (s);
  // gcc_assert (fn);
  // The above will not always be true
  // It will be false when we have an indirect function
  cgraph_node *node = fn ? cgraph_node::get (fn) : NULL;
  TypeStringifier stringifier;
  const bool _is_function_escaping
    = node ? is_function_escaping (node) : is_function_escaping (fn);
  const bool is_undefined = undefined.find (fn) != undefined.end ();
  log ("is undefined %s\n", is_undefined ? "t" : "f");
  const bool _is_escaping = is_undefined || _is_function_escaping;

  Reason arg_reason;
  arg_reason.parameter_is_visible = _is_escaping;
  arg_reason.is_indirect = !fn;
  unsigned n = gimple_call_num_args (s);
  for (unsigned i = 0; i < n; i++)
    {
      const_tree a = gimple_call_arg (s, i);
      gcc_assert (a);
      if (arg_reason.is_escaping ())
	{
	  std::string name = stringifier.stringify (TREE_TYPE (a));
	  log ("escaping parameter %s\n", name.c_str ());
	}
      exprEscaper.typeEscaper.update (TREE_TYPE (a), arg_reason);
    }

  const_tree lhs = gimple_call_lhs (s);
  if (!lhs)
    return;
  Reason return_reason;
  return_reason.return_is_visible = _is_escaping;
  return_reason.is_indirect = !fn;
  exprEscaper.update (lhs, return_reason);
}

/* Determine if cast comes from a known function.
 * Do this by following the use-def chain.  */
bool
GimpleCaster::follow_def_to_find_if_really_cast (const_tree rhs)
{
  gimple *def_for_rhs = SSA_NAME_DEF_STMT (rhs);
  gcall *is_call = dyn_cast<gcall *> (def_for_rhs);
  if (!is_call)
    return true;

  const_tree fn = gimple_call_fndecl (is_call);
  if (!fn)
    return true;

  bool known_function = GimpleEscaper::filter_known_function (fn);
  return !known_function;
}

void
GimpleCaster::_walk_pre_gassign (gassign *s)
{
  const enum gimple_rhs_class code = gimple_assign_rhs_class (s);
  const bool valid_input = GIMPLE_SINGLE_RHS == code;
  if (!valid_input)
    return;

  // I originally was using gimple_assign_cast_p
  // but that proved to be insufficient...
  // So we have to use our equality comparison...
  TypeIncompleteEquality equality;
  const_tree lhs = gimple_assign_lhs (s);
  const_tree rhs = gimple_assign_rhs1 (s);
  gcc_assert (lhs && rhs);
  Reason reason;
  const_tree t_lhs = TREE_TYPE (lhs);
  const_tree t_rhs = TREE_TYPE (rhs);
  gcc_assert (t_lhs && t_rhs);
  bool is_cast = !equality.equal (TYPE_MAIN_VARIANT(t_lhs), TYPE_MAIN_VARIANT(t_rhs));
  // If it is cast, we might need to look at the definition of rhs
  // If the definition comes from a known function... then we are good...
  bool is_ssa = TREE_CODE (rhs) == SSA_NAME;
  is_cast = is_cast && is_ssa ? follow_def_to_find_if_really_cast (rhs) : is_cast;
  // we allow casts to pointers...
  is_cast = is_cast && !(t_lhs == ptr_type_node);


  reason.type_is_casted = is_cast;
  bool in_map = _whitelisted.find (currently_walking->decl) != _whitelisted.end ();
  bool whitelisted = in_map && _whitelisted[currently_walking->decl];
  if (whitelisted) goto escaper_label;
  if (!flag_ipa_type_escape_analysis_keep_casts)
    exprEscaper.typeEscaper.update (TREE_TYPE (lhs), reason);
  if (!flag_ipa_type_escape_analysis_keep_casts)
    exprEscaper.typeEscaper.update (TREE_TYPE (rhs), reason);

escaper_label:
  GimpleEscaper::_walk_pre_gassign (s);
}

/* Check to see if arguments are casted.  */
void
GimpleCaster::_walk_pre_gcall (gcall *s)
{
  GimpleEscaper::_walk_pre_gcall (s);
  if (flag_ipa_type_escape_analysis_keep_casts)
    return;

  tree fn = gimple_call_fndecl (s);
  // If there's no function declaration, how do we
  // know the argument types?
  if (!fn)
    return;

  cgraph_node *node = cgraph_node::get (fn);
  const bool known_function = GimpleEscaper::filter_known_function (node)
			      || GimpleEscaper::filter_known_function (fn);
  if (known_function)
    return;

  if (_whitelisted.find(fn) != _whitelisted.end() && _whitelisted[fn]) return;
  bool in_map = _whitelisted.find(currently_walking->decl) != _whitelisted.end();
  bool whitelisted = in_map && _whitelisted[currently_walking->decl];
  if (whitelisted) return;

  if (!currently_walking->callers) return;

  if (!node && currently_walking->inlined_to) return;

  const_tree f_t = TREE_TYPE (fn);
  TypeIncompleteEquality equality;

  unsigned i = 0;
  TypeStringifier stringifier;
  for (tree a = TYPE_ARG_TYPES (f_t); NULL_TREE != a; a = TREE_CHAIN (a))
    {
      const_tree formal_t = TREE_VALUE (a);
      //if (formal_t == ptr_type_node) continue;
      //if (formal_t == void_type_node) continue;
      // There seems to be a final VOID_TYPE at the end of some functions?
      const enum tree_code code = TREE_CODE (formal_t);
      const bool is_void = VOID_TYPE == code;
      if (is_void)
	continue;

      const_tree real = gimple_call_arg (s, i);
      const_tree real_t = TREE_TYPE (real);
      const bool is_casted = !equality.equal (formal_t, real_t);
      log("arg %s is casted: %s\n", stringifier.stringify(real_t).c_str(), is_casted ? "T" : "F");
      Reason arg_reason;
      arg_reason.type_is_casted = is_casted;
      exprEscaper.typeEscaper.update (TREE_TYPE (real), arg_reason);
      i++;
    }

  const_tree lhs = gimple_call_lhs (s);
  if (!lhs)
    return;

  const_tree r_t = TREE_TYPE (f_t);
  const_tree l_t TREE_TYPE (lhs);
  const bool is_casted = !equality.equal (r_t, l_t);
  Reason ret_reason;
  ret_reason.type_is_casted = is_casted;
  exprEscaper.update (lhs, ret_reason);
}

bool
TypeAccessor::is_memoized (const_tree t)
{
  return memoized_map.find (t) != memoized_map.end ();
}

/* Add all fields in struct to memoized map.  */
void
TypeAccessor::_walk_RECORD_TYPE_pre (const_tree t)
{
  add_all_fields_in_struct (t);
  memoized_map.insert (t);
}

/* Initialize all fields as neither read nor written.  */
void
TypeAccessor::add_all_fields_in_struct (const_tree t)
{
  const enum tree_code c = TREE_CODE (t);
  const bool is_record = RECORD_TYPE == c;
  if (!is_record)
    return;

  const bool record_already_in_map = _map.find (t) != _map.end ();
  field_access_map_t field_map;
  field_map = record_already_in_map ? _map[t] : field_map;

  // Let's add all fields to the field map as empty.
  for (tree field = TYPE_FIELDS (t); field; field = DECL_CHAIN (field))
    {
      const bool field_already_in_map_2
	= field_map.find (field) != field_map.end ();
      if (field_already_in_map_2)
	continue;
      field_map[field] = Empty;
    }

  _map[t] = field_map;
}

record_field_map_t
ExprAccessor::get_map ()
{
  return record_field_map;
}

void
ExprAccessor::add_all_fields_in_struct (const_tree t)
{
  _typeAccessor.walk (t);
}

void
ExprAccessor::_walk_pre (const_tree e)
{
  _stack.push (e);
  const_tree t = TREE_TYPE (e);
  add_all_fields_in_struct (t);
}

void
ExprAccessor::_walk_post (__attribute__ ((unused)) const_tree e)
{
  _stack.pop ();
}

void
ExprAccessor::update (const_tree e, unsigned access)
{
  _access = access;
  walk (e);
}

/* Check if we are accessing a field
 * through pointer arithmetic.  If this is happening
 * it is likely the result of an optimization.
 * Since we are not modifying these types of expressions yet
 * we must mark all fields leading to the accessed fields
 * as possibly READ.

 * TODO: If we modify this expression later on, we could
 * make our transformation more powerful and precise by
 * not marking all fields leading up to this one as possibly
 * read.
 */
void
ExprAccessor::_walk_ADDR_EXPR_pre (__attribute__ ((unused)) const_tree e)
{
  log ("expr accessor mem ref\n");
  log ("stack size = %d\n", _stack.size ());

  if (_stack.size () < 4)
    return;

  // TODO: Fix error with double pushing
  const_tree addr_expr = _stack.top ();
  _stack.pop ();
  const_tree twice = _stack.top ();
  _stack.pop ();
  const_tree prev_expr = _stack.top ();
  _stack.push (addr_expr);
  _stack.push (twice);
  log ("prev_expr code = %s\n", get_tree_code_name (TREE_CODE (prev_expr)));
  if (TREE_CODE (prev_expr) != MEM_REF)
    return;

  tree op_0 = TREE_OPERAND (addr_expr, 0);
  const_tree addr_expr_t = TREE_TYPE (op_0);

  TypeStringifier stringifier;
  std::string name = stringifier.stringify (addr_expr_t);
  log ("accessing a field through memref...? %s\n", name.c_str ());
  if (TREE_CODE (addr_expr_t) != RECORD_TYPE)
    return;

  // We are accessing a field of a record through pointer arithmetic...
  // So what field offset are we computing...
  const_tree mref_expr = prev_expr;
  tree offset = TREE_OPERAND (mref_expr, 1);
  gcc_assert (TREE_CODE (offset) == INTEGER_CST);
  tree type_size_tree = TYPE_SIZE_UNIT (addr_expr_t);
  int type_size_int = tree_to_shwi (type_size_tree);
  // TODO: Very recently inserted this assertion so we need to test this
  gcc_assert (type_size_int > 0);
  unsigned offset_int = tree_to_uhwi (offset) % type_size_int;
  // We need to get the field that corresponds to the offset_int
  const bool record_already_in_map
    = record_field_map.find (addr_expr_t) != record_field_map.end ();
  field_access_map_t field_map;
  field_map = record_already_in_map ? record_field_map[addr_expr_t] : field_map;

  tree field = NULL;
  for (field = TYPE_FIELDS (addr_expr_t); field; field = DECL_CHAIN (field))
    {
      log ("ever inside?\n");
      // This is a weird result...
      unsigned f_byte_offset = tree_to_uhwi (DECL_FIELD_OFFSET (field));
      unsigned f_bit_offset = tree_to_uhwi (DECL_FIELD_BIT_OFFSET (field)) / 8;
      unsigned f_offset = f_byte_offset + f_bit_offset;
      // unsigned f_offset = bitpos_of_field (field);
      log ("offset field %d %d, offset by pointer %d \n ", f_offset,
	   f_bit_offset, offset_int);

      // NOTE: ALL FIELDS BEFORE THIS ONE NEED TO EXIST
      // Otherwise, this pointer arithmetic is invalid...
      // After the transformation
      const bool field_already_in_map
	= field_map.find (field) != field_map.end ();
      unsigned prev_access = field_already_in_map ? field_map[field] : Empty;

      prev_access |= Read;
      field_map[field] = prev_access;
      add_all_fields_in_struct (addr_expr_t);
      record_field_map[addr_expr_t] = field_map;

      if (f_offset == offset_int)
	break;
    }
}

/* Find out if we are taking the address of a FIELD_DECL.
 * If this is the case, it means that all FIELDS in this
 * RECORD_TYPE should be marked as READ for safety.
 */
void
ExprAccessor::_walk_COMPONENT_REF_pre (const_tree e)
{
  log ("in component_ref pre\n");
  assert_is_type (e, COMPONENT_REF);
  const_tree op0 = TREE_OPERAND (e, 0);
  gcc_assert (op0);
  const_tree op0_t = TREE_TYPE (op0);
  gcc_assert (op0_t);
  // op0_t can either be a RECORD_TYPE or a UNION_TYPE.
  const enum tree_code code = TREE_CODE (op0_t);
  const bool is_record = RECORD_TYPE == code;
  const bool is_union = UNION_TYPE == code;
  const bool valid = is_record != is_union;
  gcc_assert (valid);

  const_tree op1 = TREE_OPERAND (e, 1);
  assert_is_type (op1, FIELD_DECL);
  log ("%s.%s\n", TypeStringifier::get_type_identifier (op0_t),
       TypeStringifier::get_field_identifier (op1));
  const bool record_already_in_map
    = record_field_map.find (op0_t) != record_field_map.end ();
  field_access_map_t field_map;
  field_map = record_already_in_map ? record_field_map[op0_t] : field_map;
  const bool field_already_in_map = field_map.find (op1) != field_map.end ();
  unsigned prev_access = field_already_in_map ? field_map[op1] : Empty;

  prev_access |= _access;
  field_map[op1] = prev_access;
  add_all_fields_in_struct (op0_t);
  record_field_map[op0_t] = field_map;

  if (_stack.size () < 4)
    return;

  const_tree this_expr = _stack.top ();
  _stack.pop ();
  const_tree twice = _stack.top ();
  _stack.pop ();
  const_tree prev_expr = _stack.top ();
  _stack.push (twice);
  _stack.push (this_expr);
  if (TREE_CODE (prev_expr) != ADDR_EXPR)
    return;

  log ("we are taking address of a component?\n");
  const_tree t = op0_t;
  if (TREE_CODE (t) != RECORD_TYPE)
    return;

  /* If we are taking the address of a component, we need to mark the whole
   * RECORD_TYPE as escaping due to pointer arithmetic.
   * TODO: Maybe add a flag to enable and disable this for debugging and
   * testing.
   */
  for (tree field = TYPE_FIELDS (t); field; field = DECL_CHAIN (field))
  {
      log ("ever inside?\n");
      const bool field_already_in_map
	= field_map.find (field) != field_map.end ();
      unsigned prev_access = field_already_in_map ? field_map[field] : Empty;

      prev_access |= Read;
      field_map[field] = prev_access;
      add_all_fields_in_struct (t);
      record_field_map[t] = field_map;
  }
}

/* Print results.  */
void
ExprAccessor::print_accesses ()
{
  for (std::map<const_tree, field_access_map_t>::const_iterator i
       = record_field_map.begin (),
       e = record_field_map.end ();
       i != e; ++i)
    {
      const_tree record = i->first;
      field_access_map_t field_map = i->second;
      for (std::map<const_tree, unsigned>::const_iterator j
	   = field_map.begin (),
	   f = field_map.end ();
	   j != f; ++j)
	{
	  const_tree field = j->first;
	  const std::string name_r
	    = TypeStringifier::get_type_identifier (record);
	  const std::string name_f
	    = TypeStringifier::get_field_identifier (field);
	  unsigned access = j->second;
	  log ("%s.%s = 0x%04x\n", name_r.c_str (), name_f.c_str (), access);
	}
    }
}

/* RECORD_TYPE -> (FIELD_DECL -> bitflag)
 * bitflag specifies if field is read, written or neither.
 */
record_field_map_t
GimpleAccesser::get_map ()
{
  return exprAccessor.get_map ();
}

void
GimpleAccesser::print_accesses ()
{
  exprAccessor.print_accesses ();
}

/* Mark RHS as Read and LHS as Write.  */
void
GimpleAccesser::_walk_pre_gassign (gassign *s)
{
  // There seems to be quite a bit of code duplication here...
  const enum gimple_rhs_class code = gimple_assign_rhs_class (s);
  switch (code)
    {
    case GIMPLE_TERNARY_RHS:
      {
	const_tree rhs3 = gimple_assign_rhs3 (s);
	gcc_assert (rhs3);
	exprAccessor.update (rhs3, Read);
      }
    /* fall-through */
    case GIMPLE_BINARY_RHS:
      {
	const_tree rhs2 = gimple_assign_rhs2 (s);
	gcc_assert (rhs2);
	exprAccessor.update (rhs2, Read);
      }
    /* fall-through */
    case GIMPLE_UNARY_RHS:
    case GIMPLE_SINGLE_RHS:
      {
	const_tree rhs1 = gimple_assign_rhs1 (s);
	exprAccessor.update (rhs1, Read);
	const_tree lhs = gimple_assign_lhs (s);
	if (!lhs)
	  break;
	exprAccessor.update (lhs, Write);
	break;
      }
    default:
      gcc_unreachable ();
      break;
    }
}

/* Mark RHS as Read and LHS as Written.  */
void
GimpleAccesser::_walk_pre_gcall (gcall *s)
{
  unsigned n = gimple_call_num_args (s);
  for (unsigned i = 0; i < n; i++)
    {
      const_tree a = gimple_call_arg (s, i);
      gcc_assert (a);
      exprAccessor.update (a, Read);
    }

  const_tree lhs = gimple_call_lhs (s);
  if (!lhs)
    return;
  exprAccessor.update (lhs, Write);
}

/* Mark as Read.  */
void
GimpleAccesser::_walk_pre_greturn (greturn *s)
{
  const_tree val = gimple_return_retval (s);
  if (!val)
    return;
  exprAccessor.update (val, Read);
}

/* Mark as Read.  */
void
GimpleAccesser::_walk_pre_gcond (gcond *s)
{
  const_tree lhs = gimple_cond_lhs (s);
  const_tree rhs = gimple_cond_rhs (s);
  gcc_assert (lhs && rhs);
  exprAccessor.update (lhs, Read);
  exprAccessor.update (rhs, Read);
}

/* Print Reasons why a type might be escaping.  */
void
Reason::print () const
{
  log ("e=%d g=%d p=%d r=%d c=%d v=%d u=%d i=%d\n", this->is_escaping (),
       this->global_is_visible, this->parameter_is_visible,
       this->return_is_visible, this->type_is_casted, this->type_is_volatile,
       this->type_is_in_union, this->is_indirect);
}

/* Or an escaping Reason.  */
Reason
Reason::operator| (const Reason &other)
{
  Reason retval;
  retval.global_is_visible = this->global_is_visible | other.global_is_visible;
  retval.parameter_is_visible
    = this->parameter_is_visible | other.parameter_is_visible;
  retval.return_is_visible = this->return_is_visible | other.return_is_visible;
  retval.type_is_casted = this->type_is_casted | other.type_is_casted;
  retval.type_is_volatile = this->type_is_volatile | other.type_is_volatile;
  retval.type_is_in_union = this->type_is_in_union | other.type_is_in_union;
  retval.is_indirect = this->is_indirect | other.is_indirect;
  return retval;
}

/* Or an escaping Reason.  */
Reason &
Reason::operator|= (const Reason &other)
{
  this->global_is_visible |= other.global_is_visible;
  this->parameter_is_visible |= other.parameter_is_visible;
  this->return_is_visible |= other.return_is_visible;
  this->type_is_casted |= other.type_is_casted;
  this->type_is_volatile |= other.type_is_volatile;
  this->type_is_in_union |= other.type_is_in_union;
  this->is_indirect |= other.is_indirect;
  return *this;
}

/* Insert TYPE into a partition depending on IN_POINTS_TO_RECORD.  */
void
type_partitions_s::insert (const_tree type, bool in_points_to_record)
{
  gcc_assert (type);
  this->universe.insert (type);
  in_points_to_record ? this->points_to_record.insert (type)
		      : this->complement.insert (type);
  const bool in_points_to_set = this->in_points_to_record (type);
  const bool in_complement = this->in_complement (type);
  const bool _xor = in_points_to_set != in_complement;
  // sanity check...
  gcc_assert (_xor);
}

/* Find out whether TYPE is already in universe.  */
bool
type_partitions_s::in_universe (const_tree type) const
{
  gcc_assert (type);
  const bool seen_before = this->universe.find (type) != this->universe.end ();
  return seen_before;
}

/* Find out whether TYPE is in points_to_record partition.  */
bool
type_partitions_s::in_points_to_record (const_tree type) const
{
  gcc_assert (type);
  const bool seen_before
    = this->points_to_record.find (type) != this->points_to_record.end ();
  return seen_before;
}

/* Find out whether TYPE is not in points to record partition.  */
bool
type_partitions_s::in_complement (const_tree type) const
{
  gcc_assert (type);
  const bool seen_before
    = this->complement.find (type) != this->complement.end ();
  return seen_before;
}

/* Stringify a type.  */
std::string
TypeStringifier::stringify (const_tree t)
{
  if (!dump_file)
    return std::string ("");
  _stringification.clear ();
  gcc_assert (t);
  if (detected_incompatible_syntax)
    return std::string ("");
  walk (t);
  return _stringification;
}

void
TypeStringifier::_walk_VOID_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_walk_INTEGER_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_walk_REAL_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_walk_FIXED_POINT_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_walk_COMPLEX_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_walk_OFFSET_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_walk_BOOLEAN_TYPE_pre (const_tree t)
{
  _stringify_simple (t);
}

void
TypeStringifier::_stringify_simple (const_tree t)
{
  gcc_assert (t);
  const enum tree_code code = TREE_CODE (t);
  this->_stringification += std::string (get_tree_code_name (code));
}

void
TypeStringifier::_walk_POINTER_TYPE_post (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string ("*");
}

void
TypeStringifier::_walk_ARRAY_TYPE_post (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string ("[]");
}

void
TypeStringifier::_walk_REFERENCE_TYPE_post (__attribute__ ((unused))
					    const_tree t)
{
  this->_stringification += std::string ("&");
}

void
TypeStringifier::_walk_UNION_TYPE_pre (const_tree t)
{
  this->_stringification += std::string (" union ");
  _stringify_aggregate_pre (t);
}

void
TypeStringifier::_walk_UNION_TYPE_post (const_tree t)
{
  _stringify_aggregate_post (t);
}

void
TypeStringifier::_walk_RECORD_TYPE_pre (const_tree t)
{
  this->_stringification += std::string (" record ");
  _stringify_aggregate_pre (t);
}

void
TypeStringifier::_walk_RECORD_TYPE_post (const_tree t)
{
  _stringify_aggregate_post (t);
}

void
TypeStringifier::_stringify_aggregate_pre (const_tree t)
{
  this->_stringification
    += TypeStringifier::get_type_identifier (t) + std::string (" {");
}

void
TypeStringifier::_stringify_aggregate_post (__attribute__ ((unused))
					    const_tree t)
{
  this->_stringification += std::string ("}");
}

void
TypeStringifier::_walk_field_post (const_tree t)
{
  this->_stringification += std::string (" ")
			    + TypeStringifier::get_field_identifier (t)
			    + std::string (";");
}

void
TypeStringifier::_walk_METHOD_TYPE_pre (const_tree t)
{
  _stringify_fm_pre (t);
}

void
TypeStringifier::_walk_METHOD_TYPE_post (const_tree t)
{
  _stringify_fm_post (t);
}

void
TypeStringifier::_walk_FUNCTION_TYPE_pre (const_tree t)
{
  _stringify_fm_pre (t);
}

void
TypeStringifier::_walk_FUNCTION_TYPE_post (const_tree t)
{
  _stringify_fm_post (t);
}

void
TypeStringifier::_stringify_fm_pre (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string ("function { ");
}

void
TypeStringifier::_stringify_fm_post (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string ("}");
}

void
TypeStringifier::_walk_return_pre (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string ("(");
}

void
TypeStringifier::_walk_return_post (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string (")");
}

void
TypeStringifier::_walk_args_pre (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string ("(");
}

void
TypeStringifier::_walk_args_post (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string (")");
}

void
TypeStringifier::_walk_arg_post (__attribute__ ((unused)) const_tree t)
{
  this->_stringification += std::string (", ");
}

std::string
TypeStringifier::get_type_identifier (const_tree t)
{
  if (detected_incompatible_syntax)
    return std::string ("");
  tree name = TYPE_NAME (t);
  bool no_name = NULL_TREE == name;
  if (no_name)
    return std::string ("");

  const enum tree_code name_code = TREE_CODE (name);
  const bool is_name_type_decl = TYPE_DECL == name_code;
  name = is_name_type_decl ? DECL_NAME (name) : name;
  no_name = NULL_TREE == name;
  if (no_name)
    return std::string ("");
  const char *identifier_ptr = IDENTIFIER_POINTER (name);
  gcc_assert (identifier_ptr);
  return std::string (identifier_ptr);
}

std::string
TypeStringifier::get_field_identifier (const_tree t)
{
  assert_is_type (t, FIELD_DECL);
  const_tree decl_name = DECL_NAME (t);
  if (!decl_name)
    return std::string ("");

  const char *identifier = IDENTIFIER_POINTER (decl_name);
  return std::string (identifier);
}

/* Return true if L and R have equal structural equalities.  */
bool
TypeStructuralEquality::equal (const_tree l, const_tree r)
{
  return _equal (l, r);
}

bool
TypeStructuralEquality::_equal (const_tree l, const_tree r)
{
  bool valid_inputs = l && r;
  if (!valid_inputs)
    return l == r;

  bool equal_codes = _equal_code (l, r);
  if (!equal_codes)
    return equal_codes;

  bool recurse_l = set_l.find (l) != set_l.end ();
  bool recurse_r = set_r.find (r) != set_r.end ();
  // Verify that this the case every time.
  bool recurse = recurse_l || recurse_r;
  if (recurse)
    return recurse;

  set_l.insert (l);
  set_r.insert (r);
  const enum tree_code code = TREE_CODE (l);
  bool equal_children = false;
  switch (code)
    {
#define TSE_CASE(code)				\
  case code:					\
    equal_children = _walk_##code (l, r);	\
    break

      TSE_CASE (VOID_TYPE);
      TSE_CASE (INTEGER_TYPE);
      TSE_CASE (REAL_TYPE);
      TSE_CASE (FIXED_POINT_TYPE);
      TSE_CASE (COMPLEX_TYPE);
      TSE_CASE (ENUMERAL_TYPE);
      TSE_CASE (BOOLEAN_TYPE);
      TSE_CASE (OFFSET_TYPE);
      TSE_CASE (RECORD_TYPE);
      TSE_CASE (POINTER_TYPE);
      TSE_CASE (REFERENCE_TYPE);
      TSE_CASE (ARRAY_TYPE);
      TSE_CASE (UNION_TYPE);
      TSE_CASE (FUNCTION_TYPE);
      TSE_CASE (METHOD_TYPE);
    default:
#ifdef ABORT_IF_NOT_C
	detected_incompatible_syntax = true;
	return false;
#else
	gcc_unreachable ();
#endif
      break;
    }

  set_l.erase (l);
  set_r.erase (r);
  return equal_children;
}

bool
TypeStructuralEquality::_equal_code (const_tree l, const_tree r)
{
  const enum tree_code code_l = TREE_CODE (l);
  const enum tree_code code_r = TREE_CODE (r);
  const bool equal = code_l == code_r;
  bool array_or_ptr_l = TREE_CODE (l) == ARRAY_TYPE
    || TREE_CODE (l) == POINTER_TYPE;
  bool array_or_ptr_r = TREE_CODE (r) == ARRAY_TYPE
    || TREE_CODE (r) == POINTER_TYPE;
  bool array_or_ptr = array_or_ptr_l && array_or_ptr_r;
  return equal || array_or_ptr;
}

#define TSE_FUNC_DEF_SIMPLE(code) 					  \
  bool TypeStructuralEquality::_walk_##code (const_tree l, const_tree r)  \
  {									  \
    return _equal_code (l, r);						  \
  }

TSE_FUNC_DEF_SIMPLE (VOID_TYPE)
TSE_FUNC_DEF_SIMPLE (INTEGER_TYPE)
TSE_FUNC_DEF_SIMPLE (REAL_TYPE)
TSE_FUNC_DEF_SIMPLE (FIXED_POINT_TYPE)
TSE_FUNC_DEF_SIMPLE (ENUMERAL_TYPE)
TSE_FUNC_DEF_SIMPLE (BOOLEAN_TYPE)
TSE_FUNC_DEF_SIMPLE (OFFSET_TYPE)
TSE_FUNC_DEF_SIMPLE (COMPLEX_TYPE)

bool
TypeStructuralEquality::_equal_wrapper (const_tree l, const_tree r)
{
  const_tree inner_l = TREE_TYPE (l);
  if (TREE_CODE (inner_l) == ARRAY_TYPE 
    && TREE_CODE (TREE_TYPE (inner_l)) == POINTER_TYPE ) 
  {
    inner_l = TREE_TYPE(inner_l);
  }
  const_tree inner_r = TREE_TYPE (r);
  if (TREE_CODE (inner_r) == ARRAY_TYPE
    && TREE_CODE(TREE_TYPE (inner_r)) == POINTER_TYPE )
  {
    inner_r = TREE_TYPE(inner_r);
  }
  return _equal (inner_l, inner_r);
}

#define TSE_FUNC_DEF_WRAPPER(code)					 \
  bool TypeStructuralEquality::_walk_##code (const_tree l, const_tree r) \
  {									 \
    return _equal_wrapper (l, r);					 \
  }

TSE_FUNC_DEF_WRAPPER (REFERENCE_TYPE)
TSE_FUNC_DEF_WRAPPER (ARRAY_TYPE)
TSE_FUNC_DEF_WRAPPER (POINTER_TYPE)

#define TSE_FUNC_DEF_CONTAINER(code)					 \
  bool TypeStructuralEquality::_walk_##code (const_tree l, const_tree r) \
  {									 \
    const_tree field_l = TYPE_FIELDS (l);				 \
    const_tree field_r = TYPE_FIELDS (r);				 \
    bool efield_l = field_l;						 \
    bool efield_r = field_r;						 \
    bool still_equal = efield_l == efield_r;				 \
    if (!still_equal) 							 \
      return still_equal; 						 \
									 \
    while (field_l && field_r && still_equal) 				 \
      {									 \
	const_tree tfield_l = TREE_TYPE (field_l);			 \
	const_tree tfield_r = TREE_TYPE (field_r);			 \
	still_equal &= _equal (tfield_l, tfield_r);			 \
	field_l = DECL_CHAIN (field_l);					 \
	field_r = DECL_CHAIN (field_r);					 \
	efield_l = field_l;						 \
	efield_r = field_r;						 \
	still_equal &= efield_l == efield_r;				 \
      }									 \
    return still_equal;							 \
  }

TSE_FUNC_DEF_CONTAINER (RECORD_TYPE)
TSE_FUNC_DEF_CONTAINER (UNION_TYPE)

#define TSE_FUNC_DEF_FUNC(code)						 \
  bool TypeStructuralEquality::_walk_##code (const_tree l, const_tree r) \
  {									 \
    const_tree tret_l = TREE_TYPE (l);					 \
    const_tree tret_r = TREE_TYPE (r);					 \
    bool still_equal = _equal (tret_l, tret_r);				 \
    if (!still_equal)							 \
      return still_equal;						 \
									 \
    const_tree arg_l = TYPE_ARG_TYPES (l);				 \
    const_tree arg_r = TYPE_ARG_TYPES (r);				 \
    bool earg_l = arg_l;						 \
    bool earg_r = arg_r;						 \
    still_equal &= earg_l == earg_r;					 \
    while (arg_l && arg_r && still_equal)				 \
      {									 \
	const_tree targ_l = TREE_VALUE (arg_l);				 \
	const_tree targ_r = TREE_VALUE (arg_r);				 \
	still_equal &= _equal (targ_l, targ_r);				 \
	arg_l = TREE_CHAIN (arg_l);					 \
	arg_r = TREE_CHAIN (arg_r);					 \
	earg_l = arg_l;							 \
	earg_r = arg_r;							 \
	still_equal &= earg_l == earg_r;				 \
      }									 \
    return still_equal;							 \
  }

TSE_FUNC_DEF_FUNC (FUNCTION_TYPE)
TSE_FUNC_DEF_FUNC (METHOD_TYPE)

/* Used for comparing incomplete types.  */
bool
TypeIncompleteEquality::_equal (const_tree l, const_tree r)
{
  bool valid_inputs = l && r;
  if (!valid_inputs)
    return l == r;

  // If any of these are incomplete, then we can only compare using
  // identifiers...
  const bool complete_l = is_complete (l);
  const bool complete_r = is_complete (r);
  bool can_compare_structurally = complete_l && complete_r;
  if (can_compare_structurally)
    return TypeStructuralEquality::_equal (l, r);

  // Before comparing with identifiers
  // make last attempt to compare using main variants.
  const_tree m_l = TYPE_MAIN_VARIANT (l);
  const_tree m_r = TYPE_MAIN_VARIANT (r);
  gcc_assert (m_l && m_r);
  can_compare_structurally = m_l == m_r;
  if (can_compare_structurally)
    return true;

  const std::string n_l = TypeStringifier::get_type_identifier (m_l);
  const std::string n_r = TypeStringifier::get_type_identifier (m_r);
  return n_l.compare (n_r) == 0;
}

/* Remove non-escaping types and place in escaping types if
 * there is a tree in escaping partition which is equivalent to
 * another tree in non-escaping partition.
 * Perform this until a fixed point is reached.
 */
static void
fix_escaping_types_in_set (tpartitions_t &types)
{
  bool fixed_point_reached = false;
  TypeIncompleteEquality structuralEquality;
  do
    {
      std::vector<const_tree> fixes;
      fixed_point_reached = true;
      for (std::set<const_tree>::const_iterator i = types.escaping.begin (),
						e = types.escaping.end ();
	   i != e; ++i)
	{
	  for (std::set<const_tree>::const_iterator j
	       = types.non_escaping.begin (),
	       f = types.non_escaping.end ();
	       j != f; ++j)
	    {
	      const_tree type_esc = *i;
	      gcc_assert (type_esc);
	      const_tree type_non = *j;
	      gcc_assert (type_non);
	      // There can be cases where incomplete types are marked as
	      // non-escaping and complete types counter parts are marked as
	      // escaping.
	      const bool equal = structuralEquality.equal (type_esc, type_non);
	      if (!equal)
		continue;

	      fixed_point_reached = false;
	      // Add incomplete to escaping
	      // delete incomplete from non_escaping
	      // We shouldn't do that inside our iteration loop.
	      fixes.push_back (type_non);
	    }
	}

      for (std::vector<const_tree>::const_iterator i = fixes.begin (),
						   e = fixes.end ();
	   i != e; ++i)
	{
	  const_tree escaping_type = *i;
	  types.escaping.insert (escaping_type);
	  types.non_escaping.erase (escaping_type);
	}
    }
  while (!fixed_point_reached);
}

simple_ipa_opt_pass *
make_pass_ipa_type_escape_analysis (gcc::context *ctx)
{
  return new pass_ipa_type_escape_analysis (ctx);
}

