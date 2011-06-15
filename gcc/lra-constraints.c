/* Code for RTL transformations to satisfy insn constraints.
   Copyright (C) 2010, 2011
   Free Software Foundation, Inc.

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


/* This code selects alternatives for insns based on register
   allocation.  It has also a mode to do some simple code
   transformations.  */

#undef REG_OK_STRICT

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "hard-reg-set.h"
#include "rtl.h"
#include "tm_p.h"
#include "regs.h"
#include "insn-config.h"
#include "insn-codes.h"
#include "recog.h"
#include "output.h"
#include "addresses.h"
#include "target.h"
#include "function.h"
#include "expr.h"
#include "basic-block.h"
#include "except.h"
#include "optabs.h"
#include "df.h"
#include "ira.h"
#include "rtl-error.h"
#include "lra-int.h"

/* Value of LRA_CURR_RELOAD_NUM at the beginning of BB of the current
   insn.  Remember that LRA_CURR_RELOAD_NUM is the number of emitted
   reload insns.  */
static int bb_reload_num;

/* Array whose element is (MEM:MODE BASE_REG) corresponding to the
   mode (index) and where BASE_REG is a base hard register for given
   memory mode.  */
static rtx indirect_mem[MAX_MACHINE_MODE];

/* Return indrect memory for MODE.  */
static rtx
get_indirect_mem (enum machine_mode mode)
{
  if (indirect_mem[mode] == NULL_RTX)
    {
      enum reg_class rclass = base_reg_class (mode, MEM, SCRATCH);

      indirect_mem[mode]
	 = gen_rtx_MEM (mode, regno_reg_rtx [ira_class_hard_regs[rclass][0]]);
    }
  return indirect_mem[mode];
}

/* Initiate INDIECT_MEM.  */
static void
init_indirect_mem (void)
{
  int i;

  for (i = 0; i < MAX_MACHINE_MODE; i++)
    indirect_mem[i] = NULL_RTX;
}



/* The current insn being processed and corresponding its data (basic
   block, the insn data, and the insn static data.  */
static rtx curr_insn;
static basic_block curr_bb;
static lra_insn_recog_data_t curr_id;
static struct lra_static_insn_data *curr_static_id;



/* The page contains code to deal with the secondary memory.  */

#ifdef SECONDARY_MEMORY_NEEDED

/* Cached result of function get_secondary_mem.  */
rtx lra_secondary_memory[NUM_MACHINE_MODES];

/* Return a memory location that will be used to copy values from
   registers in mode MODE.  */
static rtx
get_secondary_mem (enum machine_mode mode)
{
  rtx x;

  /* By default, if MODE is narrower than a word, widen it to a word.
     This is required because most machines that require these memory
     locations do not support short load and stores from all registers
     (e.g., FP registers).  */

#ifdef SECONDARY_MEMORY_NEEDED_MODE
  mode = SECONDARY_MEMORY_NEEDED_MODE (mode);
#else
  if (GET_MODE_BITSIZE (mode) < BITS_PER_WORD && INTEGRAL_MODE_P (mode))
    mode = mode_for_size (BITS_PER_WORD, GET_MODE_CLASS (mode), 0);
#endif

  if (lra_secondary_memory[(int) mode] == NULL_RTX)
    {
      /* If this is the first time we've tried to get a MEM for this
	  mode, allocate a new one.  `something_changed' in reload will
	  get set by noticing that the frame size has changed.  */
#ifdef SECONDARY_MEMORY_NEEDED_RTX
      x = SECONDARY_MEMORY_NEEDED_RTX (mode);
#else
      x = assign_stack_local (mode, GET_MODE_SIZE (mode), 0);
#endif
      lra_secondary_memory[(int) mode]
	 = lra_eliminate_regs_1 (x, GET_MODE (x), false, false, true);
    }

  return copy_rtx (lra_secondary_memory[(int) mode]);
}
#endif



/* Start number for new registers at the current constraints pass
   start.  */
static int new_regno_start;

/* Return hard regno of REGNO or if it is was not assigned to a hard
   register, use a hard register from its preferred class.  */
static int
get_try_hard_regno (int regno)
{
  int hard_regno;
  enum reg_class rclass;

  if ((hard_regno = regno) >= FIRST_PSEUDO_REGISTER)
    hard_regno = lra_get_regno_hard_regno (regno);
  if (hard_regno >= 0)
    return hard_regno;
  rclass = lra_get_preferred_class (regno);
  if (rclass == NO_REGS)
    return -1;
  return ira_class_hard_regs[rclass][0];
}

/* Return class of hard regno of REGNO or if it is was not assigned to
   a hard register, return its preferred class but only for
   non-inherited pseudos created on the current constraint pass.
   Otherwise, return NO_REGS.  */
static enum reg_class
get_reg_class (int regno)
{
  int hard_regno;

  if ((hard_regno = regno) >= FIRST_PSEUDO_REGISTER)
    hard_regno = lra_get_regno_hard_regno (regno);
  if (hard_regno >= 0)
    return REGNO_REG_CLASS (hard_regno);
  if (regno >= new_regno_start
      && ! bitmap_bit_p (&lra_inheritance_pseudos, regno))
    return lra_get_preferred_class (regno);
  return NO_REGS;
}

/* Return true if REGNO satisfies reg class constraint CL.  For new
   non-inherited pseudos we should make more accurate class *NEW_CLASS
   (we set up it if it is not NULL) to satisfy the constraints.
   Otherwise, set up NEW_CLASS to NO_REGS.  */
static bool
in_class_p (int regno, enum reg_class cl, enum reg_class *new_class)
{
  enum reg_class rclass, common_class;

  if (new_class != NULL)
    *new_class = NO_REGS;
  if (regno < FIRST_PSEUDO_REGISTER)
    return TEST_HARD_REG_BIT (reg_class_contents[cl], regno);
  rclass = get_reg_class (regno);
  if (regno < new_regno_start
      || bitmap_bit_p (&lra_inheritance_pseudos, regno))
    return (rclass != NO_REGS && ira_class_subset_p[rclass][cl]
	     && ! hard_reg_set_subset_p (reg_class_contents[cl],
					 lra_no_alloc_regs));
  else
    {
      common_class = ira_reg_class_subset[rclass][cl];
      if (new_class != NULL)
	*new_class = common_class;
      return ! hard_reg_set_subset_p (reg_class_contents[common_class],
				      lra_no_alloc_regs);
    }
}

/* Return true if REGNO satisfies a memory constraint.  */
static bool
in_mem_p (int regno)
{
  return get_reg_class (regno) == NO_REGS;
}

/* Return the defined and profitable equiv substition of reg X, return
   X otherwise.  */
static rtx
get_equiv_substitution (rtx x)
{
  int regno;
  rtx res;

  if (! REG_P (x) || (regno = REGNO (x)) < FIRST_PSEUDO_REGISTER
      || ! ira_reg_equiv[regno].defined_p
      || ! ira_reg_equiv[regno].profitable_p
      || lra_get_regno_hard_regno (regno) >= 0)
    return x;
  if ((res = ira_reg_equiv[regno].memory) != NULL_RTX)
    return res;
  if ((res = ira_reg_equiv[regno].constant) != NULL_RTX)
    return res;
  if ((res = ira_reg_equiv[regno].invariant) != NULL_RTX)
    return res;
  gcc_unreachable ();
}



/* The page contains code to reuse input reloads.  */

/* Structure describes input reload of the current insns.  */
struct input_reload
{
  /* Reloaded value.  */
  rtx input;
  /* Reload pseudo used.  */
  rtx reg;
};

/* The number of elements in the following array.  */
static int curr_insn_input_reloads_num;
/* Array containing info about input reloads.  It is used to find the
   same input reload and reuse the reload pseudo in this case.  */
static struct input_reload curr_insn_input_reloads[LRA_MAX_INSN_RELOADS];

/* Initiate data concerning reusage of input reloads for the current
   insn.  */
static void
init_curr_insn_input_reloads (void)
{
  curr_insn_input_reloads_num = 0;
}

/* Change class of pseudo REGNO (and all pseudos bound to it) to
   NEW_CLASS.  Print info about it using TITLE.  Output a new line if
   NL_P.  */
static void
change_class (int regno, enum reg_class new_class, const char *title, bool nl_p)
{
  int curr_regno;

  if (lra_dump_file != NULL)
    fprintf (lra_dump_file, "%s to class %s for",
	     title, reg_class_names[new_class]);
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    {
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, " r%d", curr_regno);
      setup_reg_classes (curr_regno, new_class, NO_REGS, new_class);
    }
  if (lra_dump_file != NULL && nl_p)
    fprintf (lra_dump_file, "\n");
}

/* Create a new pseudo using MODE, RCLASS, ORIGINAL, TITLE or reuse
   already created input reload pseudo (only if TYPE is not OP_OUT).
   The result pseudo is returned through RESULT_REG.  Return TRUE if
   we created a new pseudo, FALSE if we reused the already created
   input reload pseudo.  */
static bool
get_reload_reg (enum op_type type, enum machine_mode mode, rtx original,
		enum reg_class rclass, const char *title, rtx *result_reg)
{
  bool res_p;
  int i, regno;
  enum reg_class new_class;

  if (type == OP_OUT)
    {
      *result_reg = lra_create_new_reg (mode, original, rclass, title);
      return true;
    }
  for (i = 0; i < curr_insn_input_reloads_num; i++)
    if (rtx_equal_p (curr_insn_input_reloads[i].input, original))
      break;
  if (i >= curr_insn_input_reloads_num
      || ! in_class_p (REGNO (curr_insn_input_reloads[i].reg),
			rclass, &new_class))
    {
      res_p = true;
      *result_reg = lra_create_new_reg (mode, original, rclass, title);
    }
  else
    {
      gcc_assert (! side_effects_p (original));
      res_p = false;
      *result_reg = curr_insn_input_reloads[i].reg;
      regno = REGNO (*result_reg);
      if (lra_dump_file != NULL)
	 {
	   fprintf (lra_dump_file, "     Reuse r%d for reload ", regno);
	   print_value_slim (lra_dump_file, original, 1);
	 }
      if (rclass != new_class)
	 change_class (regno, new_class, ", change", false);
      if (lra_dump_file != NULL)
	 fprintf (lra_dump_file, "\n");
    }
  gcc_assert (curr_insn_input_reloads_num < LRA_MAX_INSN_RELOADS);
  curr_insn_input_reloads[curr_insn_input_reloads_num].input = original;
  curr_insn_input_reloads[curr_insn_input_reloads_num++].reg = *result_reg;
  return res_p;
}



/* The page contains code to extract memory address parts.  */

/* Info about base and index regs of an address.  */
struct address
{
  rtx *base_reg_loc;  /* NULL if there is no a base register.  */
  rtx *base_reg_loc2; /* Second location of {post/pre}_modify, NULL
			 otherwise. */
  rtx *index_reg_loc; /* NULL if there is no an index register.  */
  rtx *index_loc; /* location of index reg * scale or index_reg_loc
		      otherwise. */
  rtx *disp_loc; /* NULL if there is no a displacement.  */
  /* Defined if base_reg_loc is not NULL.  */
  enum rtx_code base_outer_code, index_code;
  /* True if the base register is modified in the address, for
     example, in PRE_INC.  */
  bool base_modify_p;
};

/* Wrapper around REGNO_OK_FOR_INDEX_P, to allow pseudo registers.  */
static inline bool
ok_for_index_p_nonstrict (rtx reg)
{
  unsigned regno = REGNO (reg);
  
  return regno >= FIRST_PSEUDO_REGISTER || REGNO_OK_FOR_INDEX_P (regno);
}

/* A version of regno_ok_for_base_p for use here, when all
   pseudo-registers should count as OK.  Arguments as for
   regno_ok_for_base_p.  */
static inline bool
ok_for_base_p_nonstrict (rtx reg, enum machine_mode mode,
			 enum rtx_code outer_code, enum rtx_code index_code)
{
  unsigned regno = REGNO (reg);

  if (regno >= FIRST_PSEUDO_REGISTER)
    return true;
  return ok_for_base_p_1 (regno, mode, outer_code, index_code);
}

/* Process address part with location *LOC to extract address
   characteristics.

   If CONTEXT_P is false, we are looking at the base part of an
   address, otherwise we are looking at the index part.

   MODE is the mode of the memory reference; OUTER_CODE and INDEX_CODE
   give the context that the rtx appears in; MODIFY_P if *LOC is
   modified.  */
static void
extract_loc_address_regs (enum machine_mode mode,
			  rtx *loc, bool context_p, enum rtx_code outer_code,
			  enum rtx_code index_code,
			  bool modify_p, struct address *ad)
{
  rtx x = *loc;
  enum rtx_code code = GET_CODE (x);
  bool base_ok_p;

  switch (code)
    {
    case CONST_INT:
    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
      if (! context_p)
	ad->disp_loc = loc;
      return;

    case CC0:
    case PC:
      return;

    case PLUS:
      /* When we have an address that is a sum, we must determine
	 whether registers are "base" or "index" regs.  If there is a
	 sum of two registers, we must choose one to be the
	 "base".  */
      {
	rtx *arg0_loc = &XEXP (x, 0);
	rtx *arg1_loc = &XEXP (x, 1);
	rtx arg0 = *arg0_loc;
	rtx arg1 = *arg1_loc;
	enum rtx_code code0 = GET_CODE (arg0);
	enum rtx_code code1 = GET_CODE (arg1);

	/* Look inside subregs.  */
	if (code0 == SUBREG)
	  {
	    arg0_loc = &SUBREG_REG (arg0);
	    arg0 = *arg0_loc;
	    code0 = GET_CODE (arg0);
	  }
	if (code1 == SUBREG)
	  {
	    arg1_loc = &SUBREG_REG (arg1);
	    arg1 = *arg1_loc;
	    code1 = GET_CODE (arg1);
	  }

	/* If this machine only allows one register per address, it
	   must be in the first operand.  */
	if (MAX_REGS_PER_ADDRESS == 1)
	  {
	    extract_loc_address_regs (mode, arg0_loc, false, PLUS, code1,
				      modify_p, ad);
	    gcc_assert (CONSTANT_P (arg1)); /* It should be a displacement.  */
	    ad->disp_loc = arg1_loc;
	  }
	/* If index and base registers are the same on this machine,
	   just record registers in any non-constant operands.  We
	   assume here, as well as in the tests below, that all
	   addresses are in canonical form.  */
	else if (INDEX_REG_CLASS == base_reg_class (VOIDmode, PLUS, SCRATCH))
	  {
	    extract_loc_address_regs (mode, arg0_loc, false, PLUS, code1,
				      modify_p, ad);
	    if (! CONSTANT_P (arg1))
	      extract_loc_address_regs (mode, arg1_loc, true, PLUS, code0,
					modify_p, ad);
	    else
	      ad->disp_loc = arg1_loc;
	  }

	/* If the second operand is a constant integer, it doesn't
	   change what class the first operand must be.  */
	else if (code1 == CONST_INT || code1 == CONST_DOUBLE)
	  {
	    extract_loc_address_regs (mode, arg0_loc, context_p, PLUS, code1,
				      modify_p, ad);
	    ad->disp_loc = arg1_loc;
	  }
	/* If the second operand is a symbolic constant, the first
	   operand must be an index register.  */
	else if (code1 == SYMBOL_REF || code1 == CONST || code1 == LABEL_REF)
	  {
	    extract_loc_address_regs (mode, arg0_loc, true, PLUS, code1,
				      modify_p, ad);
	    ad->disp_loc = arg1_loc;
	  }
	/* If both operands are registers but one is already a hard
	   register of index or reg-base class, give the other the
	   class that the hard register is not.  */
	else if (code0 == REG && code1 == REG
		 && REGNO (arg0) < FIRST_PSEUDO_REGISTER
		 && ((base_ok_p
		      = ok_for_base_p_nonstrict (arg0, mode, PLUS, REG))
		     || ok_for_index_p_nonstrict (arg0)))
	  {
	    extract_loc_address_regs
	      (mode, arg0_loc, ! base_ok_p, PLUS, REG, modify_p, ad);
	    extract_loc_address_regs
	      (mode, arg1_loc, base_ok_p, PLUS, REG, modify_p, ad);
	  }
	else if (code0 == REG && code1 == REG
		 && REGNO (arg1) < FIRST_PSEUDO_REGISTER
		 && ((base_ok_p
		      = ok_for_base_p_nonstrict (arg1, mode, PLUS, REG))
		     || ok_for_index_p_nonstrict (arg1)))
	  {
	    extract_loc_address_regs 
	      (mode, arg0_loc, base_ok_p, PLUS, REG, modify_p, ad);
	    extract_loc_address_regs 
	      (mode, arg1_loc, ! base_ok_p, PLUS, REG, modify_p, ad);
	  }
	/* If one operand is known to be a pointer, it must be the
	   base with the other operand the index.  Likewise if the
	   other operand is a MULT.  */
	else if ((code0 == REG && REG_POINTER (arg0)) || code1 == MULT)
	  {
	    extract_loc_address_regs (mode, arg0_loc, false, PLUS, code1,
				      modify_p, ad);
	    if (code1 == MULT)
	      ad->index_loc = arg1_loc;
	    extract_loc_address_regs (mode, arg1_loc, true, PLUS, code0,
				      modify_p, ad);
	  }
	else if ((code1 == REG && REG_POINTER (arg1)) || code0 == MULT)
	  {
	    extract_loc_address_regs (mode, arg0_loc, true, PLUS, code1,
				      modify_p, ad);
	    if (code1 == MULT)
	      ad->index_loc = arg0_loc;
	    extract_loc_address_regs (mode, arg1_loc, false, PLUS, code0,
				      modify_p, ad);
	  }
	/* Otherwise, count equal chances that each might be a base or
	   index register.  This case should be rare.  */
	else
	  {
	    extract_loc_address_regs (mode, arg0_loc, false, PLUS, code1,
				      modify_p, ad);
	    extract_loc_address_regs (mode, arg1_loc, true, PLUS, code0,
				      modify_p, ad);
	  }
      }
      break;

      /* Double the importance of a pseudo that is incremented or
	 decremented, since it would take two extra insns if it ends
	 up in the wrong place.  */
    case POST_MODIFY:
    case PRE_MODIFY:
      extract_loc_address_regs (mode, &XEXP (x, 0), false, code,
				GET_CODE (XEXP (XEXP (x, 1), 1)), true,
				ad);
      gcc_assert (rtx_equal_p (XEXP (XEXP (x, 1), 0), XEXP (x, 0)));
      ad->base_reg_loc2 = &XEXP (XEXP (x, 1), 0);
      if (REG_P (XEXP (XEXP (x, 1), 1)))
	extract_loc_address_regs (mode, &XEXP (XEXP (x, 1), 1), true, code,
				  REG, modify_p, ad);
      break;

    case POST_INC:
    case PRE_INC:
    case POST_DEC:
    case PRE_DEC:
      extract_loc_address_regs (mode, &XEXP (x, 0), false, code, SCRATCH,
				true, ad);
      break;

    case REG:
      if (context_p)
	ad->index_reg_loc = loc;
      else
	{
	  ad->base_reg_loc = loc;
	  ad->base_outer_code = outer_code;
	  ad->index_code = index_code;
	  ad->base_modify_p = modify_p;
	}
      break;

    default:
      {
	const char *fmt = GET_RTX_FORMAT (code);
	int i;

	for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
	  if (fmt[i] == 'e')
	    extract_loc_address_regs (mode, &XEXP (x, i), context_p,
				      code, SCRATCH, modify_p, ad);
      }
    }
}


/* Extract address characteristics in address with location *LOC.
   Return them in AD.  Parameter OUTER_CODE for MEM should be MEM.
   Parameter OUTER_CODE for 'p' constraint should be ADDRESS and
   MEM_MODE should be VOIDmode.  */
static void
extract_address_regs (enum machine_mode mem_mode,
		       rtx *loc, enum rtx_code outer_code, struct address *ad)
{
  ad->base_reg_loc = ad->base_reg_loc2
    = ad->index_reg_loc = ad->index_loc = ad->disp_loc = NULL;
  ad->base_outer_code = SCRATCH;
  ad->index_code = SCRATCH;
  ad->base_modify_p = false;
  extract_loc_address_regs (mem_mode, loc, false, outer_code, SCRATCH,
			     false, ad);  
  if (ad->index_loc == NULL)
    /* SUBREG ??? */
    ad->index_loc = ad->index_reg_loc;
}



/* The page constains major code to choose the current insn
   alternative and do reloads for it.  */

/* Return start register offset of hard register REGNO in MODE.  */
int
lra_constraint_offset (int regno, enum machine_mode mode)
{
  gcc_assert (regno < FIRST_PSEUDO_REGISTER);
  /* On a WORDS_BIG_ENDIAN machine, point to the last register of a
     multiple hard register group of scalar integer registers, so that
     for example (reg:DI 0) and (reg:SI 1) will be considered the same
     register.  */
  if (WORDS_BIG_ENDIAN && GET_MODE_SIZE (mode) > UNITS_PER_WORD
      && SCALAR_INT_MODE_P (mode))
    return hard_regno_nregs[regno][mode] - 1;
  return 0;
}

/* Like rtx_equal_p except that it allows a REG and a SUBREG to match
   if they are the same hard reg, and has special hacks for
   autoincrement and autodecrement.  This is specifically intended for
   process_alt_operands to use in determining whether two operands
   match.  X is the operand whose number is the lower of the two.

   It is supposed that X is the output operand and Y is the input
   operand.  */
static bool
operands_match_p (rtx x, rtx y, int y_hard_regno)
{
  int i, offset;
  RTX_CODE code = GET_CODE (x);
  const char *fmt;

  if (x == y)
    return true;
  if ((code == REG || (code == SUBREG && REG_P (SUBREG_REG (x))))
      && (REG_P (y) || (GET_CODE (y) == SUBREG && REG_P (SUBREG_REG (y)))))
    {
      int j;
      
      lra_get_hard_regno_and_offset (x, &i, &offset);
      if (i < 0)
	goto slow;
      i += offset;

      if ((j = y_hard_regno) < 0)
	goto slow;

      i += lra_constraint_offset (i, GET_MODE (x));
      j += lra_constraint_offset (j, GET_MODE (y));

      return i == j;
    }

  /* If two operands must match, because they are really a single
     operand of an assembler insn, then two postincrements are invalid
     because the assembler insn would increment only once.  On the
     other hand, a postincrement matches ordinary indexing if the
     postincrement is the output operand.  */
  if (code == POST_DEC || code == POST_INC || code == POST_MODIFY)
    return operands_match_p (XEXP (x, 0), y, y_hard_regno);

  /* Two preincrements are invalid because the assembler insn would
     increment only once.  On the other hand, a preincrement matches
     ordinary indexing if the preincrement is the input operand.  */
  if (GET_CODE (y) == PRE_DEC || GET_CODE (y) == PRE_INC
      || GET_CODE (y) == PRE_MODIFY)
    return operands_match_p (x, XEXP (y, 0), y_hard_regno);
  
 slow:

  if (code == REG && GET_CODE (y) == SUBREG && REG_P (SUBREG_REG (y))
      && x == SUBREG_REG (y))
    return true;
  if (GET_CODE (y) == REG && code == SUBREG && REG_P (SUBREG_REG (x))
      && SUBREG_REG (x) == y)
    return true;

  /* Now we have disposed of all the cases in which different rtx
     codes can match.  */
  if (code != GET_CODE (y))
    return false;

  /* (MULT:SI x y) and (MULT:HI x y) are NOT equivalent.  */
  if (GET_MODE (x) != GET_MODE (y))
    return false;

  switch (code)
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_FIXED:
      return false;

    case LABEL_REF:
      return XEXP (x, 0) == XEXP (y, 0);
    case SYMBOL_REF:
      return XSTR (x, 0) == XSTR (y, 0);

    default:
      break;
    }

  /* Compare the elements.  If any pair of corresponding elements fail
     to match, return false for the whole things.  */

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      int val, j;
      switch (fmt[i])
	{
	case 'w':
	  if (XWINT (x, i) != XWINT (y, i))
	    return false;
	  break;

	case 'i':
	  if (XINT (x, i) != XINT (y, i))
	    return false;
	  break;

	case 'e':
	  val = operands_match_p (XEXP (x, i), XEXP (y, i), y_hard_regno);
	  if (val == 0)
	    return false;
	  break;

	case '0':
	  break;

	case 'E':
	  if (XVECLEN (x, i) != XVECLEN (y, i))
	    return false;
	  for (j = XVECLEN (x, i) - 1; j >= 0; --j)
	    {
	      val = operands_match_p (XVECEXP (x, i, j), XVECEXP (y, i, j),
				      y_hard_regno);
	      if (val == 0)
		return false;
	    }
	  break;

	  /* It is believed that rtx's at this level will never
	     contain anything but integers and other rtx's, except for
	     within LABEL_REFs and SYMBOL_REFs.  */
	default:
	  gcc_unreachable ();
	}
    }
  return true;
}

/* Pseudos for whose values should be not inherited from input reload
   pseudos because the same hard register should be used for an output
   (or early clobbered) reload pseudo.  */
bitmap_head lra_dont_inherit_pseudos;

/* True if X is a constant that can be forced into the constant pool.
   MODE is the mode of the operand, or VOIDmode if not known.  */
#define CONST_POOL_OK_P(MODE, X)		\
  ((MODE) != VOIDmode				\
   && CONSTANT_P (X)				\
   && GET_CODE (X) != HIGH			\
   && !targetm.cannot_force_const_mem (MODE, X))

/* True if C is a non-empty register class that has too few registers
   to be safely used as a reload target class.  */
#define SMALL_REGISTER_CLASS_P(C)					\
  (reg_class_size [(C)] == 1						\
   || (reg_class_size [(C)] >= 1 && targetm.class_likely_spilled_p (C)))

/* Generate reloads for matching OUT and IN with reg class GOAL_CLASS.
   Add input and output reloads correspondingly to the lists *BEFORE
   and *AFTER.  */
static void
match_reload (int out, int in, enum reg_class goal_class,
	      rtx *before, rtx *after)
{
  rtx new_in_reg, new_out_reg;
  enum machine_mode inmode, outmode;
  rtx in_rtx = *curr_id->operand_loc[in];
  rtx out_rtx = *curr_id->operand_loc[out];

  inmode = lra_get_mode (curr_static_id->operand[in].mode, in_rtx);
  outmode = lra_get_mode (curr_static_id->operand[out].mode, out_rtx);
  if (inmode != outmode)
    {
      /* Don't reuse the pseudos for inheritance -- they will bound.  */
      get_reload_reg (OP_IN, inmode, in_rtx, goal_class, "", &new_in_reg);
      new_out_reg = lra_create_new_reg (outmode, out_rtx, goal_class, "");
    }
  else
    {
      /* We are trying to minimize creating bound pseudos because it
	 does not work well with coalescing.  We create pseudo for out
	 rtx because we always should keep registers with the same
	 original regno have synchronized value (it is not true for
	 out register but it will be corrected by the next insn).
	 
	 Do not reuse register because of the following situation: a <-
	 a op b, and b should be the same as a.
	 
	 Don't generate inheritance for the new register because we
	 can not use the same hard register for the corresponding
	 inheritance pseudo.  */
      new_in_reg = new_out_reg
	= lra_create_new_reg (outmode, out_rtx, goal_class, "");
      bitmap_set_bit (&lra_dont_inherit_pseudos, REGNO (new_in_reg));
    }
  if (new_in_reg != in_rtx)
    {
      push_to_sequence (*before);
      lra_emit_move (new_in_reg, in_rtx);
      *before = get_insns ();
      end_sequence ();
      *curr_id->operand_loc[in] = new_in_reg;
    }
  if (new_out_reg != out_rtx
      && find_reg_note (curr_insn, REG_UNUSED, out_rtx) == NULL_RTX)
    {
      push_to_sequence (*after);
      lra_emit_move (out_rtx, new_out_reg);
      *after = get_insns ();
      end_sequence ();
    }
  *curr_id->operand_loc[out] = new_out_reg;
  if (new_in_reg != new_out_reg)
    {
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "      Bound pseudos r%d and r%d\n",
		 REGNO (new_in_reg), REGNO (new_out_reg));
      lra_bind_pseudos (REGNO (new_in_reg), REGNO (new_out_reg));
    }
  lra_update_dups (curr_id, in, out);
}

/* Return register class which is union of all reg classes in insn
   constraint alternative string starting with P.  */
static enum reg_class
reg_class_from_constraints (const char *p)
{
  int c, len;
  enum reg_class op_class = NO_REGS;

  do
    switch ((c = *p, len = CONSTRAINT_LEN (c, p)), c)
      {
      case '#':
      case ',':
	return op_class;

      case 'p':
	op_class = (reg_class_subunion
		    [op_class][base_reg_class (VOIDmode, ADDRESS, SCRATCH)]);
	break;
	
      case 'g':
      case 'r':
	op_class = reg_class_subunion[op_class][GENERAL_REGS];
	break;
	
      default:
	if (REG_CLASS_FROM_CONSTRAINT (c, p) == NO_REGS)
	  {
#ifdef EXTRA_CONSTRAINT_STR
	    if (EXTRA_ADDRESS_CONSTRAINT (c, p))
	      op_class
		= (reg_class_subunion
		   [op_class][base_reg_class (VOIDmode, ADDRESS, SCRATCH)]);
#endif
	    break;
	  }
	
	op_class
	  = reg_class_subunion[op_class][REG_CLASS_FROM_CONSTRAINT (c, p)];
	break;
      }
  while ((p += len), c);
  return op_class;
}


/* Process a special case insn (register move), return true if we
   don't need to process it anymore.  Return that RTL was changed
   through CHANGE_P.  */
static bool
check_and_process_move (bool *change_p)
{
  int regno;
  rtx set, dest, src, dreg, sr, dr, sreg, new_reg, before, x, scratch_reg;
  enum reg_class dclass, sclass, xclass, rclass, secondary_class;
  secondary_reload_info sri;
  bool in_p, temp_assign_p;

  *change_p = false;
  if ((set = single_set (curr_insn)) == NULL || side_effects_p (set))
    return false;
  dreg = dest = SET_DEST (set);
  sreg = src = SET_SRC (set);
  if (GET_CODE (dest) == SUBREG)
    dreg = SUBREG_REG (dest);
  if (GET_CODE (src) == SUBREG)
    sreg = SUBREG_REG (src);
  if (! REG_P (dreg) || ! REG_P (sreg))
    return false;
  sclass = dclass = NO_REGS;
  dr = get_equiv_substitution (dreg);
  if (dr != dreg)
    dreg = copy_rtx (dr);
  if (REG_P (dreg))
    dclass = get_reg_class (REGNO (dreg));
  if (dclass == ALL_REGS)
    /* We don't know what class we will use -- let it be figured out
       by curr_insn_transform function.  Remember some targets does not
       work with such classes through their implementation of
       machine-dependent hooks like secondary_memory_needed.  */
    return false;
  sr = get_equiv_substitution (sreg);
  if (sr != sreg)
    sreg = copy_rtx (sr);
  if (REG_P (sreg))
    sclass = get_reg_class (REGNO (sreg));
  if (sclass == ALL_REGS)
    /* See comments above.  */
    return false;
#ifdef SECONDARY_MEMORY_NEEDED
  if (dclass != NO_REGS && sclass != NO_REGS)
    {
      rtx after;

      if (SECONDARY_MEMORY_NEEDED (sclass, dclass, GET_MODE (src)))
	{
	  new_reg = get_secondary_mem (GET_MODE (dest));
	  /* If the mode is changed, it should be wider.  */
	  gcc_assert (GET_MODE_SIZE (GET_MODE (new_reg))
		      >= GET_MODE_SIZE (GET_MODE (src)));
	  start_sequence ();
	  if (GET_MODE (new_reg) == GET_MODE (dest))
	    lra_emit_move (dest, new_reg);
	  else
	    lra_emit_move (gen_rtx_SUBREG (GET_MODE (new_reg), dest, 0),
			   new_reg);
	  after = get_insns ();
	  end_sequence ();
	  lra_process_new_insns (curr_insn, NULL_RTX, after, "Inserting the move");
	  start_sequence ();
	  if (GET_MODE (new_reg) == GET_MODE (src))
	    lra_emit_move (new_reg, src);
	  else
	    lra_emit_move (new_reg,
			   gen_rtx_SUBREG (GET_MODE (new_reg), src, 0));
	  before = get_insns ();
	  end_sequence ();
	  lra_process_new_insns (curr_insn, before, NULL_RTX, "Changing on");
	  lra_set_insn_deleted (curr_insn);
	  *change_p = true;
	  return true;
	}
    }
#endif
  sri.prev_sri = NULL;
  sri.icode = CODE_FOR_nothing;
  sri.extra_cost = 0;
  if (dclass != NO_REGS)
    {
      in_p = true;
      rclass = dclass;
      x = sreg;
      xclass = sclass;
    }
  else if (sclass != NO_REGS)
    {
      in_p = false;
      rclass = sclass;
      x = dreg;
      xclass = dclass;
    }
  else
    return false;
  temp_assign_p = false;
  /* Set up hard register for a reload pseudo for hook
     secondary_reload because some targets just ignore pseudos in the
     hook.  */
  if (xclass != NO_REGS
      && REG_P (x) && (regno = REGNO (x)) >= new_regno_start
      && ! bitmap_bit_p (&lra_inheritance_pseudos, regno)
      && lra_get_regno_hard_regno (regno) < 0)
    {
      reg_renumber[regno] = ira_class_hard_regs[xclass][0];
      temp_assign_p = true;
    }
  secondary_class
    = (enum reg_class) targetm.secondary_reload (in_p, x, (reg_class_t) rclass,
						 GET_MODE (src), &sri);
  if (temp_assign_p)
    reg_renumber [REGNO (x)] = -1;
  if (secondary_class == NO_REGS && sri.icode == CODE_FOR_nothing)
    return false;
  *change_p = true;
  new_reg = NULL_RTX;
  if (secondary_class != NO_REGS)
    new_reg = lra_create_new_reg (GET_MODE (sreg), NULL_RTX,
				  secondary_class, "secondary");
  start_sequence ();
  if (sri.icode == CODE_FOR_nothing)
    lra_emit_move (new_reg, sreg);
  else
    {
      enum reg_class scratch_class;

      scratch_class = (reg_class_from_constraints
		       (insn_data[sri.icode].operand[2].constraint));
      scratch_reg = lra_create_new_reg (insn_data[sri.icode].operand[2].mode,
					NULL_RTX, scratch_class, "scratch");
      emit_insn (GEN_FCN (sri.icode) (new_reg != NULL_RTX ? new_reg : dest,
				      sreg, scratch_reg));
    }
  before = get_insns ();
  end_sequence ();
  lra_process_new_insns (curr_insn, before, NULL_RTX, "Inserting the move");
  if (new_reg != NULL_RTX)
    {
      if (GET_CODE (SET_SRC (set)) == SUBREG)
	SUBREG_REG (SET_SRC (set)) = new_reg;
      else
	SET_SRC (set) = new_reg;
    }
  else
    {
      if (lra_dump_file != NULL)
	{
	  fprintf (lra_dump_file, "Deleting move %u\n", INSN_UID (curr_insn));
	  print_rtl_slim (lra_dump_file, curr_insn, curr_insn, -1, 0);
	}
      lra_set_insn_deleted (curr_insn);
      return true;
    }
  return false;
}

/* The following data describe the result of process_alt operands.
   The data are used in curr_insn_transform to generate reloads.  */

/* The chosen reg class which should be used for the corresponding
   operands.  */
static enum reg_class goal_alternative[MAX_RECOG_OPERANDS];
/* True if the operand should be the same as another operand and the
   another operand does not need a reload.  */
static bool goal_alternative_match_win[MAX_RECOG_OPERANDS];
/* True if the operand does not need a reload.  */
static bool goal_alternative_win[MAX_RECOG_OPERANDS];
/* True if the operand can be offsetable memory.  */
static bool goal_alternative_offmemok[MAX_RECOG_OPERANDS];
/* The number of operand to which given operand can be matched to.  */
static int goal_alternative_matches[MAX_RECOG_OPERANDS];
/* True if the insn commutative operands should be swapped.  */
static bool goal_alternative_swapped;
/* The number of elements in the following two arrays.  */
static int goal_early_clobbered_nops_num;
/* Numbers of operands which are early clobbered registers.  */
static int goal_early_clobbered_nops[MAX_RECOG_OPERANDS];
/* Biggest of mode of the early clobbered registers.  */
static enum machine_mode goal_early_clobbered_modes[MAX_RECOG_OPERANDS];
/* The chosen insn alternative.  */
static int goal_alternative_number;

/* The following four variables are used to choose the best insn
   alternative.  They reflect finally characteristics of the best
   alternative.  */

/* Number of necessary reloads and overall cost reflecting the
   previous value and other unplesantness of the best alternative.  */
static int best_losers, best_overall;
/* Number of small register classes used for operands of the best
   alternative.  */
static int best_small_class_operands_num;
/* Overall number reflecting distances of previous reloading the same
   value.  It is used to improve inheritance chances.  */
static int best_reload_sum;

/* True if the current insn should have no correspondingly input or
   output reloads.  */
static bool no_input_reloads_p, no_output_reloads_p;

/* True if swapped the commutative operands in the current insn.  */
static int curr_swapped;

/* Make reloads for addr register in LOC which should be of class CL,
   add reloads to list BEFORE. If AFTER is not null emit insns to set
   the register up after the insn (it is case of inc/dec, modify).  */
static bool
process_addr_reg (rtx *loc, rtx *before, rtx *after, enum reg_class cl)
{
  int regno, final_regno;
  enum reg_class rclass, new_class;
  rtx reg = *loc;
  rtx new_reg;
  enum machine_mode mode;
  bool change_p = false;

  gcc_assert (REG_P (reg));
  final_regno = regno = REGNO (reg);
  if (regno < FIRST_PSEUDO_REGISTER)
    {
      rtx final_reg = reg;
      rtx *final_loc = &final_reg;

      lra_eliminate_reg_if_possible (final_loc);
      final_regno = REGNO (*final_loc);
    }
  /* Use class of hard register after elimination because some targets
     do not recognize virtual hard registers as valid address
     registers.  */
  rclass = get_reg_class (final_regno);
  if ((*loc = get_equiv_substitution (reg)) != reg)
    {
      if (lra_dump_file != NULL)
	{
	  fprintf (lra_dump_file,
		   "Changing pseudo %d in address of insn %u on equiv ",
		   REGNO (reg), INSN_UID (curr_insn));
	  print_value_slim (lra_dump_file, *loc, 1);
	  fprintf (lra_dump_file, "\n");
	}
      *loc = copy_rtx (*loc);
      change_p = true;
    }
  if (*loc != reg || ! in_class_p (final_regno, cl, &new_class))
    {
      mode = GET_MODE (reg);
      reg = *loc;
      if (get_reload_reg (OP_IN, mode, reg, cl, "address", &new_reg))
	{
	  push_to_sequence (*before);
	  lra_emit_move (new_reg, reg);
	  *before = get_insns ();
	  end_sequence ();
	}
      *loc = new_reg;
      if (after != NULL)
	{
	  push_to_sequence (*after);
	  lra_emit_move (reg, new_reg);
	  *after = get_insns ();
	  end_sequence ();
	}
      change_p = true;
    }
  else if (new_class != NO_REGS && rclass != new_class)
    change_class (regno, new_class, "      Change", true);
  return change_p;
}

/* Make reloads for subreg in operand NOP with internal subreg mode
   REG_MODE, add new reloads for further processing.  Return true if
   any reload was generated.  */
static bool
simplify_operand_subreg (int nop, enum machine_mode reg_mode)
{
  int hard_regno;
  rtx before, after;
  enum machine_mode mode;
  rtx reg, new_reg;
  rtx operand = *curr_id->operand_loc[nop];

  /* Remove subregs of memory.  */
  before = after = NULL_RTX;

  if (GET_CODE (operand) != SUBREG)
    return false;
  
  mode = GET_MODE (operand);
  reg = SUBREG_REG (operand);
  if (MEM_P (reg) || (REG_P (reg) && REGNO (reg) < FIRST_PSEUDO_REGISTER))
    {
      alter_subreg (curr_id->operand_loc[nop]);
      return true;
    }
  /* Force reload if this is a constant or PLUS or if there may be a
     problem accessing OPERAND in the outer mode.  */
  if ((REG_P (reg)
       && REGNO (reg) >= FIRST_PSEUDO_REGISTER
       && (hard_regno = lra_get_regno_hard_regno (REGNO (reg))) >= 0
       /* Don't reload paradoxical subregs because we could looping
	  having repeatedly final regno out of hard regs range.  */
       && (hard_regno_nregs[hard_regno][GET_MODE (reg)]
	   >= hard_regno_nregs[hard_regno][mode])
       && simplify_subreg_regno (hard_regno, GET_MODE (reg),
				 SUBREG_BYTE (operand), mode) < 0)
      || CONSTANT_P (reg) || GET_CODE (reg) == PLUS || MEM_P (reg))
    {
      /* Constant mode ???? */
      enum op_type type = curr_static_id->operand[nop].type;
      /* The class will be defined later in curr_insn_transform.  */
      enum reg_class rclass
	= (enum reg_class) targetm.preferred_reload_class (reg, ALL_REGS);

      if (get_reload_reg (type, reg_mode, reg, rclass, NULL, &new_reg)
	  && type != OP_OUT)
	{
	  push_to_sequence (before);
	  lra_emit_move (new_reg, reg);
	  before = get_insns ();
	  end_sequence ();
	}
      if (type != OP_IN)
	{
	  push_to_sequence (after);
	  lra_emit_move (reg, new_reg);
	  after = get_insns ();
	  end_sequence ();
	}
      SUBREG_REG (operand) = new_reg;
      lra_process_new_insns (curr_insn, before, after,
			     "Inserting subreg reload");
      return true;
    }
  return false;
}

/* Return final hard regno (plus offset) which will be after
   elimination.  We do this for matching constraints because the final
   hard regno could have a different class.  */
static int
get_final_hard_regno (int hard_regno, int offset)
{
  if (hard_regno < 0)
    return hard_regno;
  hard_regno += offset;
  return lra_get_elimation_hard_regno (hard_regno);
}

/* Major function to choose the current insn alternative and what
   operands should be reload and how.  If ONLY_ALTERNATIVE is not
   negative we should consider only this alternative.  Return false if
   we can not choose the alternative or find how to reload the
   operands.  */
static bool
process_alt_operands (int only_alternative)
{
  bool ok_p = false;
  int nop, small_class_operands_num, overall, nalt, offset;
  int n_alternatives = curr_static_id->n_alternatives;
  int n_operands = curr_static_id->n_operands;
  /* LOSERS counts those that don't fit this alternative and would
     require loading.  */
  int losers;
  /* REJECT is a count of how undesirable this alternative says it is
     if any reloading is required.  If the alternative matches exactly
     then REJECT is ignored, but otherwise it gets this much counted
     against it in addition to the reloading needed.  Each ? counts
     three times here since we want the disparaging caused by a bad
     register class to only count 1/3 as much.  */
  int reject;
  /* The number of elements in the following two arrays.  */
  int curr_early_clobbered_regs_num;
  /* Numbers of operands which are early clobber registers.  */
  int curr_early_clobbered_nops[MAX_RECOG_OPERANDS];
  /* Biggest of mode of the early clobbered registers.  */
  enum machine_mode curr_early_clobbered_modes[MAX_RECOG_OPERANDS];
  enum reg_class curr_alternative[MAX_RECOG_OPERANDS];
  HARD_REG_SET curr_alternative_set[MAX_RECOG_OPERANDS];
  bool curr_alternative_match_win[MAX_RECOG_OPERANDS];
  bool curr_alternative_win[MAX_RECOG_OPERANDS];
  bool curr_alternative_offmemok[MAX_RECOG_OPERANDS];
  int curr_alternative_matches[MAX_RECOG_OPERANDS];
  rtx op;
  rtx no_subreg_operand[MAX_RECOG_OPERANDS], operand_reg[MAX_RECOG_OPERANDS];
  int hard_regno[MAX_RECOG_OPERANDS];
  enum machine_mode biggest_mode[MAX_RECOG_OPERANDS];
  int reload_sum;

  /* Calculate some data common for all alternatives to speed up the
     function.  */
  for (nop = 0; nop < n_operands; nop++)
    {
      op = no_subreg_operand[nop] = *curr_id->operand_loc[nop];
      lra_get_hard_regno_and_offset (op, &hard_regno[nop], &offset);
      /* The real hard regno of the operand after the allocation.  It
	 can be negative only for registers.  */
      hard_regno[nop] = get_final_hard_regno (hard_regno[nop], offset);
      
      operand_reg[nop] = op;
      biggest_mode[nop] = GET_MODE (operand_reg[nop]);
      if (GET_CODE (operand_reg[nop]) == SUBREG)
	{
	  operand_reg[nop] = SUBREG_REG (operand_reg[nop]);
	  if (GET_MODE_SIZE (biggest_mode[nop])
	      < GET_MODE_SIZE (GET_MODE (operand_reg[nop])))
	    biggest_mode[nop] = GET_MODE (operand_reg[nop]);
	}
      if (REG_P (operand_reg[nop]))
	no_subreg_operand[nop] = operand_reg[nop];
      else
	operand_reg[nop] = NULL_RTX;
    }

  /* The constraints are made of several alternatives.  Each operand's
     constraint looks like foo,bar,... with commas separating the
     alternatives.  The first alternatives for all operands go
     together, the second alternatives go together, etc.

     First loop over alternatives.  */
  for (nalt = 0; nalt < n_alternatives; nalt++)
    {
      /* Loop over operands for one constraint alternative.  */
      if (
#ifdef HAVE_ATTR_enabled
	  (curr_id->alternative_enabled_p != NULL
	   && ! curr_id->alternative_enabled_p[nalt])
	  ||
#endif
	  (only_alternative >= 0 && nalt != only_alternative))
	continue;

      overall = losers = reject = reload_sum = 0;
      for (nop = 0; nop < n_operands; nop++)
	reject += (curr_static_id
		   ->operand_alternative[nalt * n_operands + nop].reject);
      curr_early_clobbered_regs_num = 0;

      for (nop = 0; nop < n_operands; nop++)
	{
	  const char *p;
	  char *end;
	  int len, c, m, i, opalt_num, this_alternative_matches;
	  bool win, did_match, offmemok, early_clobber_p;
	  /* false => this operand can be reloaded somehow for this
	     alternative.  */
	  bool badop;
	  /* false => this operand can be reloaded if the alternative
	     allows regs.  */
	  bool winreg;
	  /* False if a constant forced into memory would be OK for
	     this operand.  */
	  bool constmemok;
	  enum reg_class this_alternative;
	  HARD_REG_SET this_alternative_set;
	  bool this_alternative_match_win, this_alternative_win;
	  bool this_alternative_offmemok;
	  int invalidate_m;
	  enum machine_mode mode;

	  opalt_num = nalt * n_operands + nop;
	  if (curr_static_id->operand_alternative[opalt_num].anything_ok)
	    {
	      /* Fast track for no constraints at all.  */
	      curr_alternative[nop] = NO_REGS;
	      CLEAR_HARD_REG_SET (curr_alternative_set[nop]);
	      curr_alternative_win[nop] = true;
	      curr_alternative_match_win[nop] = false;
	      curr_alternative_offmemok[nop] = false;
	      curr_alternative_matches[nop] = -1;
	      continue;
	    }
      
	  op = no_subreg_operand[nop];
	  mode = GET_MODE (*curr_id->operand_loc[nop]);

	  win = did_match = winreg = offmemok = constmemok = false;
	  badop = true;
      
	  early_clobber_p = false;
	  p = curr_static_id->operand_alternative[opalt_num].constraint;
      
	  this_alternative = NO_REGS;
	  /* We update set of possible hard regs besides its class
	     because reg class might be inaccurate.  For example,
	     union of LO_REGS (l), HI_REGS(h), and STACK_REG(k) in ARM
	     is translated in HI_REGS because classes are merged by
	     pairs and there is no accurate intermediate class.  */
	  CLEAR_HARD_REG_SET (this_alternative_set);
	  this_alternative_win = false;
	  this_alternative_match_win = false;
	  this_alternative_offmemok = false;
	  this_alternative_matches = -1;
  
	  invalidate_m = -1;

	  /* An empty constraint should be excluded by the fast
	     track.  */
	  gcc_assert (*p != 0 && *p != ',');
  
	  /* Scan this alternative's specs for this operand; set WIN
	     if the operand fits any letter in this alternative.
	     Otherwise, clear BADOP if this operand could fit some
	     letter after reloads, or set WINREG if this operand could
	     fit after reloads provided the constraint allows some
	     registers.  */
  
	  do
	    switch ((c = *p, len = CONSTRAINT_LEN (c, p)), c)
	      {
	      case '\0':
		len = 0;
		break;
	      case ',':
		c = '\0';
		break;
	
	      case '=':  case '+':  case '*': case '?': case '!':
		break;
	
	      case '%':
		/* We only support one commutative marker, the first
		   one.  We already set commutative above.  */
		break;
	
	      case '&':
		early_clobber_p = true;
		break;
	
	      case '#':
		/* Ignore rest of this alternative.  */
		c = '\0';
		break;
	
	      case '0':  case '1':  case '2':  case '3':  case '4':
	      case '5':  case '6':  case '7':  case '8':  case '9':
		{
		  int m_hregno, m_offset;

		  m = strtoul (p, &end, 10);
		  p = end;
		  len = 0;
		  gcc_assert (nop > m);
	  
		  this_alternative_matches = m;
		  lra_get_hard_regno_and_offset (*curr_id->operand_loc[m],
						 &m_hregno, &m_offset);
		  m_hregno = get_final_hard_regno (m_hregno, m_offset);
		  /* We are supposed to match a previous operand.  If
		     we do, we win if that one did.  If we do not,
		     count both of the operands as losers.  (This is
		     too conservative, since most of the time only a
		     single reload insn will be needed to make the two
		     operands win.  As a result, this alternative may
		     be rejected when it is actually desirable.)  */
		  /* If it conflicts with others.  */
		  if (operands_match_p (*curr_id->operand_loc[nop],
					*curr_id->operand_loc[m], m_hregno))
		    {
		      /* If we are matching a non-offsettable address
			 where an offsettable address was expected,
			 then we must reject this combination, because
			 we can't reload it.  */
		      if (curr_alternative_offmemok[m]
			  && MEM_P (*curr_id->operand_loc[m])
			  && curr_alternative[m] == NO_REGS
			  && ! curr_alternative_win[m])
			continue;
	      
		      did_match = curr_alternative_win[m];
		    }
		  else
		    {
		      /* Operands don't match.  */
		      /* Retroactively mark the operand we had to
			 match as a loser, if it wasn't already and it
			 wasn't matched to a register constraint (e.g
			 it might be matched by memory).  */
		      if (curr_alternative_win[m]
			  && (operand_reg[m] == NULL_RTX || hard_regno[m] < 0))
			losers++;
		      invalidate_m = m;
		      if (curr_alternative[m] == NO_REGS)
			continue;
	      
		      /* We prefer no matching alternatives because it
			 gives more freedom in RA.  */
		      if (operand_reg[nop] == NULL_RTX
			  || (find_regno_note (curr_insn, REG_DEAD,
					       REGNO (operand_reg[nop]))
			      == NULL_RTX))
			reject += 2;
		    }
		  /* This can be fixed with reloads if the operand we
		     are supposed to match can be fixed with
		     reloads.  */
		  badop = false;
		  this_alternative = curr_alternative[m];
		  COPY_HARD_REG_SET (this_alternative_set,
				     curr_alternative_set[m]);

		  /* If we have to reload this operand and some
		     previous operand also had to match the same thing
		     as this operand, we don't know how to do that.
		     So reject this alternative.  */
		  if (! did_match)
		    for (i = 0; i < nop; i++)
		      if (curr_alternative_matches[i]
			  == this_alternative_matches)
			badop = true;
	  
		  break;
		}
	
	      case 'p':
		this_alternative
		  = (reg_class_subunion
		     [this_alternative]
		     [base_reg_class (VOIDmode, ADDRESS, SCRATCH)]);
		IOR_HARD_REG_SET (this_alternative_set,
				  reg_class_contents
				  [base_reg_class
				   (VOIDmode, ADDRESS, SCRATCH)]);
		win = true;
		badop = false;
		break;
	
	      case TARGET_MEM_CONSTRAINT:
		if (MEM_P (op)
		    || (REG_P (op)
			&& REGNO (op) >= FIRST_PSEUDO_REGISTER
			&& in_mem_p (REGNO (op))))
		  win = true;
		if (CONST_POOL_OK_P (mode, op))
		  badop = false;
		constmemok = true;
		break;
	
	      case '<':
		if (MEM_P (op)
		    && (GET_CODE (XEXP (op, 0)) == PRE_DEC
			|| GET_CODE (XEXP (op, 0)) == POST_DEC))
		  win = true;
		break;
	
	      case '>':
		if (MEM_P (op)
		    && (GET_CODE (XEXP (op, 0)) == PRE_INC
			|| GET_CODE (XEXP (op, 0)) == POST_INC))
		  win = true;
		break;
	
		/* Memory op whose address is not
		   offsettable.  */
	      case 'V':
		if (MEM_P (op)
		    && ! offsettable_nonstrict_memref_p (op))
		  win = true;
		break;
	
		/* Memory operand whose address is offsettable.  */
	      case 'o':
		if ((MEM_P (op)
		     && offsettable_nonstrict_memref_p (op))
		    || (REG_P (op)
			&& REGNO (op) >= FIRST_PSEUDO_REGISTER
			&& in_mem_p (REGNO (op))))
		  win = true;
		if (CONST_POOL_OK_P (mode, op) || MEM_P (op))
		  badop = false;
		constmemok = true;
		offmemok = true;
		break;
	
	      case 'E':
	      case 'F':
		if (GET_CODE (op) == CONST_DOUBLE
		    || (GET_CODE (op) == CONST_VECTOR
			&& (GET_MODE_CLASS (mode) == MODE_VECTOR_FLOAT)))
		  win = true;
		break;
	
	      case 'G':
	      case 'H':
		if (GET_CODE (op) == CONST_DOUBLE
		    && CONST_DOUBLE_OK_FOR_CONSTRAINT_P (op, c, p))
		  win = true;
		break;
	
	      case 's':
		if (CONST_INT_P (op)
		    || (GET_CODE (op) == CONST_DOUBLE && mode == VOIDmode))
		  break;
	      case 'i':
		if (CONSTANT_P (op)
		    && (! flag_pic || LEGITIMATE_PIC_OPERAND_P (op)))
		  win = true;
		break;
	
	      case 'n':
		if (CONST_INT_P (op)
		    || (GET_CODE (op) == CONST_DOUBLE && mode == VOIDmode))
		  win = true;
		break;
	
	      case 'I':
	      case 'J':
	      case 'K':
	      case 'L':
	      case 'M':
	      case 'N':
	      case 'O':
	      case 'P':
		if (CONST_INT_P (op)
		    && CONST_OK_FOR_CONSTRAINT_P (INTVAL (op), c, p))
		  win = true;
		break;
	
	      case 'X':
		/* This constraint should be excluded by the fast
		   track.  */
		gcc_unreachable ();
		break;
	
	      case 'g':
		if (/* A PLUS is never a valid operand, but LRA can
		       make it from a register when eliminating
		       registers.  */
		    GET_CODE (op) != PLUS
		    && (! CONSTANT_P (op) || ! flag_pic
			|| LEGITIMATE_PIC_OPERAND_P (op))
		    && (! REG_P (op)
			|| (REGNO (op) >= FIRST_PSEUDO_REGISTER
			    && in_mem_p (REGNO (op)))))
		  win = true;
		/* Drop through into 'r' case.  */
	
	      case 'r':
		this_alternative
		  = reg_class_subunion[this_alternative][GENERAL_REGS];
		IOR_HARD_REG_SET (this_alternative_set,
				  reg_class_contents[GENERAL_REGS]);
		goto reg;
	
	      default:
		if (REG_CLASS_FROM_CONSTRAINT (c, p) == NO_REGS)
		  {
#ifdef EXTRA_CONSTRAINT_STR
		    if (EXTRA_MEMORY_CONSTRAINT (c, p))
		      {
			if (EXTRA_CONSTRAINT_STR (op, c, p))
			  win = true;
			/* For regno_equiv_mem_loc we have to
			   check.  */
			else if (REG_P (op)
				 && REGNO (op) >= FIRST_PSEUDO_REGISTER
				 && in_mem_p (REGNO (op)))
			  {
			    /* We could transform spilled memory
			       finally to indirect memory.  */
			    if (EXTRA_CONSTRAINT_STR (get_indirect_mem (mode),
						      c, p))
			      win = true;
			  }
		
			/* If we didn't already win, we can reload
			   constants via force_const_mem, and other
			   MEMs by reloading the address like for
			   'o'.  */
			if (CONST_POOL_OK_P (mode, op) || MEM_P (op))
			  badop = false;
			constmemok = true;
			offmemok = true;
			break;
		      }
		    if (EXTRA_ADDRESS_CONSTRAINT (c, p))
		      {
			if (EXTRA_CONSTRAINT_STR (op, c, p))
			  win = true;
		
			/* If we didn't already win, we can reload the
			   address into a base register.  */
			this_alternative
			  = (reg_class_subunion
			     [this_alternative]
			     [base_reg_class (VOIDmode, ADDRESS, SCRATCH)]);
			IOR_HARD_REG_SET
			  (this_alternative_set,
			   reg_class_contents[base_reg_class
					      (VOIDmode, ADDRESS, SCRATCH)]);
			badop = false;
			break;
		      }
	    
		    if (EXTRA_CONSTRAINT_STR (op, c, p))
		      win = true;
		    else if (REG_P (op)
			     && REGNO (op) >= FIRST_PSEUDO_REGISTER
			     && in_mem_p (REGNO (op)))
		      {
			/* We could transform spilled memory finally
			   to indirect memory.  */
			if (EXTRA_CONSTRAINT_STR (get_indirect_mem (mode),
						  c, p))
			  win = true;
		      }
#endif
		    break;
		  }
	
		this_alternative
		  = (reg_class_subunion
		     [this_alternative][REG_CLASS_FROM_CONSTRAINT (c, p)]);
		IOR_HARD_REG_SET
		  (this_alternative_set,
		   reg_class_contents[REG_CLASS_FROM_CONSTRAINT (c, p)]);
	      reg:
		if (mode == BLKmode)
		  break;
		winreg = true;
		if (REG_P (op))
		  {
		    if (hard_regno[nop] >= 0
			&& in_hard_reg_set_p (this_alternative_set,
					      mode, hard_regno[nop]))
		      win = true;
		    else if (hard_regno[nop] < 0
			     && in_class_p (REGNO (op),
					    this_alternative, NULL))
		      win = true;
		  }
		break;
	      }
	  while ((p += len), c);
  
	  /* If this operand could be handled with a reg, and some reg
	     is allowed, then this operand can be handled.  */
	  if (winreg && this_alternative != NO_REGS)
	    badop = false;
  
	  /* Record which operands fit this alternative.  */
	  if (win)
	    {
	      this_alternative_win = true;
	      if (operand_reg[nop] != NULL_RTX && hard_regno[nop] < 0)
		/* Prefer won reg to spilled pseudo under other equal
		   conditions.  */
		reject++;
	    }
	  else if (did_match)
	    this_alternative_match_win = true;
	  else
	    {
	      int const_to_mem = 0;
	      bool no_regs_p;

	      no_regs_p
		= (this_alternative == NO_REGS
		   || (hard_reg_set_subset_p
		       (reg_class_contents[this_alternative],
			lra_no_alloc_regs)));
	      this_alternative_offmemok = offmemok;
	      /* If the operand is dying, has a matching constraint,
		 and satisfies constraints of the matched operand
		 which failed to satisfy the own constraints, we do
		 not need to generate a reload insn for this
		 operand.  */
	      if (this_alternative_matches < 0
		  || curr_alternative_win[this_alternative_matches]
		  || ! REG_P (op)
		  || find_regno_note (curr_insn, REG_DEAD,
				      REGNO (op)) == NULL_RTX
		  || ((hard_regno[nop] < 0
		       || ! in_hard_reg_set_p (this_alternative_set,
					       mode, hard_regno[nop]))
		      && (hard_regno[nop] >= 0
			  || ! in_class_p (REGNO (op),
					   this_alternative, NULL))))
		losers++;
	      if (operand_reg[nop] != NULL_RTX)
		{
		  int last_reload = (lra_reg_info[ORIGINAL_REGNO
						  (operand_reg[nop])]
				     .last_reload);

		  if (last_reload > bb_reload_num)
		    reload_sum += last_reload;
		  else
		    reload_sum += bb_reload_num;
		}
	      if (badop
		  /* Alternative loses if it has no regs for a reg
		     operand.  */
		  || (REG_P (op) && no_regs_p
		      && this_alternative_matches < 0))
		goto fail;
      
	      /* If this is a constant that is reloaded into the
		 desired class by copying it to memory first, count
		 that as another reload.  This is consistent with
		 other code and is required to avoid choosing another
		 alternative when the constant is moved into memory.
		 Note that the test here is precisely the same as in
		 the code below that calls force_const_mem.  */
	      if (CONST_POOL_OK_P (mode, op)
		  && ((targetm.preferred_reload_class
		       (op, this_alternative) == NO_REGS)
		      || no_input_reloads_p)
		  && lra_get_mode (curr_static_id->operand[nop].mode,
				   op) != VOIDmode)
		{
		  const_to_mem = 1;
		  if (! no_regs_p)
		    losers++;
		}
      
	      /* Alternative loses if it requires a type of reload not
		 permitted for this insn.  We can always reload
		 objects with a REG_UNUSED note.  */
	      if ((curr_static_id->operand[nop].type != OP_IN
		   && no_output_reloads_p
		   && ! find_reg_note (curr_insn, REG_UNUSED, op))
		  || (curr_static_id->operand[nop].type != OP_OUT
		      && no_input_reloads_p && ! const_to_mem))
		goto fail;
      
	      /* If we can't reload this value at all, reject this
		 alternative.  Note that we could also lose due to
		 LIMIT_RELOAD_CLASS, but we don't check that here.  */
	      if (! CONSTANT_P (op) && ! no_regs_p)
		{
		  if (targetm.preferred_reload_class
		      (op, this_alternative) == NO_REGS)
		    reject = 600;
	  
		  if (curr_static_id->operand[nop].type == OP_OUT
		      && (targetm.preferred_output_reload_class
			  (op, this_alternative) == NO_REGS))
		    reject = 600;
		}
      
	      /* We prefer to reload pseudos over reloading other
		 things, since such reloads may be able to be
		 eliminated later.  So bump REJECT in other cases.
		 Don't do this in the case where we are forcing a
		 constant into memory and it will then win since we
		 don't want to have a different alternative match
		 then.  */
	      if (! (REG_P (op)
		     && REGNO (op) >= FIRST_PSEUDO_REGISTER)
		  && ! (const_to_mem && constmemok)
		  /* We can reload the address instead of memory (so
		     do not punish it).  It is preferable to do to
		     avoid cycling in some cases.  */
		  && ! (MEM_P (op) && offmemok))
		reject += 2;
      
	      /* Input reloads can be inherited more often than output
		 reloads can be removed, so penalize output
		 reloads.  */
	      if (curr_static_id->operand[nop].type != OP_IN)
		reject++;
	      /* SUBREGS ??? */
	      if (this_alternative_matches >= 0)
		{
		  /* ?!? */
		}
	      else if (no_regs_p && ! this_alternative_offmemok && ! constmemok)
		goto fail;
	    }
  
	  if (early_clobber_p)
	    reject++;
	  /* ??? Should we update the cost because early clobber
	     register reloads or it is a rare thing to be worth to do
	     it.  */
	  overall = losers * 6 + reject;
	  if ((best_losers == 0 || losers != 0) && best_overall < overall)
	    goto fail;

	  curr_alternative[nop] = this_alternative;
	  COPY_HARD_REG_SET (curr_alternative_set[nop], this_alternative_set);
	  curr_alternative_win[nop] = this_alternative_win;
	  curr_alternative_match_win[nop] = this_alternative_match_win;
	  curr_alternative_offmemok[nop] = this_alternative_offmemok;
	  curr_alternative_matches[nop] = this_alternative_matches;
  
	  if (invalidate_m >= 0 && ! this_alternative_win)
	    curr_alternative_win[invalidate_m] = false;
  
	  if (early_clobber_p && operand_reg[nop] != NULL_RTX)
	    {
	      curr_early_clobbered_nops[curr_early_clobbered_regs_num] = nop;
	      curr_early_clobbered_modes[curr_early_clobbered_regs_num++]
		= biggest_mode[nop];
	    }
	}
      small_class_operands_num = 0;
      for (nop = 0; nop < n_operands; nop++)
	/* If this alternative can be made to work by reloading, and
	   it needs less reloading than the others checked so far,
	   record it as the chosen goal for reloading.  */
	small_class_operands_num
	  += SMALL_REGISTER_CLASS_P (curr_alternative[nop]) ? 1 : 0;

      if ((best_losers != 0 && losers == 0)
	  || (((best_losers == 0 && losers == 0)
	       || (best_losers != 0 && losers != 0))
	      && (best_overall > overall
		  || (best_overall == overall
		      /* If the cost of the reloads is the same,
			 prefer alternative which requires minimal
			 number of small register classes for the
			 operands.  This improves chances of reloads
			 for insn requiring small register
			 classes.  */
		      && (small_class_operands_num
			  < best_small_class_operands_num
			  || (small_class_operands_num
			      == best_small_class_operands_num
			      && best_reload_sum < reload_sum))))))
	{
	  for (nop = 0; nop < n_operands; nop++)
	    {
	      goal_alternative_win[nop] = curr_alternative_win[nop];
	      goal_alternative_match_win[nop]
		= curr_alternative_match_win[nop];
	      goal_alternative_matches[nop] = curr_alternative_matches[nop];
	      goal_alternative[nop] = curr_alternative[nop];
	      goal_alternative_offmemok[nop] = curr_alternative_offmemok[nop];
	      goal_early_clobbered_nops[nop] = curr_early_clobbered_nops[nop];
	      goal_early_clobbered_modes[nop] = curr_early_clobbered_modes[nop];
	    }
	  goal_early_clobbered_nops_num = curr_early_clobbered_regs_num;
	  goal_alternative_swapped = curr_swapped;
	  best_overall = overall;
	  best_losers = losers;
	  best_small_class_operands_num = small_class_operands_num;
	  best_reload_sum = reload_sum;
	  goal_alternative_number = nalt;
	}
      ok_p = true;
      if (losers == 0)
	/* Everything is satisfied.  Do not process alternatives
	   anymore.  */ 
	break;
    fail:
      ;
    }
  return ok_p;
}

/* Return 1 if ADDR is a valid memory address for mode MODE
   in address space AS, and check that each pseudo reg has the
   proper kind of hard reg.  */
static int
valid_address_p (enum machine_mode mode ATTRIBUTE_UNUSED,
		 rtx addr, addr_space_t as)
{
#ifdef GO_IF_LEGITIMATE_ADDRESS
  gcc_assert (ADDR_SPACE_GENERIC_P (as));
  GO_IF_LEGITIMATE_ADDRESS (mode, addr, win);
  return 0;
  
 win:
  return 1;
#else
  return targetm.addr_space.legitimate_address_p (mode, addr, 0, as);
#endif
}

/* Make reload base reg + disp from address AD of memory with MODE
   into a new pseudo.  Return the new pseudo.  */
static rtx
base_plus_disp_to_reg (enum machine_mode mode, struct address *ad)
{
  enum reg_class cl;
  rtx new_reg;

  gcc_assert (ad->base_reg_loc != NULL && ad->disp_loc != NULL);
  cl = base_reg_class (mode, ad->base_outer_code, ad->index_code);
  new_reg = lra_create_new_reg (Pmode, NULL_RTX, cl, "base + disp");
  lra_emit_add (new_reg, *ad->base_reg_loc, *ad->disp_loc);
  return new_reg;
}

/* Make substitution in address AD with location ADDR_LOC.  Update AD
   and ADDR_LOC if it is necessary.  Return true if a substitution was
   made.  */
static bool
equiv_address_substitution (struct address *ad, rtx *addr_loc,
			    enum machine_mode mode, enum rtx_code code)
{
  rtx base_reg, new_base_reg, index_reg, new_index_reg;
  HOST_WIDE_INT disp, scale;
  bool change_p;

  if (ad->base_reg_loc == NULL)
    base_reg = new_base_reg = NULL_RTX;
  else
    {
      base_reg = *ad->base_reg_loc;
      new_base_reg = get_equiv_substitution (base_reg);
    }
  if (ad->index_reg_loc == NULL)
    index_reg = new_index_reg = NULL_RTX;
  else
    {
      index_reg = *ad->index_reg_loc;
      new_index_reg = get_equiv_substitution (index_reg);
    }
  if (base_reg == new_base_reg && index_reg == new_index_reg)
    return false;
  disp = 0;
  change_p = false;
  if (lra_dump_file != NULL)
    {
      fprintf (lra_dump_file, "Changing address in insn %d ",
	       INSN_UID (curr_insn));
      print_value_slim (lra_dump_file, *addr_loc, 1);
    }
  if (base_reg != new_base_reg)
    {
      if (REG_P (new_base_reg))
	{
	  *ad->base_reg_loc = new_base_reg;
	  change_p = true;
	}
      else if (GET_CODE (new_base_reg) == PLUS
	       && REG_P (XEXP (new_base_reg, 0))
	       && CONST_INT_P (XEXP (new_base_reg, 1)))
	{
	  disp += INTVAL (XEXP (new_base_reg, 1));
	  *ad->base_reg_loc = XEXP (new_base_reg, 0);
	  change_p = true;
	}
      if (ad->base_reg_loc2 != NULL)
	*ad->base_reg_loc2 = *ad->base_reg_loc;
    }
  scale = 1;
  if (ad->index_loc != NULL && GET_CODE (*ad->index_loc) == MULT)
    {
      gcc_assert (CONST_INT_P (XEXP (*ad->index_loc, 1)));
      scale = INTVAL (XEXP (*ad->index_loc, 1));
    }
  if (index_reg != new_index_reg)
    {
      if (REG_P (new_index_reg))
	{
	  *ad->index_reg_loc = new_index_reg;
	  change_p = true;
	}
      else if (GET_CODE (new_index_reg) == PLUS
	       && REG_P (XEXP (new_index_reg, 0))
	       && CONST_INT_P (XEXP (new_index_reg, 1)))
	{
	  disp += INTVAL (XEXP (new_index_reg, 1)) * scale;
	  *ad->index_reg_loc = XEXP (new_index_reg, 0);
	  change_p = true;
	}
    }
  if (disp != 0)
    {
      if (ad->disp_loc != NULL)
	*ad->disp_loc = plus_constant (*ad->disp_loc, disp);
      else
	{
	  *addr_loc = gen_rtx_PLUS (Pmode, *addr_loc, GEN_INT (disp));
	  extract_address_regs (mode, addr_loc, code, ad);
	}
      change_p = true;
    }
  if (lra_dump_file != NULL)
    {
      if (! change_p)
	fprintf (lra_dump_file, " -- no change\n");
      else
	{
	  fprintf (lra_dump_file, " on equiv ");
	  print_value_slim (lra_dump_file, *addr_loc, 1);
	  fprintf (lra_dump_file, "\n");
	}
    }
  return change_p;
}

/* Major function to make reloads for address in operand NOP.  Add to
   reloads to the list *BEFORE and *AFTER.  We might need to add
   reloads to *AFTER because of inc/dec, {pre, post} modify in the
   address.  Return true for any RTL change.  */
static bool
process_address (int nop, rtx *before, rtx *after)
{
  struct address ad;
  enum machine_mode mode;
  rtx new_reg, *addr_loc, saved_index_reg, saved_base_reg, saved_base_reg2;
  bool ok_p;
  addr_space_t as;
  rtx op = *curr_id->operand_loc[nop];
  const char *constraint = curr_static_id->operand[nop].constraint;
  bool change_p;
  enum rtx_code code;

  if (constraint[0] == 'p'
      || EXTRA_ADDRESS_CONSTRAINT (constraint[0], constraint))
    {
      mode = VOIDmode;
      addr_loc = curr_id->operand_loc[nop];
      as = ADDR_SPACE_GENERIC;
      code = ADDRESS;
    }
  else if (MEM_P (op))
    {
      mode = GET_MODE (op);
      addr_loc = &XEXP (op, 0);
      as = MEM_ADDR_SPACE (op);
      code = MEM;
    }
  else if (GET_CODE (op) == SUBREG
	   && MEM_P (SUBREG_REG (op)))
    {
      mode = GET_MODE (SUBREG_REG (op));
      addr_loc = &XEXP (SUBREG_REG (op), 0);
      as = MEM_ADDR_SPACE (SUBREG_REG (op));
      code = MEM;
    }
  else
    return false;
  if (GET_CODE (*addr_loc) == AND)
    addr_loc = &XEXP (*addr_loc, 0);
  extract_address_regs (mode, addr_loc, code, &ad);
  saved_base_reg = saved_base_reg2 = saved_index_reg = NULL_RTX;
  change_p = equiv_address_substitution (&ad, addr_loc, mode, code);
  if (ad.base_reg_loc != NULL)
    {
      if (process_addr_reg (ad.base_reg_loc, before,
			    (ad.base_modify_p
			     && find_regno_note (curr_insn, REG_DEAD,
						 REGNO (*ad.base_reg_loc)) == NULL
			     ? after : NULL),
			    base_reg_class (mode, ad.base_outer_code,
					    ad.index_code)))
	change_p = true;
      if (ad.base_reg_loc2 != NULL)
	*ad.base_reg_loc2 = *ad.base_reg_loc;
      saved_base_reg = *ad.base_reg_loc;
      lra_eliminate_reg_if_possible (ad.base_reg_loc);
      if (ad.base_reg_loc2 != NULL)
	{
	  saved_base_reg2 = *ad.base_reg_loc2;
	  lra_eliminate_reg_if_possible (ad.base_reg_loc2);
	}
    }
  if (ad.index_reg_loc != NULL)
    {
      if (process_addr_reg (ad.index_reg_loc, before, NULL, INDEX_REG_CLASS))
	change_p = true;
      saved_index_reg = *ad.index_reg_loc;
      lra_eliminate_reg_if_possible (ad.index_reg_loc);
    }
  /* Some ports do not check displacements for virtual registers -- so
     we substitute them temporarily by real registers.  */
  ok_p = valid_address_p (mode, *addr_loc, as);
  if (saved_base_reg != NULL_RTX)
    {
      *ad.base_reg_loc = saved_base_reg;
      if (saved_base_reg2 != NULL_RTX)
	*ad.base_reg_loc = saved_base_reg2;
    }
  if (saved_index_reg != NULL_RTX)
    *ad.index_reg_loc = saved_index_reg;
  if (ok_p
      /* The following addressing is checked by constraints and
	 usually target specific legitimate address hooks do not
	 consider them valid.  */
      || GET_CODE (*addr_loc) == POST_DEC || GET_CODE (*addr_loc) == POST_INC
      || GET_CODE (*addr_loc) == PRE_DEC || GET_CODE (*addr_loc) == PRE_DEC
      || GET_CODE (*addr_loc) == PRE_MODIFY
      || GET_CODE (*addr_loc) == POST_MODIFY
      /* In this case we can not do anything becuase if it is wrong
	 that is because of wrong displacement.  Remember that any
	 address was legitimate in non-strict sense before LRA.  */
      || ad.disp_loc == NULL)
    return change_p;

  /* Addresses were legitimate before LRA.  So if the address has
     two registers than it can have two of them.  We should also
     not worry about scale for the same reason.  */
  push_to_sequence (*before);
  if (ad.base_reg_loc == NULL)
    {
      if (ad.index_reg_loc == NULL)
	{
	  /* disp => new_base  */
	  enum reg_class cl = base_reg_class (mode, SCRATCH, SCRATCH);
	  
	  new_reg = lra_create_new_reg (Pmode, NULL_RTX, cl, "disp");
	  lra_emit_move (new_reg, *ad.disp_loc);
	  *ad.disp_loc = new_reg;
	}
      else
	{
	  /* index * scale + disp => new base + index * scale  */
	  enum reg_class cl = base_reg_class (mode, SCRATCH, SCRATCH);

	  gcc_assert (INDEX_REG_CLASS != NO_REGS);
	  new_reg = lra_create_new_reg (Pmode, NULL_RTX, cl, "disp");
	  gcc_assert (GET_CODE (*addr_loc) == PLUS);
	  lra_emit_move (new_reg, *ad.disp_loc);
	  if (CONSTANT_P (XEXP (*addr_loc, 1)))
	    XEXP (*addr_loc, 1) = XEXP (*addr_loc, 0);
	  XEXP (*addr_loc, 0) = new_reg;
	}
    }
  else if (ad.index_reg_loc == NULL)
    {
      bool try_index_p = false;

      if (INDEX_REG_CLASS != NO_REGS)
	{
	  rtx disp = *ad.disp_loc;

	  *ad.disp_loc = regno_reg_rtx[ira_class_hard_regs[INDEX_REG_CLASS][0]];
	  try_index_p = valid_address_p (mode, *addr_loc, as);
	  *ad.disp_loc = disp;
	}
      if (try_index_p)
	{
	  /* base + disp => base + new index  */
	  new_reg = lra_create_new_reg (Pmode, NULL_RTX, INDEX_REG_CLASS, "disp");
	  lra_emit_move (new_reg, *ad.disp_loc);
	  *ad.disp_loc = new_reg;
	}
      else
	{
	  /* base + disp => new base  */
	  new_reg = base_plus_disp_to_reg (mode, &ad);
	  *addr_loc = new_reg;
	}
    }
  else
    {
      /* base + scale * index + disp => new base + scale * index  */
      new_reg = base_plus_disp_to_reg (mode, &ad);
      *addr_loc = gen_rtx_PLUS (Pmode, new_reg, *ad.index_loc);
    }
  *before = get_insns ();
  end_sequence ();
  return true;
}

/* Emit insns to reload VALUE into a new register.  VALUE is an
   autoincrement or autodecrement RTX whose operand is a register or
   memory location; so reloading involves incrementing that location.
   IN is either identical to VALUE, or some cheaper place to reload
   value being incremented/decremented from.

   INC_AMOUNT is the number to increment or decrement by (always
   positive and ignored for POST_MODIFY/PRE_MODIFY).

   Return pseudo containing the result.  */
static rtx
emit_inc (enum reg_class new_rclass, rtx in, rtx value, int inc_amount)
{
  /* REG or MEM to be copied and incremented.  */
  rtx incloc = XEXP (value, 0);
  /* Nonzero if increment after copying.  */
  int post = (GET_CODE (value) == POST_DEC || GET_CODE (value) == POST_INC
              || GET_CODE (value) == POST_MODIFY);
  rtx last;
  rtx inc;
  rtx add_insn;
  int code;
  rtx real_in = in == value ? incloc : in;
  rtx result;
  bool plus_p = true;

  if (GET_CODE (value) == PRE_MODIFY || GET_CODE (value) == POST_MODIFY)
    {
      gcc_assert (GET_CODE (XEXP (value, 1)) == PLUS
		  || GET_CODE (XEXP (value, 1)) == MINUS);
      gcc_assert (rtx_equal_p (XEXP (XEXP (value, 1), 0), XEXP (value, 0)));
      plus_p = GET_CODE (XEXP (value, 1)) == PLUS;
      inc = XEXP (XEXP (value, 1), 1);
    }
  else
    {
      if (GET_CODE (value) == PRE_DEC || GET_CODE (value) == POST_DEC)
        inc_amount = -inc_amount;

      inc = GEN_INT (inc_amount);
    }

  if (! post && REG_P (incloc))
    result = incloc;
  else
    result = lra_create_new_reg (GET_MODE (value), value, new_rclass,
				 "INC/DEC result");

  /* If this is post-increment, first copy the location to the reload reg.  */
  if (post && real_in != result)
    emit_insn (gen_move_insn (result, real_in));

  /* We suppose that there are insns to add/sub with the constant
     increment permitted in {PRE/POST)_{DEC/INC/MODIFY}.  At least the
     old reload worked with this assumption.  If the assumption
     becomes wrong, we should use approach in function
     base_plus_disp_to_reg.  */
  if (in == value)
    {
      /* See if we can directly increment INCLOC.  */
      last = get_last_insn ();
      add_insn = emit_insn (plus_p
			    ? gen_add2_insn (incloc, inc)
			    : gen_sub2_insn (incloc, inc));

      code = recog_memoized (add_insn);
      /* We should restore recog_data for the current insn.  */
      if (code >= 0)
	{
	  if (! post && result != incloc)
	    emit_insn (gen_move_insn (result, incloc));
	  return result;
	}
      delete_insns_since (last);
    }

  /* If couldn't do the increment directly, must increment in RESULT.
     The way we do this depends on whether this is pre- or
     post-increment.  For pre-increment, copy INCLOC to the reload
     register, increment it there, then save back.  */
  if (! post)
    {
      if (real_in != result)
	emit_insn (gen_move_insn (result, real_in));
      if (plus_p)
	emit_insn (gen_add2_insn (result, inc));
      else
	emit_insn (gen_sub2_insn (result, inc));
      if (result != incloc)
	emit_insn (gen_move_insn (incloc, result));
    }
  else
    {
      /* Postincrement.

	 Because this might be a jump insn or a compare, and because
	 RESULT may not be available after the insn in an input
	 reload, we must do the incrementation before the insn being
	 reloaded for.

	 We have already copied IN to RESULT.  Increment the copy in
	 RESULT, save that back, then decrement RESULT so it has
	 the original value.  */
      if (plus_p)
	emit_insn (gen_add2_insn (result, inc));
      else
	emit_insn (gen_sub2_insn (result, inc));
      emit_insn (gen_move_insn (incloc, result));
      /* Restore non-modified value for the result.  We prefer this
	 way because it does not require an addition hard
	 register.  */
      if (plus_p)
	{
	  if (CONST_INT_P (inc))
	    emit_insn (gen_add2_insn (result, GEN_INT (-INTVAL (inc))));
	  else
	    emit_insn (gen_sub2_insn (result, inc));
	}
      else if (CONST_INT_P (inc))
	emit_insn (gen_add2_insn (result, inc));
      else
	emit_insn (gen_add2_insn (result, inc));
    }
  return result;
}

/* Number of elements in the following array.  */
static int early_clobber_reload_regs_num;

/* Info about registers which we already reloaded because of conflict
   with early clobber.  */
static struct
{
  /* Regno of already reloaded register because of conflict with early
     clobber.  */
  int regno;
  /* New register used for the reload.  */
  rtx new_reg;
} early_clobber_reload_regs[MAX_RECOG_OPERANDS];

/* The function returns a new register of class RCLASS which should be
   used for reload input register X because of conflict with an early
   clobbered register.  If such new register are being created, emit
   the reload insns and put them to INSERT sequence.  */
static rtx
make_early_clobber_input_reload_reg (rtx x, enum reg_class rclass,
				     rtx *insert)
{
  int i, regno;
  rtx new_reg;
  
  gcc_assert (REG_P (x));
  regno = REGNO (x);
  for (i = 0; i < early_clobber_reload_regs_num; i++)
    if (early_clobber_reload_regs[i].regno == regno
	/* It is not worth to check class subsets or to use class
	   intersects because such cases are extremely rare.  */
	&& (rclass
	    == lra_get_preferred_class (REGNO (early_clobber_reload_regs[i]
					       .new_reg))))
      return early_clobber_reload_regs[i].new_reg;
  if (get_reload_reg (OP_IN, VOIDmode, x, rclass, "early clobbered", &new_reg))
    {
      push_to_sequence (*insert);
      lra_emit_move (new_reg, x);
      *insert = get_insns ();
      end_sequence ();
    }
  gcc_assert (early_clobber_reload_regs_num < MAX_RECOG_OPERANDS);
  early_clobber_reload_regs[early_clobber_reload_regs_num].regno = regno;
  early_clobber_reload_regs[early_clobber_reload_regs_num++].new_reg
    = new_reg;
  return new_reg;
}

/* Replace registers conflicting with early clobbered registers in
   *LOC which is inside the operand with number NOP.  The substitution
   register should have class RCLASS and the reload insns (if it is
   not created yet) should be put into sequence *BEFORE.  *LOC is an
   insn input if IN_P.  If the clobbered register is a hard register,
   replace it by a new pseudo whose class should be RCLASS and the
   reload insns should be put into sequence *BEFORE.  If a replacement
   is done, return TRUE.  */
static bool
search_and_replace_reg (int nop, rtx *loc, enum reg_class rclass,
			rtx *before, rtx *after, bool in_p)
{
  int i, j, clobber_nop, x_hard_regno, clobbered_hard_regno;
  bool res;
  enum machine_mode mode;
  rtx x, *clobbered_reg_loc, new_reg;
  const char *fmt;
  enum rtx_code code;
  HARD_REG_SET temp_set;

  if (*loc == NULL_RTX)
    return false;
  x = *loc;
  code = GET_CODE (x);
  mode = GET_MODE (x);
  if (code == SUBREG)
    {
      loc = &SUBREG_REG (x);
      x = SUBREG_REG (x);
      code = GET_CODE (x);
      if (GET_MODE_SIZE (GET_MODE (x)) > GET_MODE_SIZE (mode))
	mode = GET_MODE (x);
    }
  
  res = false;
  if (REG_P (x))
    {
      if (! in_p)
	return false;
      for (i = 0; i < goal_early_clobbered_nops_num; i++)
	{
	  clobber_nop = goal_early_clobbered_nops[i];
	  if (goal_alternative_matches[nop] == clobber_nop
	      || goal_alternative_matches[clobber_nop] == nop)
	    continue;
	  clobbered_reg_loc = curr_id->operand_loc[clobber_nop];
	  if (GET_CODE (*clobbered_reg_loc) == SUBREG)
	    clobbered_reg_loc = &SUBREG_REG (*clobbered_reg_loc);
	  x_hard_regno = REGNO (x);
	  if (x_hard_regno >= FIRST_PSEUDO_REGISTER)
	    x_hard_regno = reg_renumber[x_hard_regno];
	  clobbered_hard_regno = REGNO (*clobbered_reg_loc);
	  if (clobbered_hard_regno >= FIRST_PSEUDO_REGISTER)
	    clobbered_hard_regno = reg_renumber[clobbered_hard_regno];
	  CLEAR_HARD_REG_SET (temp_set);
	  if (clobbered_hard_regno >= 0)
	    {
	      for (j = (hard_regno_nregs[clobbered_hard_regno]
			[goal_early_clobbered_modes[i]]) - 1;
		   j >= 0;
		   j--)
		SET_HARD_REG_BIT (temp_set, clobbered_hard_regno + j);
	    }
	  /* Examples of conflicts: 1) early clobbered pseudo which is
	     also an address register in a memory; 2) early clobbered
	     pseudo which got the same hard register as an input
	     operand (it might be a hard register itself).  ??? Should
	     we fix it in IRA.  */
	  if (x != *clobbered_reg_loc
	      && (x_hard_regno == -1
		  || clobbered_hard_regno == -1
		  || ! lra_hard_reg_set_intersection_p (x_hard_regno, mode,
							temp_set)))
	    continue;
	  if (REGNO (*clobbered_reg_loc) >= FIRST_PSEUDO_REGISTER)
	    {
	      new_reg
		= make_early_clobber_input_reload_reg (x, rclass, before);
	      *loc = new_reg;
	    }
	  else
	    {
	      /* In case of conflict with another input, the following
		 code is not executed again because a new register has
		 no hard register yet.   */
	      gcc_assert (goal_alternative[clobber_nop] != NO_REGS);
	      new_reg = lra_create_new_reg (VOIDmode, *clobbered_reg_loc,
					    goal_alternative[clobber_nop],
					    "early clobbered");
	      push_to_sequence (*after);
	      lra_emit_move (*clobbered_reg_loc, new_reg);
	      *after = get_insns ();
	      end_sequence ();
	      *clobbered_reg_loc = new_reg;
	    }
	  bitmap_set_bit (&lra_dont_inherit_pseudos, REGNO (new_reg));
	  res = true;
	}
      return res;
    }
  if (MEM_P (x))
    {
      struct address ad;
      enum machine_mode mode = GET_MODE (x);
      rtx *addr_loc = &XEXP (x, 0);

      extract_address_regs (mode, addr_loc, MEM, &ad);
      if (ad.base_reg_loc != NULL)
	res = search_and_replace_reg (nop, ad.base_reg_loc,
				      base_reg_class (mode,
						      ad.base_outer_code,
						      ad.index_code),
				      before, after, true);
      if (ad.index_reg_loc != NULL)
	res = (search_and_replace_reg (nop, ad.index_reg_loc,
				       INDEX_REG_CLASS, before, after, true)
	       || res);
    }
  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	res = search_and_replace_reg (nop, &XEXP (x, i),
				      rclass, before, after, in_p) || res;
      else if (fmt[i] == 'E')
	{
	  for (j = XVECLEN (*loc, i) - 1; j >= 0; j--)
	    res = search_and_replace_reg (nop, &XVECEXP (*loc, i, j),
					  rclass, before, after, in_p) || res;
	}
    }
  return res;
}

/* Make reload insn and put them into sequence *BEFORE or *AFTER to
   resolve conflicts of inputs with early clobbered registers.
   Unfortunately IRA does not avoid such conflict creation, e.g. when
   early clobbered pseudo also present in a memory as an address
   register.

   ??? Should we fix such conflicts in IRA (pro: we can remove this
   code here, contra: we can not do it effectively in IRA because we
   don't know yet there what insn alternative will be used).  */
static void
create_early_clobber_reloads (rtx *before, rtx *after)
{
  int i;

  if (goal_early_clobbered_nops_num == 0)
    return;
  early_clobber_reload_regs_num = 0;
  for (i = 0; i < curr_static_id->n_operands; i++)
    /* We don't want process insides of match_operator and
       match_parallel because otherwise we would process their
       operands once again generating a wrong code.  */
    if (! curr_static_id->operand[i].is_operator
	&& search_and_replace_reg (i, curr_id->operand_loc[i],
				   goal_alternative[i], before, after,
				   curr_static_id->operand[i].type == OP_IN))
      lra_update_dups (curr_id, i, -1);
}

/* Main entry point of this file: search the body of the current insn
   to choose the best alternative.  It is mimicking insn alternative
   cost calculation model of former reload pass.  That is because
   machine descriptions were written to use this model.  This model
   can be changed in future.  Make commutative operand exchange if it
   is chosen.

   Return true if some RTL changes happened during function call.  */
static bool
curr_insn_transform (void)
{
  int i;
  int n_operands;
  int n_alternatives;
  int n_dups;
  int commutative;
  int goal_alternative_matched[MAX_RECOG_OPERANDS];
  rtx before, after;
  bool alt_p = false;
  /* Flag that the insn has been changed through a transformation.  */
  bool change_p;
  int max_regno_before;
  int reused_alternative_num;

  no_input_reloads_p = no_output_reloads_p = false;
  goal_alternative_number = 0;

  if (check_and_process_move (&change_p))
    return change_p;

  /* JUMP_INSNs and CALL_INSNs are not allowed to have any output
     reloads; neither are insns that SET cc0.  Insns that use CC0 are
     not allowed to have any input reloads.  */
  if (JUMP_P (curr_insn) || CALL_P (curr_insn))
    no_output_reloads_p = true;

#ifdef HAVE_cc0
  if (reg_referenced_p (cc0_rtx, PATTERN (curr_insn)))
    no_input_reloads_p = true;
  if (reg_set_p (cc0_rtx, PATTERN (curr_insn)))
    no_output_reloads_p = true;
#endif

  n_operands = curr_static_id->n_operands;
  n_alternatives = curr_static_id->n_alternatives;
  n_dups = curr_static_id->n_dups;

  /* Just return "no reloads" if insn has no operands with
     constraints.  */
  if (n_operands == 0 || n_alternatives == 0)
    return false;

  max_regno_before = max_reg_num ();

  for (i = 0; i < n_operands; i++)
    {
      goal_alternative_matched[i] = -1;
      goal_alternative_matches[i] = -1;
    }

  commutative = curr_static_id->commutative;

  /* Now see what we need for pseudo-regs that didn't get hard regs or
     got the wrong kind of hard reg.  For this, we must consider all
     the operands together against the register constraints.  */

  best_losers = best_overall = MAX_RECOG_OPERANDS * 2 + 600;
  best_small_class_operands_num = best_reload_sum = 0;

  curr_swapped = false;
  goal_alternative_swapped = false;

  /* Make equivalence substitution and memory subreg elimination
     before address processing because an address legitimacy can
     depend on memory mode.  */
  for (i = 0; i < n_operands; i++)
    {
      rtx op = *curr_id->operand_loc[i];
      rtx subst, old = op;
      bool op_change_p = false;

      if (GET_CODE (old) == SUBREG)
	old = SUBREG_REG (old);
      subst = get_equiv_substitution (old);
      if (subst != old)
	{
	  subst = copy_rtx (subst);
	  gcc_assert (REG_P (old));
	  if (GET_CODE (op) == SUBREG)
	    SUBREG_REG (op) = subst;
	  else
	    *curr_id->operand_loc[i] = subst;
	  if (lra_dump_file != NULL)
	    {
	      fprintf (lra_dump_file,
		       "Changing pseudo %d in operand %i of insn %u on equiv ",
		       REGNO (old), i, INSN_UID (curr_insn));
	      print_value_slim (lra_dump_file, subst, 1);
	      fprintf (lra_dump_file, "\n");
	    }
	  op_change_p = change_p = true;
	}
      if (simplify_operand_subreg (i, GET_MODE (old)) || op_change_p)
	{
	  change_p = true;
	  lra_update_dups (curr_id, i, -1);
	}
    }

  /* Reload address registers and displacements.  We do it before
     finding an alternative because of memory constraints.  */
  before = after = NULL_RTX;
  for (i = 0; i < n_operands; i++)
    if (process_address (i, &before, &after))
      {
	change_p = true;
	lra_update_dups (curr_id, i, -1);
      }
  
 try_swapped:

  reused_alternative_num = curr_id->used_insn_alternative;
  if (lra_dump_file != NULL && reused_alternative_num >= 0)
    fprintf (lra_dump_file, "Reusing alternative %d for insn #%u\n",
	     reused_alternative_num, INSN_UID (curr_insn));

  if (process_alt_operands (reused_alternative_num))
    alt_p = true;

  /* If insn is commutative (it's safe to exchange a certain pair of
     operands) then we need to try each alternative twice, the second
     time matching those two operands as if we had exchanged them.  To
     do this, really exchange them in operands.

     If we have just tried the alternatives the second time, return
     operands to normal and drop through.  */

  if (reused_alternative_num < 0 && commutative >= 0)
    {
      rtx x;

      curr_swapped = !curr_swapped;
      if (curr_swapped)
	{
	  x = *curr_id->operand_loc[commutative];
	  *curr_id->operand_loc[commutative]
	    = *curr_id->operand_loc[commutative + 1];
	  *curr_id->operand_loc[commutative + 1] = x;
	  /* Swap the duplicates too.  */
	  lra_update_dups (curr_id, commutative, commutative + 1);
	  goto try_swapped;
	}
      else
	{
	  x = *curr_id->operand_loc[commutative];
	  *curr_id->operand_loc[commutative]
	    = *curr_id->operand_loc[commutative + 1];
	  *curr_id->operand_loc[commutative + 1] = x;
	  lra_update_dups (curr_id, commutative, commutative + 1);
	}
    }

  /* The operands don't meet the constraints.  goal_alternative
     describes the alternative that we could reach by reloading the
     fewest operands.  Reload so as to fit it.  */

  if (! alt_p)
    {
      /* No alternative works with reloads??  */
      if (INSN_CODE (curr_insn) >= 0)
	fatal_insn ("unable to generate reloads for:", curr_insn);
      error_for_asm (curr_insn,
		     "inconsistent operand constraints in an %<asm%>");
      /* Avoid further trouble with this insn.  */
      PATTERN (curr_insn) = gen_rtx_USE (VOIDmode, const0_rtx);
      return false;
    }

  /* If the best alternative is with operands 1 and 2 swapped, swap
     them.  Update the operand numbers of any reloads already
     pushed.  */

  if (goal_alternative_swapped)
    {
      rtx tem;
      rtx x;
      int dup1, dup2;

      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "  Commutative operand exchange in insn %u\n",
		 INSN_UID (curr_insn));

      tem = *curr_id->operand_loc[commutative];
      *curr_id->operand_loc[commutative]
	= *curr_id->operand_loc[commutative + 1];
      *curr_id->operand_loc[commutative + 1] = tem;

      /* Swap the duplicates too.  */
      for (dup1 = dup2 = -1, i = 0; i < n_dups; i++)
	if (curr_static_id->dup_num[i] == commutative)
	  dup1 = i;
	else if  (curr_static_id->dup_num[i] == commutative + 1)
	  dup2 = i;
      
      if (dup1 >= 0 && dup2 >= 0)
	{
	  x = *curr_id->dup_loc[dup1];
	  *curr_id->dup_loc[dup1] = *curr_id->dup_loc[dup2];
	  *curr_id->dup_loc[dup2] = x;
	}

      change_p = true;
    }

  lra_set_used_insn_alternative (curr_insn,
				 goal_alternative_number);

  if (lra_dump_file != NULL)
    {
      const char *p;

      fprintf (lra_dump_file, "  Choosing alt %d in insn %u:",
	       goal_alternative_number, INSN_UID (curr_insn));
      for (i = 0; i < n_operands; i++)
	{
	  p = (curr_static_id->operand_alternative
	       [goal_alternative_number * n_operands + i].constraint);
	  if (*p == '\0')
	    continue;
	  fprintf (lra_dump_file, "  (%d) ", i);
	  for (; *p != '\0' && *p != ',' && *p != '#'; p++)
	    fputc (*p, lra_dump_file);
	}
      fprintf (lra_dump_file, "\n");
    }

  /* Right now, for any pair of operands I and J that are required to
     match, with I < J, goal_alternative_matches[J] is I.  Set up
     goal_alternative_matched as the inverse function:
     goal_alternative_matched[I] = J.  */
  
  for (i = 0; i < n_operands; i++)
    if (goal_alternative_matches[i] >= 0)
      goal_alternative_matched[goal_alternative_matches[i]] = i;
  
  for (i = 0; i < n_operands; i++)
    goal_alternative_win[i] |= goal_alternative_match_win[i];
  
  /* Any constants that aren't allowed and can't be reloaded into
     registers are here changed into memory references.  */
  for (i = 0; i < n_operands; i++)
    if (goal_alternative_win[i])
      {
	int regno;
	enum reg_class new_class;
	rtx reg = *curr_id->operand_loc[i];

	if (GET_CODE (reg) == SUBREG)
	  reg = SUBREG_REG (reg);
	    
	if (REG_P (reg) && (regno = REGNO (reg)) >= FIRST_PSEUDO_REGISTER)
	  {
	    bool ok_p = in_class_p (regno, goal_alternative[i], &new_class);

	    if (new_class != NO_REGS && get_reg_class (regno) != new_class)
	      {
		gcc_assert (ok_p);
		change_class (regno, new_class, "      Change", true);
	      }
	  }
      }
    else
      {
	const char *constraint;
	char c;
	rtx op = *curr_id->operand_loc[i];
	rtx subreg = NULL_RTX;
	rtx plus = NULL_RTX;
	enum machine_mode mode
	  = lra_get_mode (curr_static_id->operand[i].mode, op);
	
	if (GET_CODE (op) == SUBREG)
	  {
	    subreg = op;
	    op = SUBREG_REG (op);
	    mode = GET_MODE (op);
	  }
	
	if (GET_CODE (op) == PLUS)
	  {
	    plus = op;
	    op = XEXP (op, 1);
	  }
	
	if (CONST_POOL_OK_P (mode, op)
	    && ((targetm.preferred_reload_class
		 (op, (enum reg_class) goal_alternative[i]) == NO_REGS)
		|| no_input_reloads_p)
	    && mode != VOIDmode)
	  {
	    rtx tem = force_const_mem (mode, op);
	    
	    change_p = true;
	    /* If we stripped a SUBREG or a PLUS above add it back.  */
	    if (plus != NULL_RTX)
	      tem = gen_rtx_PLUS (mode, XEXP (plus, 0), tem);
	    
	    if (subreg != NULL_RTX)
	      tem = gen_rtx_SUBREG (mode, tem, SUBREG_BYTE (subreg));
	    
	    *curr_id->operand_loc[i] = tem;
	    lra_update_dups (curr_id, i, -1);
	    process_address (i, &before, &after);
	    
	    /* If the alternative accepts constant pool refs directly
	       there will be no reload needed at all.  */
	    if (plus != NULL_RTX || subreg != NULL_RTX)
	      continue;
	    /* Skip alternatives before the one requested.  */
	    constraint
	      = (curr_static_id->operand_alternative
		 [goal_alternative_number * n_operands + i].constraint);
	    for (;
		 (c = *constraint) && c != ',' && c != '#';
		 constraint += CONSTRAINT_LEN (c, constraint))
	      {
		if (c == TARGET_MEM_CONSTRAINT || c == 'o')
		  break;
#ifdef EXTRA_CONSTRAINT_STR
		if (EXTRA_MEMORY_CONSTRAINT (c, constraint)
		    && EXTRA_CONSTRAINT_STR (tem, c, constraint))
		  break;
#endif
	      }
	    if (c == '\0' || c == ',' || c == '#')
	      continue;
	    
	    goal_alternative_win[i] = true;
	  }
      }
  
  for (i = 0; i < n_operands; i++)
    {
      rtx old, new_reg;
      rtx op = *curr_id->operand_loc[i];

      if (goal_alternative_win[i])
	{
	  if (goal_alternative[i] == NO_REGS
	      && REG_P (op)
	      && lra_former_scratch_operand_p (curr_insn, i))
	    change_class (REGNO (op), NO_REGS, "      Change", true);
	  continue;
	}
      
      /* Operands that match previous ones have already been handled.  */
      if (goal_alternative_matches[i] >= 0)
	continue;

      /* We should not have an operand with a nonoffsettable address
	 appearing where an offsettable address will do.  It also may
	 be a case when the address should be special in other words
	 not a general one (e.g. it needs no index reg).  */
      if (goal_alternative_matched[i] == -1
	  && goal_alternative_offmemok[i]
	  && MEM_P (op))
	{
	  enum reg_class rclass;
	  rtx *loc = &XEXP (op, 0);
	  enum rtx_code code = GET_CODE (*loc);

	  push_to_sequence (before);
	  rclass = base_reg_class (GET_MODE (op), MEM, SCRATCH);
	  if (code == PRE_DEC || code == POST_DEC
	      || code == PRE_INC || code == POST_INC
	      || code == PRE_MODIFY || code == POST_MODIFY)
	    new_reg = emit_inc (rclass, *loc, *loc,
				/* This value does not matter for MODIFY.  */
				GET_MODE_SIZE (GET_MODE (op)));
	  else if (get_reload_reg (OP_IN, Pmode, *loc, rclass,
				   "offsetable address", &new_reg))
	    lra_emit_move (new_reg, *loc);
	  before = get_insns ();
	  end_sequence ();
	  *loc = new_reg;
	  lra_update_dups (curr_id, i, -1);
	}
      else if (goal_alternative_matched[i] == -1)
	{
	  enum machine_mode mode;
	  rtx reg, *loc;
	  int hard_regno, byte;
	  enum op_type type = curr_static_id->operand[i].type;

	  loc = curr_id->operand_loc[i];
	  mode = lra_get_mode (curr_static_id->operand[i].mode, *loc);
	  if (GET_CODE (*loc) == SUBREG)
	    {
	      reg = SUBREG_REG (*loc);
	      byte = SUBREG_BYTE (*loc);
	      if (REG_P (reg)
		  /* Strict_low_part requires reload the register not
		     the sub-register.  */
		  && (curr_static_id->operand[i].strict_low
		      || (GET_MODE_SIZE (mode)
			  <= GET_MODE_SIZE (GET_MODE (reg))
			  && (hard_regno
			      = get_try_hard_regno (REGNO (reg))) >= 0
			  && (simplify_subreg_regno
			      (hard_regno,
			       GET_MODE (reg), byte, mode) < 0)
			  && (goal_alternative[i] == NO_REGS
			      || (simplify_subreg_regno
				  (ira_class_hard_regs[goal_alternative[i]][0],
				   GET_MODE (reg), byte, mode) >= 0)))))
		{
		  loc = &SUBREG_REG (*loc);
		  mode = GET_MODE (*loc);
		}
	    }
	  old = *loc;
	  if (get_reload_reg (type, mode, old, goal_alternative[i], "", &new_reg)
	      && type != OP_OUT)
	    {
	      push_to_sequence (before);
	      lra_emit_move (new_reg, *loc);
	      before = get_insns ();
	      end_sequence ();
	    }
	  *loc = new_reg;
	  if (type != OP_IN)
	    {
	      if (find_reg_note (curr_insn, REG_UNUSED, old) == NULL_RTX)
		{
		  push_to_sequence (after);
		  lra_emit_move (old, new_reg);
		  after = get_insns ();
		  end_sequence ();
		}
	      *loc = new_reg;
	    }
	  lra_update_dups (curr_id, i, -1);
	}
      else if (curr_static_id->operand[i].type == OP_IN
	       && (curr_static_id
		   ->operand[goal_alternative_matched[i]].type == OP_OUT))
	match_reload (goal_alternative_matched[i], i,
		      goal_alternative[i], &before, &after);
      else if (curr_static_id->operand[i].type == OP_OUT
	       && (curr_static_id
		   ->operand[goal_alternative_matched[i]].type == OP_IN))
	match_reload (i, goal_alternative_matched[i],
		      goal_alternative[i], &before, &after);
      else
	{
	  gcc_assert (INSN_CODE (curr_insn) < 0);
	  error_for_asm (curr_insn,
			 "inconsistent operand constraints in an %<asm%>");
	  /* Avoid further trouble with this insn.  */
	  PATTERN (curr_insn) = gen_rtx_USE (VOIDmode, const0_rtx);
	  return false;
	}
    }
  create_early_clobber_reloads (&before, &after);
  if (before != NULL_RTX || after != NULL_RTX || max_regno_before != max_reg_num ())
    change_p = true;
  if (change_p)
    /* Something changes -- process the insn.  */
    lra_update_insn_regno_info (curr_insn);
  lra_process_new_insns (curr_insn, before, after, "Inserting insn reload");
  return change_p;
}

/* Return true i X is in LIST.  */
static bool
in_list_p (rtx x, rtx list)
{
  for (; list != NULL_RTX; list = XEXP (list, 1))
    if (XEXP (list, 0) == x)
      return true;
  return false;
}

/* Return true if X contains a (spilled if SPILLED_P) pseudo.  */
static bool
contains_pseudo_p (rtx x, bool spilled_p)
{
  int i, j;
  const char *fmt;
  enum rtx_code code;

  code = GET_CODE (x);
  if (REG_P (x))
    {
      if (REGNO (x) < FIRST_PSEUDO_REGISTER)
	return false;
      if (! spilled_p)
	return true;
      return lra_get_regno_hard_regno (REGNO (x)) < 0;
    }
  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (contains_pseudo_p (XEXP (x, i), spilled_p))
	    return true;
	}
      else if (fmt[i] == 'E')
	{
	  for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	    if (contains_pseudo_p (XVECEXP (x, i, j), spilled_p))
	      return true;
	}
    }
  return false;
}

/* Maximum number of constraint pass iteration number.  It is for
   preventing all LRA cycling.  */
#define MAX_CONSTRAINT_ITERATION_NUMBER 15

/* Maximum number of generated reload insns per an insn.  It is for
   preventing this pass cycling.  */
#define MAX_RELOAD_INSNS_NUMBER 20

/* The current iteration number of this LRA pass.  */
int lra_constraint_iter;

/* Entry function of LRA constraint pass.  Return true if the
   constraint pass did change the code.  */
bool
lra_constraints (bool first_p)
{
  bool changed_p;
  int i, hard_regno, new_insns_num;
  unsigned int min_len;
  rtx set, x;
  basic_block last_bb;

  lra_constraint_iter++;
  if (lra_dump_file != NULL)
    fprintf (lra_dump_file, "\n********** Local #%d: **********\n\n",
	     lra_constraint_iter);
  if (lra_constraint_iter > MAX_CONSTRAINT_ITERATION_NUMBER)
    internal_error
      ("Maximum number of LRA constraint passes is achieved (%d)\n",
       MAX_CONSTRAINT_ITERATION_NUMBER);
  changed_p = false;
  new_regno_start = first_p ? lra_constraint_new_regno_start : max_reg_num ();
  for (i = FIRST_PSEUDO_REGISTER; i < new_regno_start; i++)
    ira_reg_equiv[i].profitable_p = true;
  for (i = FIRST_PSEUDO_REGISTER; i < new_regno_start; i++)
    if (lra_reg_info[i].nrefs != 0)
      {
	if ((hard_regno = lra_get_regno_hard_regno (i)) >= 0)
	  {
	    int j, nregs = hard_regno_nregs[hard_regno][PSEUDO_REGNO_MODE (i)];
	    
	    for (j = 0; j < nregs; j++)
	      df_set_regs_ever_live (hard_regno + j, true);
	  }
	else if ((x = get_equiv_substitution (regno_reg_rtx[i])) != NULL_RTX)
	  {
	    if (! first_p && contains_pseudo_p (x, false))
	      /* After RTL transformation, we can not guarantee that
		 pseudo in the susbtitution was not reloaded which
		 might make equivalence invalid.  For example, in
		 reverse equiv of p0

		 p0 <- ...
		 ...
		 equiv_mem <- p0

		 the memory address register was reloaded before the
		 2nd insn.  */
	      ira_reg_equiv[i].defined_p = false;
	    if (contains_pseudo_p (x, true))
	      ira_reg_equiv[i].profitable_p = false;
	  }
      }
  lra_eliminate (false);
  min_len = VEC_length (rtx, lra_constraint_insn_stack);
  new_insns_num = 0;
  last_bb = NULL;
  changed_p = false;
  for (;VEC_length (rtx, lra_constraint_insn_stack) != 0;)
    {
      curr_insn = VEC_pop (rtx, lra_constraint_insn_stack);
      bitmap_clear_bit (&lra_constraint_insn_stack_bitmap,
			INSN_UID (curr_insn));
      curr_bb = BLOCK_FOR_INSN (curr_insn); 
      if (curr_bb != last_bb)
	{
	  last_bb = curr_bb;
	  bb_reload_num = lra_curr_reload_num;
	}
      if (min_len > VEC_length (rtx, lra_constraint_insn_stack))
	{
	  min_len = VEC_length (rtx, lra_constraint_insn_stack);
	  new_insns_num = 0;
	}
      if (new_insns_num > MAX_RELOAD_INSNS_NUMBER)
	internal_error
	  ("Max. number of generated reload insns per insn is achieved (%d)\n",
	   MAX_RELOAD_INSNS_NUMBER);
      new_insns_num++;
      if (NONDEBUG_INSN_P (curr_insn))
	{
	  if ((set = single_set (curr_insn)) != NULL_RTX
	      && ((((x = get_equiv_substitution (SET_DEST (set)))
		    != SET_DEST (set))
		   /* Remove insns which set up a pseudo whose value
		      can not be changed.  Such insns might be not in
		      init_insns because we don't update equiv data
		      during insn transformations.

		      As an example, let suppose that a pseudo got
		      hard register and on the 1st pass was not
		      changed to equivalent constant.  We generate an
		      additional insn setting up the pseudo because of
		      secondary memory movement.  Then the pseudo is
		      spilled and we use the equiv constant.  In this
		      case we should remove the additional insn and
		      this insn is not init_insns list.  */
		   && (! MEM_P (x) || MEM_READONLY_P (x)
		       || in_list_p (curr_insn,
				     ira_reg_equiv
				     [REGNO (SET_DEST (set))].init_insns)))
		  || (SET_SRC (set) != get_equiv_substitution (SET_SRC (set))
		      && in_list_p (curr_insn,
				    ira_reg_equiv
				    [REGNO (SET_SRC (set))].init_insns))))
	    {
	      /* This is equiv init insn of pseudo which did not get a
		 hard register -- remove the insn.  */
	      if (lra_dump_file != NULL)
		{
		  fprintf (lra_dump_file,
			   "      Removing equiv init insn %i (freq=%d)\n",
			   INSN_UID (curr_insn),
			   BLOCK_FOR_INSN (curr_insn)->frequency);
		  print_rtl_slim (lra_dump_file, curr_insn, curr_insn, -1, 0);
		}
	      lra_set_insn_deleted (curr_insn);
	      continue;
	    }
	  curr_id = lra_get_insn_recog_data (curr_insn);
	  curr_static_id = curr_id->insn_static_data;
	  init_curr_insn_input_reloads ();
	  if (curr_insn_transform ())
	    changed_p = true;
	}
    }
  /* If we used a new hard regno, changed_p should be true because the
     hard reg is assigned to a new pseudo.  */
#ifdef ENABLE_CHECKING
  if (! changed_p)
    {
      for (i = FIRST_PSEUDO_REGISTER; i < new_regno_start; i++)
	if (lra_reg_info[i].nrefs != 0
	    && (hard_regno = lra_get_regno_hard_regno (i)) >= 0)
	  {
	    int j, nregs = hard_regno_nregs[hard_regno][PSEUDO_REGNO_MODE (i)];
	    
	    for (j = 0; j < nregs; j++)
	      gcc_assert (df_regs_ever_live_p (hard_regno + j));
	  }
    }
#endif
  return changed_p;
}

/* Initiate the LRA constraint pass.  It is done once per
   function.  */
void
lra_contraints_init (void)
{
#ifdef SECONDARY_MEMORY_NEEDED
  int mode;

  for (mode = 0; mode < MAX_MACHINE_MODE; mode++)
    lra_secondary_memory[mode] = NULL_RTX;
#endif
  init_indirect_mem ();
  bitmap_initialize (&lra_dont_inherit_pseudos, &reg_obstack);
}

/* Finalize the LRA constraint pass.  It is done once per
   function.  */
void
lra_contraints_finish (void)
{
  bitmap_clear (&lra_dont_inherit_pseudos);
}



/* This page contains code to do inheritance transformations.  */

/* Current reload pseudo check for validity of elements in
   RELOAD_INSN.  */
static int curr_reload_insn_check;
/* If an element value is equal to the above variable value, then the
   corresponding element in RELOAD_INSN is valid.  */
static int *reload_insn_check;
/* Map: reload pseudo regno -> last insn in the current EBB which sets
   up the reload pseudo from the original pseudo and the original
   pseudo value is not changed after the last insn.  In order words,
   if we need to reload the original pseudo again we can do this from
   the reload pseudo in the last insn.  */
static rtx *reload_insn;

/* Do inheritance transformation for reload insn INSN reloading
   ORIGINAL_REGNO into RELOAD_REG where the subsequent reload insn in
   EBB (remember we traverse insns in the backward direction) for the
   original regno is LAST_RELOAD_INSN.  */
static void
inherit_reload_reg (rtx reload_reg, int original_regno,
		    rtx insn, rtx last_reload_insn)
{
  int reload_regno = REGNO (reload_reg);
  enum reg_class rclass = lra_get_preferred_class (reload_regno);
  rtx new_reg, new_insns, set, src, dst;
  basic_block bb;

  new_reg = lra_create_new_reg (GET_MODE (reload_reg), reload_reg,
				rclass, "inheritance");
  ORIGINAL_REGNO (new_reg) = original_regno;
  bitmap_set_bit (&lra_inheritance_pseudos, REGNO (new_reg));
  start_sequence ();
  emit_move_insn (new_reg, reload_reg);
  new_insns = get_insns ();
  end_sequence ();
  lra_process_new_insns (insn, NULL_RTX, new_insns,
			 "Add inheritance definition");
  if (lra_dump_file != NULL)
    print_rtl_slim (lra_dump_file, last_reload_insn, last_reload_insn, -1, 0);
  set = single_set (last_reload_insn);
  gcc_assert (set != NULL_RTX);
  dst = SET_DEST (set);
  src = SET_SRC (set);
  gcc_assert (REG_P (src) && REG_P (dst)
	      && (int) REGNO (dst) >= lra_constraint_new_regno_start);
  SET_SRC (set) = new_reg;
  lra_push_insn (last_reload_insn);
  /* Invalidate alternatives for insn should be processed.  */
  lra_set_used_insn_alternative_by_uid (INSN_UID (last_reload_insn), -1);
  if (lra_dump_file != NULL)
    {
      fprintf (lra_dump_file, "    Inheritance reuse change:\n");
      print_rtl_slim (lra_dump_file, last_reload_insn, last_reload_insn,
		      -1, 0);
      fprintf (lra_dump_file, "\n");
    }
  for (bb = BLOCK_FOR_INSN (insn);
       bb != BLOCK_FOR_INSN (last_reload_insn);
       bb = bb->next_bb)
    {
      bitmap_set_bit (DF_LR_OUT (bb), REGNO (new_reg));
      bitmap_set_bit (DF_LR_IN (bb->next_bb), REGNO (new_reg));
    }
}

/* Do inheritance transformations in EBB starting with HEAD and
   finishing on TAIL.  We process EBB insns in the reverse order.  */
static void
inherit_in_ebb (rtx head, rtx tail)
{
  int src_regno, dst_regno;
  rtx prev_insn, last_reload_insn, set;
  struct lra_insn_reg *reg;

  curr_reload_insn_check++;
  /* Remeber: we can remove the current insn.  */
  for (curr_insn = tail; curr_insn != PREV_INSN (head); curr_insn = prev_insn)
    {
      prev_insn = PREV_INSN (curr_insn);
      if (! NONDEBUG_INSN_P (curr_insn))
	continue;
      curr_id = lra_get_insn_recog_data (curr_insn);
      src_regno = dst_regno = -1;
      if ((set = single_set (curr_insn)) != NULL_RTX
	  && REG_P (SET_DEST (set)) && REG_P (SET_SRC (set)))
	{
	  src_regno = REGNO (SET_SRC (set));
	  dst_regno = REGNO (SET_DEST (set));
	}
      if (src_regno < lra_constraint_new_regno_start
	  && dst_regno >= lra_constraint_new_regno_start
	  && lra_get_preferred_class (dst_regno) != NO_REGS)
	{
	  /* 'reload_pseudo <- original_pseudo'.  */
	  if (reload_insn_check[src_regno] == curr_reload_insn_check
	      && (last_reload_insn = reload_insn[src_regno]) != NULL_RTX
	      && ! bitmap_bit_p (&lra_dont_inherit_pseudos, dst_regno))
	    inherit_reload_reg (SET_DEST (set), src_regno,
				curr_insn, last_reload_insn);
	  reload_insn_check[src_regno] = curr_reload_insn_check;
	  reload_insn[src_regno] = curr_insn;
	}
      else if (src_regno >= lra_constraint_new_regno_start
	       && dst_regno < lra_constraint_new_regno_start
	       && lra_get_preferred_class (src_regno) != NO_REGS
	       && reload_insn_check[dst_regno] == curr_reload_insn_check
	       && (last_reload_insn = reload_insn[dst_regno]) != NULL_RTX)
	{
	  /* 'original_pseudo <- reload_pseudo'.  */
	  inherit_reload_reg (SET_SRC (set), dst_regno,
			      curr_insn, last_reload_insn);
	  /* Invalidate.  */
	  reload_insn_check[dst_regno] = 0;
	}
      else
	{
	  for (reg = curr_id->regs; reg != NULL; reg = reg->next)
	    if (reg->type != OP_IN
		&& reg->regno < lra_constraint_new_regno_start)
	      /* Invalidate.  */
	      reload_insn_check[reg->regno] = 0;
	}
    }
}

/* This value affects EBB forming.  If probability of edge from EBB to
   a BB is not greater than the following value, we don't add the BB
   to EBB.  */ 
#define EBB_PROBABILITY_CUTOFF (REG_BR_PROB_BASE / 2)

/* Current number of inheritance iteration.  */
int lra_inheritance_iter;

/* Entry function for inheritance pass.  */
void
lra_inheritance (void)
{
  basic_block bb;
  rtx head, tail;
  edge e;

  lra_inheritance_iter++;
  if (lra_dump_file != NULL)
    fprintf (lra_dump_file, "\n********** Inheritance #%d: **********\n\n",
	     lra_inheritance_iter);
  curr_reload_insn_check = 0;
  reload_insn_check = (int *) xmalloc (sizeof (int)
				       * lra_constraint_new_regno_start);
  memset (reload_insn_check, 0,
	  sizeof (int) * lra_constraint_new_regno_start);
  reload_insn = (rtx *) xmalloc (sizeof (rtx) * lra_constraint_new_regno_start);
  FOR_EACH_BB (bb)
    {
      head = BB_HEAD (bb);
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "EBB");
      /* Form a EBB starting with BB.  */
      for (;;)
	{
	  if (lra_dump_file != NULL)
	    fprintf (lra_dump_file, " %d", bb->index);
	  tail = BB_END (bb);
	  if (bb->next_bb == EXIT_BLOCK_PTR || LABEL_P (BB_HEAD (bb->next_bb)))
	    break;
	  e = find_fallthru_edge (bb->succs);
	  if (! e)
	    break;
	  if (e->probability <= EBB_PROBABILITY_CUTOFF)
	    break;
	  bb = bb->next_bb;
	}
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "\n");
      inherit_in_ebb (head, tail);
    }
  free (reload_insn_check);
  free (reload_insn);
}



/* This page contains code to undo failed inheritance
   transformations.  */

/* Current number of iteration undoing inheritance.  */
int lra_undo_inheritance_iter;

/* Temporary bitmaps used during calls of FIX_BB_LIVE_INFO.  */
static bitmap_head temp_bitmap_head;

/* Fix BB live info LIVE after removing pseudos created on pass doing
   inheritance which are REMOVED_PSEUDOS.  */
static void
fix_bb_live_info (bitmap live, bitmap removed_pseudos)
{
  unsigned int regno;
  bitmap_iterator bi;

  bitmap_and (&temp_bitmap_head, removed_pseudos, live);
  EXECUTE_IF_SET_IN_BITMAP (&temp_bitmap_head, 0, regno, bi)
    {
      bitmap_clear_bit (live, regno);
      bitmap_set_bit (live, ORIGINAL_REGNO (regno_reg_rtx[regno]));
    }
}

/* Entry function for undoing inheritance transformation.  Return true
   if we did any change.  */
bool
lra_undo_inheritance (void)
{
  basic_block bb;
  int src_regno, dst_regno, original_regno;
  unsigned int inherit_regno;
  rtx set;
  bitmap_head remove_pseudos, original_remove_pseudos;
  bitmap_iterator bi;

  lra_undo_inheritance_iter++;
  if (lra_dump_file != NULL)
    fprintf (lra_dump_file,
	     "\n********** Undoing inheritance #%d: **********\n\n",
	     lra_undo_inheritance_iter);
  bitmap_initialize (&remove_pseudos, &reg_obstack);
  bitmap_initialize (&original_remove_pseudos, &reg_obstack);
  EXECUTE_IF_SET_IN_BITMAP (&lra_inheritance_pseudos, 0, inherit_regno, bi)
    if (reg_renumber[inherit_regno] < 0)
      {
	original_regno = ORIGINAL_REGNO (regno_reg_rtx[inherit_regno]);
	/* If the original pseudo got a hard register we can not remove
	   the inheritance pseudo because of probable expanding the
	   original pseudo live range.  */
	if (reg_renumber[original_regno] < 0)
	  {
	    bitmap_set_bit (&remove_pseudos, inherit_regno);
	    bitmap_set_bit (&original_remove_pseudos, original_regno);
	  }
      }
  if (bitmap_empty_p (&remove_pseudos))
    return false;
  bitmap_initialize (&temp_bitmap_head, &reg_obstack);
  FOR_EACH_BB (bb)
    {
      fix_bb_live_info (DF_LR_IN (bb), &remove_pseudos);
      fix_bb_live_info (DF_LR_OUT (bb), &remove_pseudos);
      FOR_BB_INSNS_REVERSE (bb, curr_insn)
	{
	  if (! NONDEBUG_INSN_P (curr_insn))
	    continue;
	  if ((set = single_set (curr_insn)) != NULL_RTX
	      && REG_P (SET_DEST (set)) && REG_P (SET_SRC (set)))
	    {
	      src_regno = REGNO (SET_SRC (set));
	      dst_regno = REGNO (SET_DEST (set));
	      if (bitmap_bit_p (&remove_pseudos, src_regno))
		{
		  /* reload pseudo <- inheritance pseudo.  */
		  if (lra_dump_file != NULL)
		    print_rtl_slim (lra_dump_file, curr_insn, curr_insn, -1, 0);
		  SET_SRC (set) = regno_reg_rtx[ORIGINAL_REGNO (SET_SRC (set))];
		  lra_push_insn_and_update_insn_regno_info (curr_insn);
		  if (lra_dump_file != NULL)
		    {
		      fprintf (lra_dump_file, "    Inheritance reuse change:\n");
		      print_rtl_slim (lra_dump_file, curr_insn, curr_insn,
				      -1, 0);
		      fprintf (lra_dump_file, "\n");
		    }
		}
	      else if (bitmap_bit_p (&remove_pseudos, dst_regno))
		{
		  /* inheritance pseudo <- reload_pseudo  */
		  if (lra_dump_file != NULL)
		    {
		      fprintf (lra_dump_file,
			       "    Removing inheritance definition:\n");
		      print_rtl_slim (lra_dump_file,
				      curr_insn, curr_insn, -1, 0);
		    }
		  lra_set_insn_deleted (curr_insn);
		}
	    }
	}
    }
  bitmap_clear (&remove_pseudos);
  bitmap_clear (&original_remove_pseudos);
  bitmap_clear (&temp_bitmap_head);
  return true;
}
