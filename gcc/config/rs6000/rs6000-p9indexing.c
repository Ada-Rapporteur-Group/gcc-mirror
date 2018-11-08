/* Subroutines used to transform array subscripting expressions into
   forms that are more amenable to d-form instruction selection for p9
   little-endian VSX code.
   Copyright (C) 1991-2018 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "rtl.h"
#include "tree.h"
#include "memmodel.h"
#include "df.h"
#include "tm_p.h"
#include "ira.h"
#include "print-tree.h"
#include "varasm.h"
#include "explow.h"
#include "expr.h"
#include "output.h"
#include "tree-pass.h"
#include "rtx-vector-builder.h"
#include "cfgloop.h"

#include "insn-config.h"
#include "recog.h"

#include "print-rtl.h"
#include "tree-pretty-print.h"

#include "genrtl.h"

extern bool rs6000_debug_legitimate_address_p (machine_mode, rtx, bool);



/* This pass transforms array indexing expressions from a form that
   favors selection of X-form instructions into a form that favors
   selection of D-form instructions.

   Showing favor for D-form instructions is especially important when
   targeting Power9, as the Power9 architecture added a number of new
   D-form instruction capabilities.  */

/* This is based on the union-find logic in web.c.  web_entry_base is
   defined in df.h.  */
class indexing_web_entry : public web_entry_base
{
 public:
  rtx_insn *insn;		/* Pointer to the insn */
  basic_block bb;		/* Pointer to the enclosing basic block */

  /* If this insn is relevant, it is a load or store with a memory
     address that is comprised of a base pointer (e.g. the address of
     an array or array slice) and an index expression (e.g. an index
     within the array).  The original_base_use and original_index_use
     fields represent the numbers of the instructions that define the
     base and index values which are summed together with a constant
     value to determine the value of this instruction's memory
     address.  */
  unsigned int original_base_use;
  unsigned int original_index_use;

  /* If this insn is relevant, the register assigned by insn
     original_base_use is original_base_reg.  The insn assigned by insn
     original_index_use is original_index_reg.  */
  unsigned int original_base_reg;
  unsigned int original_index_reg;

  /* If this insn is_relevant, this is the constant that is added to
     the originating expression to calculate the value of this insn's
     memory address.  */
  int base_delta;
  int index_delta;

  /* If this insn is relevant, it belongs to an equivalence class.
     The equivalence classes are identified by the definitions that
     define the inputs to this insn.
   */
  unsigned int base_equivalence_hash;
  unsigned int index_equivalence_hash;

  /* When multiple insns fall within the same equivalence class, they
     are linked together through this field.  The value UINT_MAX
     represents the end of this list.  */
  unsigned int equivalent_sibling;

  unsigned int is_relevant: 1;
  unsigned int is_load: 1;
  unsigned int is_store: 1;
  unsigned int is_originating: 1;
};

static int count_links (struct df_link *def_link)
{
  if (def_link == NULL) return 0;
  else return 1 + count_links (def_link->next);
}

static int max_use_links = 0;

static int
help_hash (int count, struct df_link *def_link) {
  int *ids;
  int i = 0;

  if (count > max_use_links)
    max_use_links = count;

  ids = (int *) alloca (count * sizeof (int));
  while (def_link != NULL) {
    ids[i++] = DF_REF_ID (def_link->ref);
    def_link = def_link->next;
  }

  /* bubble sort to put ids in ascending order. */
  for (int end = count - 1; end > 0; end--) {
    for (int j = 0; j < end; j++) {
      if (ids[j] > ids[j+1]) {
	int swap = ids[j];
	ids[j] = ids[j+1];
	ids[j+1] = swap;
      }
    }  /* ids[end] has largest entry in ids[0..end]  */
  }

  int result = 0;
  for (int i = 0; i < count; i++)
    {
      result = (result << 6) | ((result & 0xf000000) >> 28);
      result += ids[i];

      /* kelvin debugging */
      if (dump_file)
	fprintf (dump_file, "calculating hash 0x%x, after adding in 0x%x\n",
		 result, ids[i]);

    }
  return result;
}

static int
equivalence_hash (struct df_link *def_link)
{
  int count = count_links (def_link);
  return help_hash (count, def_link);
}

static void
find_defs (indexing_web_entry *insn_entry, rtx_insn *insn,
	   struct df_link **insn_base, struct df_link **insn_index)
{
  unsigned int uid = INSN_UID (insn);
  rtx body = PATTERN (insn);
  rtx mem;
  if ((GET_CODE (body) == SET) && MEM_P (SET_SRC (body)))
    mem = XEXP (SET_SRC (body), 0);
  else if ((GET_CODE (body) == SET) && MEM_P (SET_DEST (body)))
    mem = XEXP (SET_DEST (body), 0);
  else
    mem = NULL;
  /* else, this insn is neither load nor store.  */

  if (mem != NULL)
    {
      enum rtx_code code = GET_CODE (mem);
      if ((code == PLUS) || (code == MINUS))
	{
	  rtx base_reg = XEXP (mem, 0);
	  rtx index_reg = XEXP (mem, 1);

	  if (REG_P (base_reg) && REG_P (index_reg))
	    {
	      struct df_insn_info *insn_info = DF_INSN_INFO_GET (insn);
	      df_ref use;
	      FOR_EACH_INSN_INFO_USE (use, insn_info)
		{
		  if (rtx_equal_p (DF_REF_REG (use), base_reg))
		    {
		      struct df_link *def_link = DF_REF_CHAIN (use);
		      /* if there is no def, or the def is artificial,
			 or there are multiple defs, this is an originating
			 use.  */
		      if (!def_link || !def_link->ref
			  || DF_REF_IS_ARTIFICIAL (def_link->ref)
			  || def_link->next)
			*insn_base = def_link;
		      else
			{
			  unsigned int uid2 =
			    insn_entry[uid].original_base_use;
			  df_ref use2;
			  if (uid2 > 0)
			    {
			      rtx_insn *insn2 = insn_entry[uid2].insn;
			      struct df_insn_info *insn_info2 =
				DF_INSN_INFO_GET (insn2);
			      use2 = DF_INSN_INFO_USES (insn_info2);
			      if (use2)
				*insn_base = DF_REF_CHAIN (use2);
			      else
				*insn_base = NULL;
			    }
			}
		    }
		  else if (rtx_equal_p (DF_REF_REG (use), index_reg))
		    {
		      struct df_link *def_link = DF_REF_CHAIN (use);
		      /* if there is no def, or the def is artificial,
			 or there are multiple defs, this is an originating
			 use.  */
		      if (!def_link || !def_link->ref
			  || DF_REF_IS_ARTIFICIAL (def_link->ref)
			  || def_link->next)
			*insn_index = def_link;
		      else
			{
			  unsigned int uid2 =
			    insn_entry[uid].original_index_use;
			  df_ref use2;
			  if (uid2 > 0)
			    {
			      rtx_insn *insn2 = insn_entry[uid2].insn;
			      struct df_insn_info *insn_info2 =
				DF_INSN_INFO_GET (insn2);
			      use2 = DF_INSN_INFO_USES (insn_info2);
			      if (use2)
				*insn_index = DF_REF_CHAIN (use2);
			      else
				*insn_index = NULL;
			    }
			}
		    }
		}
	    }
	}
    }
}

/* Return non-zero if an only if use represents a compile-time constant.  */
static int
represents_constant_p (df_ref use)
{
  struct df_link *def_link = DF_REF_CHAIN (use);

  /* If there is no definition, or the definition is
     artificial, or there are multiple definitions, this
     is an originating use.  */
  if (!def_link || !def_link->ref
      || DF_REF_IS_ARTIFICIAL (def_link->ref) || def_link->next)
    return false;
  else
    {
      rtx def_insn = DF_REF_INSN (def_link->ref);
      /* unsigned uid = INSN_UID (def_insn); not needed? */
      rtx body = PATTERN (def_insn);
      if (GET_CODE (body) == CONST_INT)
	return true;
      else if (GET_CODE (body) == SET)
	{
	  /* recurse on the use that defines this variable */
	  struct df_insn_info *inner_insn_info = DF_INSN_INFO_GET (def_insn);
	  df_ref inner_use;
	  FOR_EACH_INSN_INFO_USE (inner_use, inner_insn_info)
	    {
	      if (!represents_constant_p (inner_use))
		return false;
	    }
	  /* There were multiple defs but they are all constant.  */
	  return true;
	}
      else			/* treat unrecognized codes as not constant */
	return false;
    }
}


/* An originator represents the first point at which the value of
   DEF_LINK is derived from potentially more than one input
   definition, or the point at which DEF_LINK's value is defined by an
   algebraic expression involving only constants,

   If DEF_LINK's value depends on a constant combined with a single
   variable or a simple propagation of a single variable, continue
   the search for the originator by examining the origin of the source
   variable's value.

   The value of *ADJUSTMENT is overwritten with the constant value that is
   added to the originator expression to obtain the value intended to
   be represented by DEF_LINK.  In the case that find_true_originator
   returns NULL, the value held in *ADJUSTMENT is undefined.

   Returns NULL if there is no single true originator.  In general, the search
   for an originator expression only spans SET operations that are
   based on simple algebraic expressions, each of which involves no
   more than one variable input.  */
static rtx
find_true_originator (struct df_link *def_link, long long int *adjustment)
{
  rtx def_insn = DF_REF_INSN (def_link->ref);

  rtx inner_body = PATTERN (def_insn);
  if (GET_CODE (inner_body) == SET)
    {
      struct df_insn_info *inner_insn_info = DF_INSN_INFO_GET (def_insn);
      df_ref inner_use;

      /* We're only happy with multiple uses if all but one represent
	 constant values.  Below, we assure that  */
      int non_constant_uses = 0;
      rtx result = NULL;
      FOR_EACH_INSN_INFO_USE (inner_use, inner_insn_info)
	{
	  if (!represents_constant_p (inner_use))
	    {
	      non_constant_uses++;
	      /* There should be only one non-constant use, and it should
		 satisfy find_true_originator.  */
	      struct df_link *def_link = DF_REF_CHAIN (inner_use);

	      /* If there is no definition, or the definition is
		 artificial, or there are multiple definitions, this
		 is an originating use.  */
	      if (!def_link || !def_link->ref
		  || DF_REF_IS_ARTIFICIAL (def_link->ref) || def_link->next)
		result = def_insn;
	      else
		result = find_true_originator (def_link, adjustment);
	    }
	}

      /* If non_constant_uses > 1, the value of result is not well
	 defined because it is overwritten during multiple iterations
	 of the above loop.  But in the case that non_constant_uses >
	 1, we do not make use of the result value.  */
      if (non_constant_uses == 1) {

	/* If my SET looks like a simple register copy, or if it looks
	   like PLUS or MINUS of a constant and a register, this is
	   what we optimize.  Otherwise, punt.  */

	if (result == NULL)
	  /* Doing constant arithmetic with unknown originator is not
	     useful.  */
	  return def_insn;

	rtx source_expr = SET_SRC (inner_body);
	int source_code = GET_CODE (source_expr);
	if (source_code == PLUS)
	  {
	    rtx op1 = XEXP (source_expr, 0);
	    rtx op2 = XEXP (source_expr, 1);

	    if ((GET_CODE (op1) == CONST_INT) && (GET_CODE (op2) != CONST_INT))
	      *adjustment += INTVAL (op1);
	    else if ((GET_CODE (op1) != CONST_INT)
		     && (GET_CODE (op2) == CONST_INT))
	      *adjustment += INTVAL (op2);
	  }
	else if (source_code == MINUS)
	  {
	    rtx op1 = XEXP (source_expr, 0);
	    rtx op2 = XEXP (source_expr, 1);

	    if ((GET_CODE (op1) != CONST_INT) && (GET_CODE (op2) == CONST_INT))
	      *adjustment -= INTVAL (op1);
	    else		/* assumption is that *adjustment is
				   added to a positive variable
				   expression, so don't optimize this
				   rare condition.  */
	      result = def_insn;
	  }
	else if (source_code != REG)
	    /* We don't handle ashift, UNSPEC, etc..  */
	    result = def_insn;
	/* else, this is a register copy expression: no impact on
	   adjustment.  */

	return result;
      }
      else
	return def_insn;	/* Same behavior if there are
				   too many non-constant inputs,
				   or if all inputs are
				   constant.  */
    }
  else				/* This is not a SET operation, so it
				   does not serve as a true originator. */
    return NULL;
}

/* The size of the insn_entry array.  Note that this array does not
   represent instructions created during this optimization pass.  */
static unsigned int max_uid_at_start;

static bool
in_use_list (struct df_link *list, struct df_link *element)
{
  while (list != NULL)
    {
      /* kelvin debugging.  */
      if (dump_file) {
	fprintf (dump_file, " against definition %d\n",
		 DF_REF_ID(list->ref));
      }

      if (element->ref == list->ref)
	return true;
      list = list->next;
    }

  /* kelvin debugging.  */
  if (dump_file) {
    fprintf (dump_file, " No joy!\n");
  }

  /* Got to end of list without finding element.  */
  return false;
}

/* Return true iff the instruction represented by uid_1 is in the same
   equivalence class as the instruction represented by uid_2.  */
static bool
equivalent_p (indexing_web_entry *insn_entry,
	      unsigned int uid_1, unsigned int uid_2)
{
  /* kelvin debugging */
  if (dump_file) {
    fprintf (dump_file, "testing equivalence of insn %d and insn %d\n",
	     uid_1, uid_2);
    fprintf (dump_file, " uid %d base_hash: %d, index_hash: %d\n", uid_1,
	     insn_entry[uid_1].base_equivalence_hash,
	     insn_entry[uid_1].index_equivalence_hash);
    fprintf (dump_file, " uid %d base_hash: %d, index_hash: %d\n", uid_2,
	     insn_entry[uid_2].base_equivalence_hash,
	     insn_entry[uid_2].index_equivalence_hash);
  }

  if ((insn_entry[uid_1].base_equivalence_hash !=
       insn_entry[uid_2].base_equivalence_hash) ||
      (insn_entry[uid_1].index_equivalence_hash !=
       insn_entry[uid_2].index_equivalence_hash))
    return false;
  else				/* Hash codes match.  Check details.  */
    {
      rtx_insn *insn_1, *insn_2;
      insn_1 = insn_entry[uid_1].insn;
      insn_2 = insn_entry[uid_2].insn;

      struct df_link *insn1_base_defs, *insn1_index_defs;
      struct df_link *insn2_base_defs, *insn2_index_defs;

      find_defs (insn_entry, insn_1, &insn1_base_defs, &insn1_index_defs);
      find_defs (insn_entry, insn_2, &insn2_base_defs, &insn2_index_defs);

      int base_count_1 = count_links (insn1_base_defs);
      int index_count_1 = count_links (insn1_index_defs);
      int base_count_2 = count_links (insn2_base_defs);
      int index_count_2 = count_links (insn2_index_defs);

      if ((base_count_1 != base_count_2) || (index_count_1 != index_count_2))
	return false;

      /* kelvin debugging.  */
      if (dump_file) {
	fprintf (dump_file, "base_count: %d, index_count: %d\n",
		 base_count_1, index_count_1);
      }

      /* Counts are the same.  Make sure elements match.   */
      while (insn1_base_defs != NULL)
	{

	  /* kelvin debugging.  */
	  if (dump_file) {
	    fprintf (dump_file, "checking base definition %d\n",
		     DF_REF_ID(insn1_base_defs->ref));
	  }

	  if (!in_use_list (insn2_base_defs, insn1_base_defs))
	    return false;
	  insn1_base_defs = insn1_base_defs->next;
	}
      /* base patterns match, but stil need to consider index matches.  */
      while (insn1_index_defs != NULL)
	{
	  /* kelvin debugging.  */
	  if (dump_file) {
	    fprintf (dump_file, "checking index definition %d\n",
		     DF_REF_ID(insn1_index_defs->ref));
	  }

	  if (!in_use_list (insn2_index_defs, insn1_index_defs))
	    return false;
	  insn1_index_defs = insn1_index_defs->next;
	}
      /* If nothing above causes match to fail, the two instructions
	 are equivalent.  */

      /* After all this, kelvin is pretty sure the only time we return
	 true is if insn2_index_defs has the same originator as
	 insn1_index_defs and insn1_base_defs has the same originator
	 as ins2_base_defs.  */

      if (dump_file) {
	fprintf (dump_file, "equivalent_p preparing to return true,");
	fprintf (dump_file, " but only if regs match\n");
	fprintf (dump_file,
		 " insn %d, base_originator: %d, index_originator: %d\n",
		 uid_1, insn_entry [uid_1].original_base_use,
		 insn_entry [uid_1].original_index_use);
	fprintf (dump_file, "           base_reg: %d, index_reg: %d\n",
		 insn_entry [uid_1].original_base_reg,
		 insn_entry [uid_1].original_index_reg);
	fprintf (dump_file,
		 " insn %d, base_originator: %d, index_originator: %d\n",
		 uid_2, insn_entry [uid_2].original_base_use,
		 insn_entry [uid_2].original_index_use);
	fprintf (dump_file, "           base_reg: %d, index_reg: %d\n",
		 insn_entry [uid_2].original_base_reg,
		 insn_entry [uid_2].original_index_reg);
      }
      if (insn_entry [uid_1].original_base_reg
	  != insn_entry [uid_2].original_base_reg)
	return false;
      else if (insn_entry [uid_1].original_index_reg
	  != insn_entry [uid_2].original_index_reg)
	return false;
      else
	return true;
    }
}

/* Return true iff instruction I2 dominates instruction I1.  */
static bool
insn_dominated_by_p (rtx_insn *i1, rtx_insn *i2)
{
  basic_block bb1 = BLOCK_FOR_INSN (i1);
  basic_block bb2 = BLOCK_FOR_INSN (i2);

  if (bb1 == bb2)
    {
      for (rtx_insn *i = i2; BLOCK_FOR_INSN (i) == bb1; i = NEXT_INSN (i))
	if (i == i1)
	  return true;
      return false;
    }
  else
    return dominated_by_p (CDI_DOMINATORS, bb1, bb2);
}

static void
build_and_fixup_equivalence_classes (indexing_web_entry *insn_entry)
{
  unsigned int i;
  unsigned int *equivalence_hash =
    (unsigned int *) alloca (max_uid_at_start * sizeof (unsigned int));

  for (i = 0; i < max_uid_at_start; i++)
    equivalence_hash [i] = UINT_MAX;

  /* kelvin debugging */
  if (dump_file)
    fprintf (dump_file, "build_and_fixup_equivalence_classes\n");

  for (unsigned int uid = 0; uid < max_uid_at_start; uid++)
    {
      if (insn_entry [uid].is_relevant)
	{
	  int hash = ((insn_entry [uid].base_equivalence_hash +
		       insn_entry [uid].index_equivalence_hash)
		      % max_uid_at_start);

	  /* kelvin debugging */
	  if (dump_file)
	    fprintf (dump_file,
		     "insn %d relevant, base: %d, index: %d, compound: %d\n",
		     uid, insn_entry [uid].base_equivalence_hash,
		     insn_entry [uid].index_equivalence_hash, hash);

	  if (equivalence_hash [hash] == UINT_MAX)
	    {			/* first mention of this class */
	      equivalence_hash [hash] = uid;
	      insn_entry [uid].equivalent_sibling = UINT_MAX;
	    }
	  else
	    {
	      while ((equivalence_hash [hash] != UINT_MAX)
		     && !equivalent_p (insn_entry, uid,
				       equivalence_hash [hash]))
		hash = (hash + 1) % max_uid_at_start;

	      /* kelvin debugging */
	      if (dump_file)
		fprintf (dump_file,
			 " settling on hash table slot %d\n", hash);

	      /* either we have found an equivalent instruction, or
		 the equivalence class does not yet exist.  */
	      if (equivalence_hash [hash] != UINT_MAX)
		{
		  insn_entry [uid].equivalent_sibling =
		    equivalence_hash [hash];
		  equivalence_hash [hash] = uid;
		}
	      else		/* Equivalence class doesn't yet exist.  */
		{
		  equivalence_hash [hash] = uid;
		  insn_entry [uid].equivalent_sibling = UINT_MAX;
		}
	    }
	}
    }

  for (unsigned int i = 0; i < max_uid_at_start; i++)
    {
      while (equivalence_hash [i] != UINT_MAX)
	{
	  unsigned int the_dominator = equivalence_hash [i];
	  unsigned int uid;

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "Equivalence class consists of\n");

	  for (uid = the_dominator; uid != UINT_MAX;
	       uid = insn_entry [uid].equivalent_sibling)
	    {
	      if (insn_dominated_by_p (insn_entry [the_dominator].insn,
				       insn_entry [uid].insn))
		{
		  /* strictly debugging.  */
		  if (dump_file)
		    fprintf (dump_file, "<insn %d dominates current "
			     "dominator %d, swap>\n", uid, the_dominator);

		  the_dominator = uid;
		}

	      if (dump_file && (dump_flags & TDF_DETAILS))
		fprintf (dump_file, "  member: %d\n", uid);
	    }

	  int removed_partition = UINT_MAX;
	  int size_of_equivalence = 0;
	  unsigned int preceding_uid = UINT_MAX;
	  unsigned int next_uid;

	  /* Having found a dominator, remove from this equivalence
	     class any element that is not dominated by the_dominator.  */
	  for (uid = equivalence_hash [i]; uid != UINT_MAX; uid = next_uid)
	    {
	      next_uid = insn_entry [uid].equivalent_sibling;
	      if (!insn_dominated_by_p (insn_entry [uid].insn,
					insn_entry [the_dominator].insn))
		{
		  /* insn uid thinks its in this equivalence class,
		     but it's not dominated by the_dominator, so
		     remove it.  */
		  insn_entry [uid].equivalent_sibling = removed_partition;
		  removed_partition = uid;

		  /* strictly debugging.  */
		  if (dump_file)
		    fprintf (dump_file, "<insn %d not dominated, removing>\n",
			     uid);

		  if (preceding_uid == UINT_MAX)
		    equivalence_hash [i] = next_uid;
		  else
		    insn_entry [preceding_uid].equivalent_sibling = next_uid;
		}
	      else
		{
		  /* strictly debugging */
		  if (dump_file)
		    fprintf (dump_file, "<insn %d is dominated by insn %d, "
			     "not removing>\n", uid, the_dominator);

		  size_of_equivalence++;
		  preceding_uid = uid;
		}
	    }

	  int replacement_count = size_of_equivalence;
	  /* Confirm that everything in the equivalence class is
	     eligible for representation as a d-form insn.  Otherwise,
	     remove additional entries from the equivalence class.  */
	  long long int dominator_delta =
	    (insn_entry [the_dominator].base_delta
	     + insn_entry [the_dominator].index_delta);
	  for (uid = equivalence_hash [i]; uid != UINT_MAX;
	       uid = insn_entry [uid].equivalent_sibling)
	    {
	      if (uid != the_dominator)
		{
		  long long int dominated_delta =
		    (insn_entry [uid].base_delta
		     + insn_entry [uid].index_delta);
		  dominated_delta -= dominator_delta;

		  rtx_insn *insn = insn_entry [uid].insn;
		  rtx body = PATTERN (insn);
		  rtx mem;

		  gcc_assert (GET_CODE (body) == SET);

		  if (MEM_P (SET_SRC (body))) /* load */
		    {
		      mem = SET_SRC (body);
		      if (!rs6000_target_supports_dform_offset_p
			  (false, GET_MODE (mem), dominated_delta))
			replacement_count--;
		    }
		  else
		    {
		      mem = SET_DEST (body); /* store */
		      if (!rs6000_target_supports_dform_offset_p
			  (false, GET_MODE (mem), dominated_delta))
			replacement_count--;
		    }
		}
	    }

	  if (replacement_count > 1)
	    {
	      /* First, fix up the_dominator instruction.  */
	      rtx derived_ptr_reg = gen_reg_rtx (Pmode);
	      rtx_insn *insn = insn_entry [the_dominator].insn;
	      rtx body = PATTERN (insn);
	      rtx base_reg, index_reg;
	      rtx addr, mem;
	      rtx new_init_expr;
	      /* not used: rtx new_delta_expr = NULL; */

	      if (dump_file)
		{
		  fprintf (dump_file, "Endeavoring to replace "
			   "originating insn %d: ", the_dominator);
		  print_inline_rtx (dump_file, insn, 2);
		  fprintf (dump_file, "\n");
		}

	      gcc_assert (GET_CODE (body) == SET);
	      if (MEM_P (SET_SRC (body)))
		{
		  /* originating instruction is a load */
		  mem = SET_SRC (body);
		  addr = XEXP (SET_SRC (body), 0);
		}
	      else
		{ /* originating instruction is a store */
		  gcc_assert (MEM_P (SET_DEST (body)));
		  mem = SET_DEST (body);
		  addr = XEXP (SET_DEST (body), 0);
		}

	      enum rtx_code code = GET_CODE (addr);
	      gcc_assert ((code == PLUS) || (code == MINUS));
	      base_reg = XEXP (addr, 0);
	      index_reg = XEXP (addr, 1);

	      if (code == PLUS)
		new_init_expr = gen_rtx_PLUS (Pmode, base_reg, index_reg);
	      else
		new_init_expr = gen_rtx_MINUS (Pmode, base_reg, index_reg);
	      new_init_expr = gen_rtx_SET (derived_ptr_reg, new_init_expr);

	      rtx_insn *new_insn = emit_insn_before (new_init_expr, insn);
	      set_block_for_insn (new_insn, BLOCK_FOR_INSN (insn));
	      INSN_CODE (new_insn) = -1; /* force re-recogniition. */
	      df_insn_rescan (new_insn);

	      if (dump_file) {
		fprintf (dump_file, "with insn %d: ", INSN_UID (new_insn));
		print_inline_rtx (dump_file, new_insn, 2);
		fprintf (dump_file, "\n");
	      }

	      /* If dominator_delta != 0, we need to make adjustments
		 for dominator_delta in the D-form constant offsets
		 associated with the propagating instructions.  */

	      rtx new_mem = gen_rtx_MEM (GET_MODE (mem), derived_ptr_reg);
	      MEM_COPY_ATTRIBUTES (new_mem, mem);
	      rtx new_expr;
	      if (insn_entry [the_dominator].is_load)
		new_expr = gen_rtx_SET (SET_DEST (body), new_mem);
	      else
		new_expr = gen_rtx_SET (new_mem, SET_SRC (body));

	      if (!validate_change (insn, &PATTERN(insn), new_expr, false))
		{	/* proposed change was rejected */
		  if (dump_file)
		    {
		      fprintf (dump_file,
			       "Proposed dform optimization was"
			       " rejected by validate_change\n");
		      print_inline_rtx (dump_file, new_insn, 2);
		      fprintf (dump_file, "\n");
		    }
		}
	      else if (dump_file)
		{
		  fprintf (dump_file, "and with insn %d: ",
			   INSN_UID (insn));
		  print_inline_rtx (dump_file, insn, 2);
		  fprintf (dump_file, "\n");
		}

	      for (uid = equivalence_hash [i]; uid != UINT_MAX;
		   uid = insn_entry [uid].equivalent_sibling)
		{
		  if (uid != the_dominator)
		    {
		      long long int dominated_delta =
			(insn_entry [uid].base_delta
			 + insn_entry [uid].index_delta);
		      dominated_delta -= dominator_delta;

		      rtx_insn *insn = insn_entry [uid].insn;
		      rtx body = PATTERN (insn);
		      rtx mem;

		      if (dump_file) {
			fprintf (dump_file, "Endeavoring to replace "
				 "propagating insn %d: ", uid);
			print_inline_rtx (dump_file, insn, 2);
			fprintf (dump_file, "\n");
		      }

		      gcc_assert (GET_CODE (body) == SET);

		      if (MEM_P (SET_SRC (body))) /* load */
			mem = SET_SRC (body);
		      else
			mem = SET_DEST (body); /* store */

		      rtx ci = gen_rtx_raw_CONST_INT (Pmode, dominated_delta);
		      rtx addr_expr = gen_rtx_PLUS (Pmode,
						    derived_ptr_reg, ci);
		      rtx new_mem = gen_rtx_MEM (GET_MODE (mem), addr_expr);
		      MEM_COPY_ATTRIBUTES (new_mem, mem);

		      rtx new_expr;
		      if (insn_entry [uid].is_load)
			new_expr = gen_rtx_SET (SET_DEST (body), new_mem);
		      else
			new_expr = gen_rtx_SET (new_mem, SET_SRC (body));

		      if (!validate_change (insn, &PATTERN(insn),
					    new_expr, false))
			{	/* proposed change was rejected */
			  if (dump_file)
			    {
			      fprintf (dump_file,
				       "Proposed dform optimization was"
				       " rejected by validate_change\n");
			      print_inline_rtx (dump_file, new_expr, 2);
			      fprintf (dump_file, "\n");
			    }
			}
		      else if (dump_file)
			{
			  fprintf (dump_file,
				   "with insn %d: ", INSN_UID (insn));
			  print_inline_rtx (dump_file, insn, 2);
			  fprintf (dump_file, "\n");
			}
		    }
		}
	    }
	  else if (dump_file)
	    {
	      fprintf (dump_file,
		       "Abandoning dform optimization: too few dform insns\n");
	    }

	  /* if (removed_partition !- UINT_MAX), need to reprocess the
	     contents of the removed_partition.  There may be
	     additional opportunity to optimize within the set of
	     insns that were not dominated by the selected dominator.

	     Each time through this loop, at least one dominator and
	     any instructions it dominates are "processed".  Anything
	     not dominated by the selected dominator remains in the
	     "removed partition".  The "removed partition" gets
	     smaller on each iteration, assuring eventual termination.  */
	  equivalence_hash [i] = removed_partition;
	}
    }
}

/* Main entry point for this pass.

   This pass runs after loops have been unrolled.  The pass searches
   for sequences of code of the form:

   A0: *(array_base + offset)

   Aij:			(optional, for j = 1 .. Ki, with different Ki
                         for each value of i.  If Ki equals 0, there
                         are no constant adjustments to offset for
                         this value of i)
      offset += constant (i, j)

   Ai:                    (for i = 1 .. N)
      *(array_base + offset)

   where for each i = 1 to N and j = 1 to K-1
     A(i-1) dominates A(i), and
     A(i-1) dominates A(i, 1) and
     A(i,j) dominates A(i, j+1) and
     A(i,K) dominanes A(i) and
     there are no other assignments to offset between A0 and AN

   It replaces these sequences with:

   A0: derived_pointer = array_base + offset
       *(derived_pointer)

   Aij: leave this alone.  expect that subsequent optimization deletes
        this code as it may become dead (since we don't use the
        indexing expression following out code transformations.)

   Ai:
   *(derived_pointer + constant_i)
     (where constant_i equals sum of constant (n,j) for all n from 1
      to i paired with all j from 1 to Kn,

   Note that each function may match this pattern multiple times.

*/
unsigned int
rs6000_fix_indexing (function *fun)
{
  basic_block bb;
  rtx_insn *insn, *curr_insn = 0;
  indexing_web_entry *insn_entry;

  calculate_dominance_info (CDI_DOMINATORS);

  /* Dataflow analysis for use-def chains.  */
  df_set_flags (DF_RD_PRUNE_DEAD_DEFS);
  df_chain_add_problem (DF_DU_CHAIN | DF_UD_CHAIN);
  df_analyze ();

  /* Since this pass creates new instructions, get_max_uid () may
     return different values at different times during this pass.  The
     insn_entry array does not represent any of the instructions newly
     inserted during this pass.
  */
  max_uid_at_start = get_max_uid ();
  insn_entry = XCNEWVEC (indexing_web_entry, max_uid_at_start);

  if (dump_file) {
    fprintf (dump_file, "Creating insn_entry array with %d entries\n",
	     max_uid_at_start);
  }

  /* I'm looking for patterns such as the following:

      ;; Note that reg/v/f:DI <27> gets its value here, but do we
      ;; care?  What is important to us is that reg/v/f:DI <27> does
      ;; not change throughout our sequence of insns..

      (cinsn 2 (set (reg/v/f:DI <27> [ x ])
                    (reg:DI 3 [ x ])) "ddot-c.c":12
       (expr_list:REG_DEAD (reg:DI 3 [ x ])))

      ;;
      ;; vsr_35 = MEM [x + reg:DI <9>]
      ;;
      (cinsn 31 (set (reg:V2DF <35> [ vect__3.7 ])
                     (mem:V2DF (plus:DI (reg/v/f:DI <27> [ x ])
                                        (reg:DI <9> [ ivtmp.18 ]))
                      [1 MEM[base: x_20(D), index: ivtmp.18_35,
                       offset: 0B]+0 S16 A64])) "ddot-c.c":18)

      ;;
      ;; i += constant value 16

      ;;
      (cinsn 304 (set (reg:DI <70>)
                      (plus:DI (reg:DI <9> [ ivtmp.18 ])
                               (const_int 16)))
       (expr_list:REG_DEAD (reg:DI <9> [ ivtmp.18 ])))
      (cinsn 34 (set (reg:DI <9> [ ivtmp.18 ])
                     (reg:DI <70>)))

      ;; by the way, I don't think I really need to do dominator
      ;; analysis.  I can just use the du-chains to confirm that there
      ;; is only one way the information can flow to particular
      ;; locations in the code.

      What does the algorithm look like:
       1. Look for multiple array indexing expressions that refer to
          the same array base address.
       2. Group these into subsets for which the indexing expression
          derives from the same initial_value + some accumulation of
          constant values added thereto.

      Question: is it possible that if I look at the insns now, they
      will have adjusted register numbers?

   */

  /* Walk the insns to gather basic data.  */
  FOR_ALL_BB_FN (bb, fun)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, "Scrutinizing bb %d\n", bb->index);

      FOR_BB_INSNS_SAFE (bb, insn, curr_insn)
	{
	  unsigned int uid = INSN_UID (insn);

	  insn_entry[uid].insn = insn;
	  insn_entry[uid].bb = BLOCK_FOR_INSN (insn);
	  insn_entry[uid].is_relevant = false;

	  if (dump_file && (dump_flags & TDF_DETAILS)) {
	    fprintf (dump_file, "\nLooking at insn: %d\n", uid);
	    df_dump_insn_top (insn, dump_file);
	    dump_insn_slim (dump_file, insn);
	    df_dump_insn_bottom (insn, dump_file);
	  }

	  /*
	   * first, look for all memory[base + index] expressions.
	   * then group these by base.
	   * then for all instructions in each group, scrutinize the index
	   * definition. Partition this group according to the origin
	   * variable upon which the the definitions of i are based.
	   *
	   * how do we define "origin variable"?
	   *
	   *  if i has multiple definitions, it is its own origin
	   *  variable.  Likewise, if i has a single definition and the
	   *  definition is NOT the sum or difference of a constant value
	   *  and some other variable, the i is its own origin variable.
	   *
	   *  Otherwise, i has the same origin variable as the expression
	   *  that represents its definition.
	   *
	   * After we've created these partitions, for each partition
	   * whose size is greater than 1:
	   *
	   *  1. introduce derived_ptr = base + origin_variable
	   *     immediately following the instruction that defines
	   *     origin_variable.
	   *
	   *  2. for each member of the partition, replace the expression
	   *     memory [base + index] with derived_ptr [constant], where
	   *     constant is the sum of all constant values added to the
	   *     origin variable to represent this particular value of i.
	   */
	  if (NONDEBUG_INSN_P (insn))
	    {
	      rtx body = PATTERN (insn);
	      rtx mem;
	      if ((GET_CODE (body) == SET) && MEM_P (SET_SRC (body)))
		{
		  mem = XEXP (SET_SRC (body), 0);
		  insn_entry[uid].is_load = true;
		  insn_entry[uid].is_store = false;
		  if (dump_file && (dump_flags & TDF_DETAILS))
		    {
		      fprintf (dump_file,
			       " this insn is fetching data from memory: ");
		      print_inline_rtx (dump_file, mem, 2);
		      fprintf (dump_file, "\n");
		    }
		}
	      else if ((GET_CODE (body) == SET) && MEM_P (SET_DEST (body)))
		{
		  mem = XEXP (SET_DEST (body), 0);
		  insn_entry[uid].is_load = false;
		  insn_entry[uid].is_store = true;
		  if (dump_file && (dump_flags & TDF_DETAILS))
		    {
		      fprintf (dump_file,
			       " this insn is storing data to memory: ");
		      print_inline_rtx (dump_file, mem, 2);
		      fprintf (dump_file, "\n");
		    }
		}
	      else
		{
		  if (dump_file && (dump_flags & TDF_DETAILS))
		    {
		      fprintf (dump_file,
			       " this insn is neither load nor store\n");
		    }
		  continue;		/* Not a load or store */
		}

	      enum rtx_code code = GET_CODE (mem);
	      if ((code == PLUS) || (code == MINUS))
		{
		  rtx base_reg = XEXP (mem,0);
		  rtx index_reg = XEXP (mem, 1);

		  if (dump_file && (dump_flags & TDF_DETAILS))
		    {
		      fprintf (dump_file, " memory is base + index, ");
		      fprintf (dump_file, "base: ");
		      print_inline_rtx (dump_file, base_reg, 2);
		      fprintf (dump_file, "\n index: ");
		      print_inline_rtx (dump_file, index_reg, 2);
		      fprintf (dump_file, "\n");
		    }

		  if (REG_P (base_reg) && REG_P (index_reg))
		    {
		      /*
		      int base_originator = -1;
		      unsigned long long int base_offset = 0;
		      const char *base_defs = NULL;
		      int index_originator = -1;
		      unsigned long long int index_offset = 0;
		      const char *index_defs = NULL;
		      */

		      struct df_insn_info *insn_info = DF_INSN_INFO_GET (insn);
		      /* Since insn is known to represent a sum or
			 difference, this insn is likely to use at
			 least two input variables.  */

		      int num_base_defs = 0;
		      int num_index_defs = 0;
		      bool base_is_relevant = false;
		      bool index_is_relevant = false;
		      bool base_is_originating = false;
		      bool index_is_originating = false;
		      df_ref use;
		      FOR_EACH_INSN_INFO_USE (use, insn_info)
			{
			  if (rtx_equal_p (DF_REF_REG (use), base_reg))
			    {
			      if (dump_file && (dump_flags & TDF_DETAILS))
				{
				  fprintf (dump_file,
					   "Found use corresponding "
					   "to base_reg\n");
				  df_ref_debug (use, dump_file);
				}
			      struct df_link *def_link = DF_REF_CHAIN (use);
			      num_base_defs++;

			      /* If there is no definition, or the definition
				 is artificial, or there are multiple
				 definitions, this is an originating use.  */
			      if (!def_link || !def_link->ref
				  || DF_REF_IS_ARTIFICIAL (def_link->ref)
				  || def_link->next)
				{
				  if (dump_file
				      && (dump_flags & TDF_DETAILS))
				    fprintf (dump_file,
					     "Use is originating!\n");

				  base_is_relevant = true;
				  base_is_originating = true;
				  insn_entry[uid].original_base_reg
				    = REGNO (base_reg);
				  insn_entry[uid].original_base_use = uid;
				  insn_entry[uid].base_delta = 0;

				  /* kelvin debug */
				  if (dump_file)
				    fprintf (dump_file,
					     "hashing for insn %d base\n",
					     uid);

				  insn_entry[uid].base_equivalence_hash =
				    equivalence_hash (def_link);
				}
			      else
				{
				  /* Only one definition.  Dig deeper.  */
				  long long int delta = 0;
				  rtx insn2 =
				    find_true_originator (def_link, &delta);

				  if (insn2)
				    {
				      unsigned uid2 = INSN_UID (insn2);

				      if (dump_file
					  && (dump_flags & TDF_DETAILS))
					fprintf (dump_file,
						 "Use may propagate from %d\n",
						 uid2);

				      struct df_insn_info *insn_info2 =
					DF_INSN_INFO_GET (insn2);

				      df_ref use2;
				      if (insn_info2)
					use2 = DF_INSN_INFO_USES (insn_info2);
				      else
					use2 = NULL;

				      if (!use2 || !DF_REF_NEXT_LOC (use2))
					{
					  base_is_originating = false;

					  rtx body = PATTERN (insn2);
					  gcc_assert (GET_CODE (body) == SET);
					  gcc_assert (REG_P (SET_DEST (body)));

					  insn_entry[uid].original_base_reg
					    = REGNO (SET_DEST (body));
					  insn_entry[uid].original_base_use
					    = uid2;
					  insn_entry[uid].base_delta = delta;

					  if (use2)
					    {
					      struct df_link *def_link =
						DF_REF_CHAIN (use2);

					      /* kelvin debug */
					      if (dump_file)
						fprintf (dump_file,
							 "hashing for insn %d base\n",
							 uid2);

					      base_is_relevant = true;
					      insn_entry[uid].
						base_equivalence_hash =
						equivalence_hash (def_link);
					    }
					  /* else, base is not relevant.  */
					  /*
					  else
					    {
					    insn_entry[uid].
					      base_equivalence_hash =
					      equivalence_hash (NULL);
					  */

					  if (dump_file
					      && (dump_flags & TDF_DETAILS))
					    {
					      fprintf (dump_file,
						       " propagates from"
						       " originating insn %d"
						       " with delta: %lld\n",
						       uid2, delta);
					    }
					}
				      else if (dump_file
					       && (dump_flags & TDF_DETAILS))
					    {
					      fprintf (dump_file,
						       " Dependencies are too"
						       " complicated for this"
						       " optimization\n");
					    }

				    }
				}
			    }
			  else if (rtx_equal_p (DF_REF_REG (use), index_reg))
			    {
			      if (dump_file && (dump_flags & TDF_DETAILS))
				{
				  fprintf (dump_file,
					   "Found use corresponding "
					   "to index\n");
				  df_ref_debug (use, dump_file);
				}
			      struct df_link *def_link = DF_REF_CHAIN (use);
			      num_index_defs++;

			      /* If there is no definition, or the definition
				 is artificial, or there are multiple
				 definitions, this is an originating use.  */
			      if (!def_link || !def_link->ref
				  || DF_REF_IS_ARTIFICIAL (def_link->ref)
				  || def_link->next)
				{
				  if (dump_file
				      && (dump_flags & TDF_DETAILS))
				    fprintf (dump_file,
					     "Use is originating!\n");

				  index_is_relevant = true;
				  index_is_originating = true;

				  insn_entry[uid].original_index_reg
				    = REGNO (index_reg);
				  insn_entry[uid].original_index_use = uid;
				  insn_entry[uid].index_delta = 0;

				  /* kelvin debug */
				  if (dump_file)
				    fprintf (dump_file,
					     "hashing for insn %d index\n",
					     uid);

				  insn_entry[uid].index_equivalence_hash =
				    equivalence_hash (def_link);
				}
			      else
				{
				  /* Only one definition.  Dig deeper.  */
				  long long int delta = 0;
				  rtx insn2 =
				    find_true_originator (def_link, &delta);

				  if (insn2)
				    {
				      unsigned int uid2 = INSN_UID (insn2);

				      if (dump_file
					  && (dump_flags & TDF_DETAILS))
					fprintf (dump_file,
						 "Use may propagate from %d\n",
						 uid2);

				      struct df_insn_info *insn_info2 =
					DF_INSN_INFO_GET (insn2);

				      df_ref use2;
				      if (insn_info2)
					use2 = DF_INSN_INFO_USES (insn_info2);
				      else
					use2 = NULL;

				      if (!use2 || !DF_REF_NEXT_LOC (use2))
					{
					  index_is_originating = false;

					  rtx body = PATTERN (insn2);
					  gcc_assert (GET_CODE (body) == SET);
					  gcc_assert (REG_P (SET_DEST (body)));

					  insn_entry[uid].original_index_reg
					    = REGNO (SET_DEST(body));
					  insn_entry[uid].original_index_use
					    = uid2;
					  insn_entry[uid].index_delta = delta;

					  if (use2)
					    {
					      struct df_link *def_link =
						DF_REF_CHAIN (use2);

					      /* kelvin debug */
					      if (dump_file)
						fprintf (dump_file,
							 "hashing for insn %d index\n",
							 uid2);

					      index_is_relevant = true;
					      insn_entry[uid].
						index_equivalence_hash =
						equivalence_hash (def_link);
					    }
					  /* else, index is not relevant.  */
					  /*
					  else
					    insn_entry[uid].
					      index_equivalence_hash =
					      equivalence_hash (NULL);
					  */

					  if (dump_file
					      && (dump_flags & TDF_DETAILS))
					    {
					      fprintf (dump_file,
						       " propagates from"
						       " originating insn %d"
						       ", with delta %lld\n",
						       uid2, delta);
					    }
					}
				      else if (dump_file
					       && (dump_flags & TDF_DETAILS))
					{
					  fprintf (dump_file,
						   " Dependencies are too"
						   " complicated for this"
						   " optimization\n");
					}
				    }
				}
			    }
			}

		      /* This insn is only relevant if there is
			 exactly one definition of base and one
			 definition of index and they are both
			 considered to be relevant.  */
		      if ((num_base_defs == 1) && (num_index_defs == 1) &&
			  base_is_relevant && index_is_relevant)
			{
			  insn_entry[uid].is_relevant = true;
			  insn_entry[uid].is_originating =
			    (base_is_originating && index_is_originating);
			}
		      else if (dump_file)
			{
			  fprintf (dump_file,
				   "Rejecting dform optimization of insn %d\n",
				   uid);

			  if (num_base_defs != 1)
			    fprintf (dump_file,
				     "Too %s (%d) base definitions\n",
				     (num_base_defs > 1)? "many": "few",
				     num_base_defs);

			  if (num_index_defs != 1)
			    fprintf (dump_file,
				     "Too %s (%d) index definitions\n",
				     (num_index_defs > 1)? "many": "few",
				     num_index_defs);

			  if (!base_is_relevant)
			    fprintf (dump_file,
				     "The available base definition is "
				     "not relevant\n");

			  if (!index_is_relevant)
			    fprintf (dump_file,
				     "The available index definition is "
				     "not relevant\n");
			}
		    }
		  else if (dump_file && (dump_flags & TDF_DETAILS))
		    fprintf (dump_file,
			     " punting because base or index not registers\n");
		}
	      else if (dump_file && (dump_flags & TDF_DETAILS))
		fprintf (dump_file,
			 " address not sum or difference of values\n");
	    }
	  /* else, this is a DEBUG_INSN_P (insn) so ignore it.  */
	}

	if (dump_file && (dump_flags & TDF_DETAILS))
	  fprintf (dump_file, "\n");
    }

  build_and_fixup_equivalence_classes (insn_entry);
  free_dominance_info (CDI_DOMINATORS);
  return 0;
}  // anon namespace


const pass_data pass_data_fix_indexing =
{
  RTL_PASS, /* type */
  "indexing", /* name */
  OPTGROUP_NONE, /* optinfo_flags, or could use OPTGROUP_LOOP */
  TV_NONE, /* tv_id, or could use TV_LOOP_UNROLL */
  0, /* properties_required */
  0, /* properties_provided */
  0, /* properties_destroyed */
  0, /* todo_flags_start */
  TODO_df_finish, /* todo_flags_finish */
};

class pass_fix_indexing : public rtl_opt_pass
{
public:
  pass_fix_indexing(gcc::context *ctxt)
    : rtl_opt_pass(pass_data_fix_indexing, ctxt)
  {}

  /* opt_pass methods: */
  virtual bool gate (function *)
    {
      // This is most relevant to P9 targets since that architecture
      // introduces new D-form instructions, but this may pay off on
      // other architectures as well.  Might want to experiment.
      return (optimize > 0 && !BYTES_BIG_ENDIAN && TARGET_VSX
	      && TARGET_P9_VECTOR);
    }

  virtual unsigned int execute (function *fun)
    {
      return rs6000_fix_indexing (fun);
    }

  opt_pass *clone ()
    {
      return new pass_fix_indexing (m_ctxt);
    }

}; // class pass_fix_indexing

rtl_opt_pass *make_pass_fix_indexing (gcc::context *ctxt)
{
  return new pass_fix_indexing (ctxt);
}
