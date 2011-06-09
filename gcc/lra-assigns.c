/* Assign reload pseudos.
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


#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "hard-reg-set.h"
#include "rtl.h"
#include "tm_p.h"
#include "target.h"
#include "insn-config.h"
#include "recog.h"
#include "output.h"
#include "regs.h"
#include "function.h"
#include "expr.h"
#include "basic-block.h"
#include "except.h"
#include "df.h"
#include "ira.h"
#include "sparseset.h"
#include "lra-int.h"

/* Return a regno with biggest size mode of bound pseudo group given
   by REGNO.  */
static int
get_biggest_bound_mode_pseudo (int regno)
{
  int curr_regno;
  int best_regno = -1;

  gcc_assert (regno >= FIRST_PSEUDO_REGISTER);
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    if (best_regno < 0
	|| (GET_MODE_SIZE (GET_MODE (regno_reg_rtx[best_regno]))
	    < GET_MODE_SIZE (GET_MODE (regno_reg_rtx[curr_regno]))))
      best_regno = curr_regno;
  return best_regno;
}


/* Return biggest size mode of bound pseudo group given by REGNO.  */
static enum machine_mode
get_biggest_bound_mode (int regno)
{
  return GET_MODE (regno_reg_rtx[get_biggest_bound_mode_pseudo (regno)]);
}

/* Approximate order number of insn for each given reload pseudo (its
   regno is the index) was generated, 0 otherwise.  This values are
   used to improve chance of the inheritance.  */
static int *reload_insn_num;

/* The function is used to sort *reload* pseudos to try to assign them
   hard registers.  */
static int
reload_pseudo_compare_func (const void *v1p, const void *v2p)
{
  int r1 = *(const int *) v1p, r2 = *(const int *) v2p;
  enum reg_class cl1 = lra_get_preferred_class (r1);
  enum reg_class cl2 = lra_get_preferred_class (r2);
  int diff;
  
  gcc_assert (r1 >= lra_constraint_new_regno_start
	      && r2 >= lra_constraint_new_regno_start
	      && lra_reg_info[r1].first == r1 && lra_reg_info[r2].first == r2);
  
  /* Prefer to assign reload registers with smaller classes first to
     guarantee assignment to all reload registers.  */
  if ((diff = (ira_available_class_regs[cl1]
	       - ira_available_class_regs[cl2])) != 0)
    return diff;
  /* Prefer to assign more frequently used reload registers first.  */
  if ((diff = lra_bound_pseudo_freq (r2) - lra_bound_pseudo_freq (r1)) != 0)
    return diff;
  /* It is to improve chance for inheritance.  */
  if ((diff = ((int) ORIGINAL_REGNO (regno_reg_rtx[r1])
	       - (int) ORIGINAL_REGNO (regno_reg_rtx[r2]))) != 0)
    return diff;
  /* It is to improve chance for inheritance.  */
  if ((diff = reload_insn_num[r1] - reload_insn_num[r2]) != 0)
    return diff;
  
  /* If regs are equally good, sort by their numbers, so that the
     results of qsort leave nothing to chance.  */
  return r1 - r2;
}

/* The function is used to sort *non-reload* pseudos to try to assign
   them hard registers.  The order calculation is simpler than in the
   previous function and based on the pseudo frequency usage.  */
static int
pseudo_compare_func (const void *v1p, const void *v2p)
{
  int r1 = *(const int *) v1p, r2 = *(const int *) v2p;
  int diff;

  gcc_assert (lra_reg_info[r1].first == r1 && lra_reg_info[r2].first == r2);
  
  /* Prefer to assign more frequently used registers first.  */
  if ((diff = lra_bound_pseudo_freq (r2) - lra_bound_pseudo_freq (r1)) != 0)
    return diff;
  
  /* If regs are equally good, sort by their numbers, so that the
     results of qsort leave nothing to chance.  */
  return r1 - r2;
}

/* Map: program point -> bitmap of all pseudos living at the point and
   assigned to hard registers.  */
static bitmap_head *live_hard_reg_pseudos;

/* Bitmap used to calculate living hard reg pseudos for some program
   point range.  */
static bitmap_head live_range_hard_reg_pseudos;

/* Bitmap used to calculate living reload pseudos for some program
   point range.  */
static bitmap_head live_range_reload_pseudos;

/* Allocate and initialize the data about living pseudos at program
   points.  */
static void
init_lives (void)
{
  int i;

  bitmap_initialize (&live_range_hard_reg_pseudos, &reg_obstack);
  bitmap_initialize (&live_range_reload_pseudos, &reg_obstack);
  live_hard_reg_pseudos = (bitmap_head *) xmalloc (sizeof (bitmap_head)
						   * lra_live_max_point);
  for (i = 0; i < lra_live_max_point; i++)
    bitmap_initialize (&live_hard_reg_pseudos[i], &reg_obstack);
}

/* Free the data about living pseudos at program points.  */
static void
finish_lives (void)
{
  int i;

  bitmap_clear (&live_range_hard_reg_pseudos);
  bitmap_clear (&live_range_reload_pseudos);
  for (i = 0; i < lra_live_max_point; i++)
    bitmap_clear (&live_hard_reg_pseudos[i]);
  free (live_hard_reg_pseudos);
}

/* Update LIVE_HARD_REG_PSEUDOS by pseudo REGNO assigment or by the
   pseudo spilling if FREE_P.  */
static void
update_lives (int regno, bool free_p)
{
  int p, curr_regno;
  lra_live_range_t r;

  for (curr_regno = lra_reg_info[regno].first;
	curr_regno >= 0;
	curr_regno = lra_reg_info[curr_regno].next)
    {
      if (reg_renumber[curr_regno] < 0)
	return;
      for (r = lra_reg_info[curr_regno].live_ranges;
	   r != NULL;
	   r = r->next)
	{
	  for (p = r->start; p <= r->finish; p++)
	    if (free_p)
	      bitmap_clear_bit (&live_hard_reg_pseudos[p], curr_regno);
	    else
	      bitmap_set_bit (&live_hard_reg_pseudos[p], curr_regno);
	}
    }
}

/* Bitmap used to calculate reload pseudos conflicting with a given
   pseudo when we are trying to find a hard register for the given
   pseudo.  */
static bitmap_head conflict_reload_pseudos;

/* Map: program point -> bitmap of all reload pseudos living at the
   point.  */
static bitmap_head *live_reload_pseudos;

/* Allocate and initialize data about living reload pseudos at any
   given program point.  */
static void
init_live_reload_pseudos (void)
{
  int i, p;
  lra_live_range_t r;
  
  bitmap_initialize (&conflict_reload_pseudos, &reg_obstack);
  live_reload_pseudos
    = (bitmap_head *) xmalloc (sizeof (bitmap_head) * lra_live_max_point);
  for (p = 0; p < lra_live_max_point; p++)
    bitmap_initialize (&live_reload_pseudos[p], &reg_obstack);
  for (i = lra_constraint_new_regno_start; i < max_reg_num (); i++)
    for (r = lra_reg_info[i].live_ranges; r != NULL; r = r->next)
      for (p = r->start; p <= r->finish; p++)
	bitmap_set_bit (&live_reload_pseudos[p], i);
}

/* Finalize data about living reload pseudos at any given program
   point.  */
static void
finish_live_reload_pseudos (void)
{
  int p;

  bitmap_clear (&conflict_reload_pseudos);
  for (p = 0; p < lra_live_max_point; p++)
    bitmap_clear (&live_reload_pseudos[p]);
  free (live_reload_pseudos);
}

/* The value used to check that cost of given hard reg is defined
   currently.  */
static int curr_hard_regno_costs_check = 0;
/* Array used to check that cost of the corresponding hard reg (the
   array element index) is defined currently.  */
static int hard_regno_costs_check[FIRST_PSEUDO_REGISTER];
/* The current costs of allocation of hard regs.  Defined only if the
   value of the corresponding element of the previous array is equal to
   CURR_HARD_REGNO_COSTS_CHECK.  */
static int hard_regno_costs[FIRST_PSEUDO_REGISTER];

/* Return a profit to use hard register for pseudo REGNO (and pseudos
   bound to it) instead of memory.  */
static int
get_allocation_profit (int regno)
{
  int profit, curr_regno;

  profit = 0;
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    profit += lra_reg_info[curr_regno].freq;
  return profit;
}

/* Find and return best free hard register for pseudo REGNO (and
   pseudos bound to it).  In failure case, return a negative number.
   Return through *COST the cost of usage of the hard register for the
   pseudo.  Best free hard register has smallest cost of usage for
   REGNO or smallest register bank if the cost is the same.  */
static int
find_hard_regno_for (int regno, int *cost)
{
  HARD_REG_SET conflict_set;
  int best_cost = INT_MAX, best_bank = INT_MAX, best_usage = INT_MAX;
  lra_live_range_t r;
  int p, i, j, rclass_size, best_hard_regno, bank;
  int curr_regno, hard_regno;
  unsigned int conflict_regno, original_regno;
  enum reg_class rclass;
  bitmap_iterator bi;
  bool all_p;

  COPY_HARD_REG_SET (conflict_set, lra_no_alloc_regs);
  rclass = lra_get_preferred_class (regno);
  curr_hard_regno_costs_check++;
  bitmap_clear (&conflict_reload_pseudos);
  bitmap_clear (&live_range_hard_reg_pseudos);
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    {
      IOR_HARD_REG_SET (conflict_set,
			lra_reg_info[curr_regno].conflict_hard_regs);
      for (r = lra_reg_info[curr_regno].live_ranges;
	   r != NULL;
	   r = r->next)
	{
	  for (p = r->start; p <= r->finish; p++)
	    {
	      bitmap_ior_into (&live_range_hard_reg_pseudos,
			       &live_hard_reg_pseudos[p]);
	      bitmap_ior_into (&conflict_reload_pseudos, &live_reload_pseudos[p]);
	    }
	}
      if ((hard_regno = lra_reg_info[curr_regno].preferred_hard_regno1) >= 0)
	{
	  if (hard_regno_costs_check[hard_regno] != curr_hard_regno_costs_check)
	    hard_regno_costs[hard_regno] = 0;
	  hard_regno_costs_check[hard_regno] = curr_hard_regno_costs_check;
	  hard_regno_costs[hard_regno]
	    -= lra_reg_info[curr_regno].preferred_hard_regno_profit1;
	}
      if ((hard_regno = lra_reg_info[curr_regno].preferred_hard_regno2) >= 0)
	{
	  if (hard_regno_costs_check[hard_regno] != curr_hard_regno_costs_check)
	    hard_regno_costs[hard_regno] = 0;
	  hard_regno_costs_check[hard_regno] = curr_hard_regno_costs_check;
	  hard_regno_costs[hard_regno]
	    -= lra_reg_info[curr_regno].preferred_hard_regno_profit2;
	}
#ifdef STACK_REGS
      if (lra_reg_info[curr_regno].no_stack_p)
	for (i = FIRST_STACK_REG; i <= LAST_STACK_REG; i++)
	  SET_HARD_REG_BIT (conflict_set, i);
#endif
      gcc_assert (rclass == lra_get_preferred_class (curr_regno));
    }
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    bitmap_clear_bit (&conflict_reload_pseudos, curr_regno);
  original_regno = ORIGINAL_REGNO (regno_reg_rtx[regno]);
  all_p = bitmap_bit_p (&lra_dont_inherit_pseudos, regno);
  EXECUTE_IF_SET_IN_BITMAP (&live_range_hard_reg_pseudos, 0,
			    conflict_regno, bi)
    if (original_regno != conflict_regno
	|| all_p || bitmap_bit_p (&lra_dont_inherit_pseudos, conflict_regno))
      lra_add_hard_reg_set (reg_renumber[conflict_regno],
			    lra_reg_info[conflict_regno].biggest_mode,
			    &conflict_set);
  if (hard_reg_set_subset_p (reg_class_contents[rclass],
			     conflict_set))
    return -1;
  EXECUTE_IF_SET_IN_BITMAP (&conflict_reload_pseudos, 0, conflict_regno, bi)
    for (curr_regno = lra_reg_info[conflict_regno].first;
	 curr_regno >= 0;
	 curr_regno = lra_reg_info[curr_regno].next)
      {
	if (reg_renumber[curr_regno] >= 0)
	  continue;
	if ((hard_regno = lra_reg_info[curr_regno].preferred_hard_regno1) >= 0)
	  {
	    if (hard_regno_costs_check[hard_regno]
		!= curr_hard_regno_costs_check)
	      hard_regno_costs[hard_regno] = 0;
	    hard_regno_costs_check[hard_regno] = curr_hard_regno_costs_check;
	    hard_regno_costs[hard_regno]
	      += lra_reg_info[curr_regno].preferred_hard_regno_profit1;
	  }
	if ((hard_regno = lra_reg_info[curr_regno].preferred_hard_regno2) >= 0)
	  {
	    if (hard_regno_costs_check[hard_regno]
		!= curr_hard_regno_costs_check)
	      hard_regno_costs[hard_regno] = 0;
	    hard_regno_costs_check[hard_regno] = curr_hard_regno_costs_check;
	    hard_regno_costs[hard_regno]
	      += lra_reg_info[curr_regno].preferred_hard_regno_profit2;
	  }
      }
  /* That is important for allocation of multi-word pseudos.  */
  IOR_COMPL_HARD_REG_SET (conflict_set, reg_class_contents[rclass]);
  /* ?!? may be cover class for the old.  */
  gcc_assert (rclass != NO_REGS);
  rclass_size = ira_class_hard_regs_num[rclass];
  best_hard_regno = -1;
  for (i = 0; i < rclass_size; i++)
    {
      hard_regno = ira_class_hard_regs[rclass][i];
      for (curr_regno = lra_reg_info[regno].first;
	   curr_regno >= 0;
	   curr_regno = lra_reg_info[curr_regno].next)
	{
	  if (lra_hard_reg_set_intersection_p (hard_regno,
					       PSEUDO_REGNO_MODE (curr_regno),
					       conflict_set)
	      /* We can not use prohibited_class_mode_regs because it is
		 defined not for all classes.  */
	      || ! HARD_REGNO_MODE_OK (hard_regno,
				       PSEUDO_REGNO_MODE (curr_regno)))
	    break;
	}
      if (curr_regno < 0)
	{
	  if (hard_regno_costs_check[hard_regno] != curr_hard_regno_costs_check)
	    {
	      hard_regno_costs_check[hard_regno] = curr_hard_regno_costs_check;
	      hard_regno_costs[hard_regno] = 0;
	    }
	  for (j = 0;
	       j < hard_regno_nregs[hard_regno][get_biggest_bound_mode (regno)];
	       j++)
	    if (! TEST_HARD_REG_BIT (call_used_reg_set, hard_regno + j)
		&& ! df_regs_ever_live_p (hard_regno + j))
	      /* It needs save restore.  */
	      hard_regno_costs[hard_regno]
		+= 2 * ENTRY_BLOCK_PTR->next_bb->frequency;
	  bank = targetm.register_bank (hard_regno);
	  if (best_hard_regno < 0 || hard_regno_costs[hard_regno] < best_cost
	      || (hard_regno_costs[hard_regno] == best_cost
		  && (bank < best_bank
		      || (bank == best_bank
			  && best_usage > lra_hard_reg_usage[hard_regno]))))
	    {
	      best_hard_regno = hard_regno;
	      best_cost = hard_regno_costs[hard_regno];
	      best_bank = bank;
	      best_usage = lra_hard_reg_usage[hard_regno];
	    }
	}
    }
  if (best_hard_regno >= 0)
    *cost = best_cost - get_allocation_profit (regno);
  return best_hard_regno;
}

/* Update REG_RENUMBER and other pseudo preferences by assignment of
   HARD_REGNO to pseudo REGNO (and pseudos bound to it) and print
   about it if PRINT_P.  */
void
lra_setup_reg_renumber (int regno, int hard_regno, bool print_p)
{
  int i, hr, curr_regno, biggest_regno, another_regno;
  int offset, curr_offset;
  lra_copy_t cp, next_cp;

  if (hard_regno < 0 || lra_reg_info[regno].next < 0)
    {
      hr = reg_renumber[regno];
      biggest_regno = regno;
      offset = 0;
    }
  else
    {
      hr  = -1;
      biggest_regno = get_biggest_bound_mode_pseudo (regno);
      offset = lra_constraint_offset (hard_regno,
				      GET_MODE (regno_reg_rtx[biggest_regno]));
    }
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    {
      if (curr_regno == biggest_regno)
	reg_renumber[curr_regno] = hard_regno;
      else
	{
	  curr_offset
	    = lra_constraint_offset (hard_regno, PSEUDO_REGNO_MODE (curr_regno));
	  if (hard_regno < 0)
	    reg_renumber[curr_regno] = -1;
	  else
	    reg_renumber[curr_regno] = hard_regno + offset - curr_offset;
	}
      if (hr < 0)
	hr = reg_renumber[curr_regno];
      gcc_assert (hr >= 0);
      for (i = 0;
	   i < hard_regno_nregs[hr][PSEUDO_REGNO_MODE (curr_regno)];
	   i++)
	if (hard_regno < 0)
	  lra_hard_reg_usage[hr + i] -= lra_reg_info[curr_regno].freq;
	else
	  lra_hard_reg_usage[hr + i] += lra_reg_info[curr_regno].freq;
      if (print_p && lra_dump_file != NULL)
	fprintf (lra_dump_file, "      Assign %d to %sr%d (freq=%d)\n",
		 reg_renumber[curr_regno],
		 curr_regno < lra_constraint_new_regno_start
		 ? "" : bitmap_bit_p (&lra_inheritance_pseudos, curr_regno)
		 ? "inheritance " : "reload ",
		 curr_regno, lra_reg_info[curr_regno].freq);
      if (hard_regno >= 0)
	for (cp = lra_reg_info[curr_regno].copies; cp != NULL; cp = next_cp)
	  {
	    if (cp->regno1 == curr_regno)
	      {
		next_cp = cp->regno1_next;
		another_regno = cp->regno2;
	      }
	    else if (cp->regno2 == curr_regno)
	      {
		next_cp = cp->regno2_next;
		another_regno = cp->regno1;
	      }
	    else
	      gcc_unreachable ();
	    if (reg_renumber[another_regno] < 0)
	      lra_setup_reload_pseudo_preferenced_hard_reg
		(another_regno, hard_regno, cp->freq);
	  }
    }
}

/* Pseudos which should be ignored for spilling for a particular
   pseudo. */
static bitmap_head ignore_pseudos_bitmap;

/* Bitmaps used to contain spill pseudos for given pseudo hard regno
   and best spill pseudos for given pseudo (and best hard regno).  */
static bitmap_head spill_pseudos_bitmap, best_spill_pseudos_bitmap;

/* Bitmap used to contain all posible candidates which might get a
   hard register after spilling for given pseudo hard regno.  */
static bitmap_head assign_candidates_bitmap;
/* Array used to contain and sort the possible candidates (see
   above).  */
static int *assign_candidates;

/* Array used to contain assigned pseudos during a try of spilling
   pseudos.  */
static int *assigned_pseudos;

/* Current pseudo check for validity of elements in
   TRY_HARD_REG_PSEUDOS.  */
static int curr_pseudo_check;
/* Array used for validity of elements in TRY_HARD_REG_PSEUDOS.  */
static int try_hard_reg_pseudos_check[FIRST_PSEUDO_REGISTER];
/* Pseudos who hold given hard register at corresponding points.  */
static bitmap_head try_hard_reg_pseudos[FIRST_PSEUDO_REGISTER];

/* Set up try_hard_reg_pseudos for given program point P and class
   RCLASS.  Those are pseudos living at P and assigned to a hard
   register of RCLASS.  In other words, those are pseudos which can be
   spilled to assign a hard register of RCLASS to a pseudo living at
   P.  */
static void
setup_try_hard_regno_pseudos (int p, enum reg_class rclass)
{
  int i, hard_regno;
  int spill_first_regno;
  enum machine_mode mode;
  unsigned int spill_regno;
  bitmap_iterator bi;

  /* Find what pseudos could be spilled.  */
  EXECUTE_IF_SET_IN_BITMAP (&live_hard_reg_pseudos[p], 0, spill_regno, bi)
    {
      spill_first_regno = lra_reg_info[spill_regno].first;
      mode = get_biggest_bound_mode (spill_first_regno);
      if (lra_hard_reg_set_intersection_p (reg_renumber[spill_first_regno],
					   mode,
					   reg_class_contents[rclass]))
	{
	  hard_regno = reg_renumber[spill_first_regno];
	  for (i = hard_regno_nregs[hard_regno][mode] - 1; i >= 0; i--)
	    {
	      if (try_hard_reg_pseudos_check[hard_regno + i]
		  != curr_pseudo_check)
		{
		  try_hard_reg_pseudos_check[hard_regno + i]
		    = curr_pseudo_check;
		  bitmap_clear (&try_hard_reg_pseudos[hard_regno + i]);
		}
	      bitmap_set_bit (&try_hard_reg_pseudos[hard_regno + i],
			      spill_first_regno);
	    }
	}
    }
}

/* Assign temporarily HARD_REGNO to pseudo REGNO (and pseudos bound to
   it).  Temporary assignment means that we might undo the data
   change.  */
static void
assign_temporarily (int regno, int hard_regno)
{
  int p, curr_regno;
  lra_live_range_t r;

  for (curr_regno = lra_reg_info[regno].first;
	curr_regno >= 0;
	curr_regno = lra_reg_info[curr_regno].next)
    {
      for (r = lra_reg_info[curr_regno].live_ranges;
	   r != NULL;
	   r = r->next)
	{
	  for (p = r->start; p <= r->finish; p++)
	    if (hard_regno < 0)
	      bitmap_clear_bit (&live_hard_reg_pseudos[p], curr_regno);
	    else
	      bitmap_set_bit (&live_hard_reg_pseudos[p], curr_regno);
	}
      /* It is not accurately for bound pseudos in few cases but it is
	 used only for cost evaluation.  */
      reg_renumber[curr_regno] = hard_regno;
    }
}

/* Array used for sorting reload pseudos for subsequent allocation
   after some spilling a pseudo.  */
static int *sorted_reload_pseudos;

/* Spill for a reload pseudo REGNO and return hard register which
   should be used for pseudo after spilling.  The function adds
   spilled pseudos to SPILLED_PSEUDO_BITMAP.  When we choose hard
   register (and pseudos occupying the hard registers and to be
   spilled), we take into account not only how REGNO will from the
   spills but also how other reload pseudos not assigned to hard
   registers yet benefit from the spills too.  */
static int
spill_for (int regno, bitmap spilled_pseudo_bitmap)
{
  int i, j, n, p, hard_regno, best_hard_regno, cost, best_cost, rclass_size;
  int curr_regno, reload_hard_regno, reload_cost;
  enum machine_mode mode, mode2;
  enum reg_class rclass;
  HARD_REG_SET spilled_hard_regs;
  unsigned int spill_regno, reload_regno, uid;
  int insn_pseudos_num, best_insn_pseudos_num;
  lra_live_range_t r;
  bitmap_iterator bi;

  gcc_assert (lra_reg_info[regno].first == regno);
  rclass = lra_get_preferred_class (regno);
  gcc_assert (reg_renumber[regno] < 0 && rclass != NO_REGS);
  bitmap_clear (&ignore_pseudos_bitmap);
  bitmap_clear (&best_spill_pseudos_bitmap);
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    {
      EXECUTE_IF_SET_IN_BITMAP (&lra_reg_info[curr_regno].insn_bitmap,
				0, uid, bi)
	  {
	    struct lra_insn_reg *ir;
	    
	    for (ir = lra_get_insn_regs (uid); ir != NULL; ir = ir->next)
	      if (ir->regno >= FIRST_PSEUDO_REGISTER)
		bitmap_set_bit (&ignore_pseudos_bitmap, ir->regno);
	  }
    }
  best_hard_regno = -1;
  best_cost = INT_MAX;
  best_insn_pseudos_num = INT_MAX;
  rclass_size = ira_class_hard_regs_num[rclass];
  mode = get_biggest_bound_mode (regno);
  curr_pseudo_check++; /* Invalidate try_hard_reg_pseudos elements.  */
  for (curr_regno = lra_reg_info[regno].first;
       curr_regno >= 0;
       curr_regno = lra_reg_info[curr_regno].next)
    {
      for (r = lra_reg_info[curr_regno].live_ranges; r != NULL; r = r->next)
	for (p = r->start; p <= r->finish; p++)
	  setup_try_hard_regno_pseudos (p, rclass);
    }
  for (i = 0; i < rclass_size; i++)
    {
      hard_regno = ira_class_hard_regs[rclass][i];
      bitmap_clear (&spill_pseudos_bitmap);
      for (j = hard_regno_nregs[hard_regno][mode] - 1; j >= 0; j--)
	{
	  if (try_hard_reg_pseudos_check[hard_regno + j] != curr_pseudo_check)
	    continue;
	  gcc_assert (! bitmap_empty_p (&try_hard_reg_pseudos[hard_regno + j]));
	  bitmap_ior_into (&spill_pseudos_bitmap,
			   &try_hard_reg_pseudos[hard_regno + j]);
	}
      /* Spill pseudos.  */
      CLEAR_HARD_REG_SET (spilled_hard_regs);
      EXECUTE_IF_SET_IN_BITMAP (&spill_pseudos_bitmap, 0, spill_regno, bi)
	for (curr_regno = lra_reg_info[spill_regno].first;
	     curr_regno >= 0;
	     curr_regno = lra_reg_info[curr_regno].next)
	  if (curr_regno >= lra_constraint_new_regno_start
	      && ! bitmap_bit_p (&lra_inheritance_pseudos, curr_regno))
	    goto fail;
      insn_pseudos_num = 0;
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "        Trying %d:", hard_regno);
      bitmap_clear (&live_range_reload_pseudos);
      EXECUTE_IF_SET_IN_BITMAP (&spill_pseudos_bitmap, 0, spill_regno, bi)
	{
	  if (bitmap_bit_p (&ignore_pseudos_bitmap, spill_regno))
	    insn_pseudos_num++;
	  gcc_assert (lra_reg_info[spill_regno].first == (int) spill_regno);
	  mode2 = get_biggest_bound_mode (spill_regno);
	  update_lives (spill_regno, true);
	  if (lra_dump_file != NULL)
	    fprintf (lra_dump_file, " spill %d(freq=%d)",
		     spill_regno, lra_reg_info[spill_regno].freq);
	  lra_add_hard_reg_set (reg_renumber[spill_regno], mode2,
				&spilled_hard_regs);
	  for (r = lra_reg_info[spill_regno].live_ranges; r != NULL; r = r->next)
	    for (p = r->start; p <= r->finish; p++)
	      bitmap_ior_into (&live_range_reload_pseudos, &live_reload_pseudos[p]);
	}
      /* We are trying to spill reload pseudo.  That is wrong we
	 should assign all reload pseudos, otherwise we cannot reuse
	 selected alternativies.  */
      hard_regno = find_hard_regno_for (regno, &cost);
      if (hard_regno >= 0)
	{
	  assign_temporarily (regno, hard_regno);
	  n = 0;
	  EXECUTE_IF_SET_IN_BITMAP (&live_range_reload_pseudos, 0, reload_regno, bi)
	    if (reg_renumber[reload_regno] < 0
		&& lra_reg_info[reload_regno].first == (int) reload_regno
		&& (hard_reg_set_intersect_p
		    (reg_class_contents[lra_get_preferred_class (reload_regno)],
		     spilled_hard_regs)))
	      sorted_reload_pseudos[n++] = reload_regno;
	  qsort (sorted_reload_pseudos, n, sizeof (int), pseudo_compare_func);
	  for (j = 0; j < n; j++)
	    {
	      reload_regno = sorted_reload_pseudos[j];
	      if (reg_renumber[reload_regno] < 0
		  && (reload_hard_regno
		      = find_hard_regno_for (reload_regno, &reload_cost)) >= 0
		  && (lra_hard_reg_set_intersection_p
		      (reload_hard_regno,
		       get_biggest_bound_mode (reload_regno),
		       spilled_hard_regs)))
		{
		  if (lra_dump_file != NULL)
		    fprintf (lra_dump_file, " assign %d(cost=%d)",
			     reload_regno, reload_cost);
		  assign_temporarily (reload_regno, reload_hard_regno);
		  cost += reload_cost;
		}
	    }
	  EXECUTE_IF_SET_IN_BITMAP (&spill_pseudos_bitmap, 0, spill_regno, bi)
	    {
	      rtx x;
	      
	      cost += get_allocation_profit (spill_regno);
	      if (ira_reg_equiv[spill_regno].memory != NULL
		  || ira_reg_equiv[spill_regno].constant != NULL)
		for (x = ira_reg_equiv[spill_regno].init_insns;
		     x != NULL;
		     x = XEXP (x, 1))
		  cost -= REG_FREQ_FROM_BB (BLOCK_FOR_INSN (XEXP (x, 0)));
	    }
	  if (best_insn_pseudos_num > insn_pseudos_num
	      || (best_insn_pseudos_num == insn_pseudos_num && best_cost > cost))
	    {
	      best_insn_pseudos_num = insn_pseudos_num;
	      best_cost = cost;
	      best_hard_regno = hard_regno;
	      bitmap_copy (&best_spill_pseudos_bitmap, &spill_pseudos_bitmap);
	      if (lra_dump_file != NULL)
		fprintf (lra_dump_file, "        Now best %d(cost=%d)\n",
			 hard_regno, cost);
	    }
	  assign_temporarily (regno, -1);
	  for (j = 0; j < n; j++)
	    {
	      reload_regno = sorted_reload_pseudos[j];
	      if (reg_renumber[reload_regno] >= 0)
		assign_temporarily (reload_regno, -1);
	    }
	}
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "\n");
      /* Restore the live hard reg pseudo info for spilled pseudos.  */
      EXECUTE_IF_SET_IN_BITMAP (&spill_pseudos_bitmap, 0, spill_regno, bi)
	update_lives (spill_regno, false);
    fail:
      ;
    }
  /* Spill: */
  EXECUTE_IF_SET_IN_BITMAP (&best_spill_pseudos_bitmap, 0, spill_regno, bi)
    {
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "      Spill %sr%d(hr=%d, freq=%d) for r%d\n",
		 ((int) spill_regno < lra_constraint_new_regno_start
		  ? ""
		  : bitmap_bit_p (&lra_inheritance_pseudos, spill_regno)
		  ? "inheritance " : "reload "),
		 spill_regno, reg_renumber[spill_regno],
		 lra_reg_info[spill_regno].freq, regno);
      update_lives (spill_regno, true);
      lra_setup_reg_renumber (spill_regno, -1, false);
    }
  bitmap_ior_into (spilled_pseudo_bitmap, &best_spill_pseudos_bitmap);
  return best_hard_regno;
}

/* Assign HARD_REGNO to REGNO.  */
static void
assign_hard_regno (int hard_regno, int regno)
{
  int i;

  gcc_assert (hard_regno >= 0);
  lra_setup_reg_renumber (regno, hard_regno, true);
  update_lives (regno, false);
  for (i = 0;
       i < hard_regno_nregs[hard_regno][get_biggest_bound_mode (regno)];
       i++)
    df_set_regs_ever_live (hard_regno + i, true);
}

/* Array used for sorting different pseudos.  */
static int *sorted_pseudos;

/* Constraint transformation can use equivalences and they can
   contains pseudos assigned to hard registers.  Such equivalence
   usage might create new conflicts of pseudos with hard registers
   (like ones used for parameter passing or call clobbered ones) or
   other pseudos assigned to the same hard registers.  Process pseudos
   assigned to hard registers (most frequently used first), spill if a
   conflict is found, and mark the spilled pseudos in
   SPILLED_PSEUDO_BITMAP.  Set up LIVE_HARD_REG_PSEUDOS from pseudos,
   assigned to hard registers. */
static void
setup_live_pseudos_and_spill_after_equiv_moves (bitmap spilled_pseudo_bitmap)
{
  int p, i, j, n, regno, curr_regno, hard_regno;
  unsigned int conflict_regno, original_regno;
  HARD_REG_SET conflict_set;
  enum machine_mode mode;
  lra_live_range_t r;
  bitmap_iterator bi;

  for (n = 0, i = FIRST_PSEUDO_REGISTER; i < max_reg_num (); i++)
    if (reg_renumber[i] >= 0
	&& lra_reg_info[i].nrefs > 0 && lra_reg_info[i].first == i)
      sorted_pseudos[n++] = i;
  qsort (sorted_pseudos, n, sizeof (int), pseudo_compare_func);
  for (i = 0; i < n; i++)
    {
      regno = sorted_pseudos[i];
      hard_regno = reg_renumber[regno];
      gcc_assert (hard_regno >= 0);
      mode = lra_reg_info[regno].biggest_mode;
      bitmap_clear (&live_range_hard_reg_pseudos);
      for (curr_regno = lra_reg_info[regno].first;
	   curr_regno >= 0;
	   curr_regno = lra_reg_info[curr_regno].next)
	{
	  IOR_HARD_REG_SET (conflict_set,
			    lra_reg_info[curr_regno].conflict_hard_regs);
	  if (GET_MODE_SIZE (mode)
	      < GET_MODE_SIZE (lra_reg_info[curr_regno].biggest_mode))
	    mode = lra_reg_info[curr_regno].biggest_mode;
	  for (r = lra_reg_info[curr_regno].live_ranges; r != NULL; r = r->next)
	    for (p = r->start; p <= r->finish; p++)
	      bitmap_ior_into (&live_range_hard_reg_pseudos,
			       &live_hard_reg_pseudos[p]);
	}
      COPY_HARD_REG_SET (conflict_set, lra_no_alloc_regs);
      original_regno = ORIGINAL_REGNO (regno_reg_rtx[regno]);
      EXECUTE_IF_SET_IN_BITMAP (&live_range_hard_reg_pseudos, 0,
				conflict_regno, bi)
	if (original_regno != conflict_regno)
	  lra_add_hard_reg_set (reg_renumber[conflict_regno],
				lra_reg_info[conflict_regno].biggest_mode,
				&conflict_set);
      if (! lra_hard_reg_set_intersection_p (hard_regno, mode, conflict_set))
	{
	  for (curr_regno = lra_reg_info[regno].first;
	       curr_regno >= 0;
	       curr_regno = lra_reg_info[curr_regno].next)
	    update_lives (curr_regno, false);
	  continue;
	}
      for (curr_regno = lra_reg_info[regno].first;
	   curr_regno >= 0;
	   curr_regno = lra_reg_info[curr_regno].next)
	{
	  bitmap_set_bit (spilled_pseudo_bitmap, curr_regno);
	  hard_regno = reg_renumber[curr_regno];
	  for (j = 0;
	       j < hard_regno_nregs[hard_regno][PSEUDO_REGNO_MODE (curr_regno)];
	       j++)
	    lra_hard_reg_usage[hard_regno + j] -= lra_reg_info[curr_regno].freq;
	  reg_renumber[curr_regno] = -1;
	  if (lra_dump_file != NULL)
	    fprintf (lra_dump_file,
		     "    Spill r%d after reg equiv. moves\n",
		     curr_regno);
	}
    }
}

/* Bitmap finaly containing all pseudos spilled on this assignment
   pass.  */
static bitmap_head all_spilled_pseudos;
/* All pseudos whose allocation was changed.  */
static bitmap_head changed_pseudo_bitmap;

/* Assign hard registers to reload pseudos and other pseudos.  */
static void
assign_by_spills (void)
{
  int i, n, nfails, iter, regno, hard_regno, cost;
  rtx insn, set;
  basic_block bb;
  bitmap_head changed_insns;

  reload_insn_num = (int *) xmalloc (sizeof (int) * max_reg_num ());
  memset (reload_insn_num, 0, sizeof (int) * max_reg_num ());
  n = 0;
  FOR_EACH_BB (bb)
    FOR_BB_INSNS (bb, insn)
      if (NONDEBUG_INSN_P (insn) && (set = single_set (insn)) != NULL_RTX
	  && REG_P (SET_DEST (set))
	  && (regno
	      = REGNO (SET_DEST (set))) >= lra_constraint_new_regno_start)
	reload_insn_num[regno] = ++n;
  for (n = 0, i = lra_constraint_new_regno_start; i < max_reg_num (); i++)
    if (reg_renumber[i] < 0
	&& lra_reg_info[i].nrefs != 0 && lra_reg_info[i].first == i
	&& lra_get_preferred_class (i) != NO_REGS)
      sorted_pseudos[n++] = i;
  bitmap_initialize (&ignore_pseudos_bitmap, &reg_obstack);
  bitmap_initialize (&spill_pseudos_bitmap, &reg_obstack);
  bitmap_initialize (&best_spill_pseudos_bitmap, &reg_obstack);
  bitmap_initialize (&assign_candidates_bitmap, &reg_obstack);
  assign_candidates = (int *) xmalloc (sizeof (int) * max_reg_num ());
  assigned_pseudos = (int *) xmalloc (sizeof (int) * max_reg_num ());
  memset (try_hard_reg_pseudos_check, 0, sizeof (try_hard_reg_pseudos_check));
  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    bitmap_initialize (&try_hard_reg_pseudos[i], &reg_obstack);
  curr_pseudo_check = 0;
  bitmap_initialize (&changed_insns, &reg_obstack);
  for (iter = 0; iter <= 1; iter++)
    {
      qsort (sorted_pseudos, n, sizeof (int), reload_pseudo_compare_func);
      nfails = 0;
      for (i = 0; i < n; i++)
	{
	  regno = sorted_pseudos[i];
	  hard_regno = find_hard_regno_for (regno, &cost);
	  if (hard_regno < 0 && ! bitmap_bit_p (&lra_inheritance_pseudos, regno))
	    hard_regno = spill_for (regno, &all_spilled_pseudos);
	  if (hard_regno < 0)
	    {
	      if (! bitmap_bit_p (&lra_inheritance_pseudos, regno))
		sorted_pseudos[nfails++] = regno;
	    }
	  else
	    {
	      /* Remember that reload pseudos can be spilled on the
		 1st pass.  */
	      bitmap_clear_bit (&all_spilled_pseudos, regno);
	      assign_hard_regno (hard_regno, regno);
	    }
	}
      if (nfails == 0)
	break;
      gcc_assert (iter == 0);
      /* This is a very rare event.  We can not assign a hard
	 register to reload pseudo because the hard register was
	 assigned to another reload pseudo on a previous
	 assignment pass.  For x86 example, on the 1st pass we
	 assigned CX (although another hard register could be used
	 for this) to reload pseudo in an insn, on the 2nd pass we
	 need CX (and only this) hard register for a new reload
	 pseudo in the same insn.  */
      if (lra_dump_file != NULL)
	fprintf (lra_dump_file, "  2nd iter for reload pseudo assignments:\n");
      for (i = 0; i < nfails; i++)
	{
	  if (lra_dump_file != NULL)
	    fprintf (lra_dump_file, "    Reload r%d assignment failure\n",
		     sorted_pseudos[i]);
	  bitmap_ior_into (&changed_insns,
			   &lra_reg_info[sorted_pseudos[i]].insn_bitmap);
	}
      FOR_EACH_BB (bb)
	FOR_BB_INSNS (bb, insn)
	  if (bitmap_bit_p (&changed_insns, INSN_UID (insn)))
	    {
	      lra_insn_recog_data_t data;
	      struct lra_insn_reg *r;
	      
	      data = lra_get_insn_recog_data (insn);
	      for (r = data->regs; r != NULL; r = r->next)
		{
		  regno = r->regno;
		  if (regno < lra_constraint_new_regno_start
		      || bitmap_bit_p (&lra_inheritance_pseudos, regno)
		      || reg_renumber[regno] < 0)
		    continue;
		  sorted_pseudos[nfails++] = regno;
		  if (lra_dump_file != NULL)
		    fprintf (lra_dump_file,
			     "      Spill reload r%d(hr=%d, freq=%d)\n",
			     regno, reg_renumber[regno],
			     lra_reg_info[regno].freq);
		  update_lives (regno, true);
		  lra_setup_reg_renumber (regno, -1, false);
		}
	    }
      n = nfails;
    }
  bitmap_clear (&changed_insns);
  for (n = 0, i = FIRST_PSEUDO_REGISTER; i < max_reg_num (); i++)
    if ((i < lra_constraint_new_regno_start
	 || bitmap_bit_p (&lra_inheritance_pseudos, i))
	&& reg_renumber[i] < 0
	&& lra_reg_info[i].nrefs != 0 && lra_reg_info[i].first == i
	&& lra_get_preferred_class (i) != NO_REGS)
      sorted_pseudos[n++] = i;
  if (n != 0 && lra_dump_file != NULL)
    fprintf (lra_dump_file, "  Reassing non-reload pseudos\n");
  qsort (sorted_pseudos, n, sizeof (int), pseudo_compare_func);
  for (i = 0; i < n; i++)
    {
      int curr_regno;
	  
      regno = sorted_pseudos[i];
      hard_regno = find_hard_regno_for (regno, &cost);
      if (hard_regno >= 0)
	{
	  bitmap_set_bit (&changed_pseudo_bitmap, regno);
	  assign_hard_regno (hard_regno, regno);
	  /* We change allocation for non-reload pseudo on
	     this iteration -- mark it for invalidation used
	     alternative of insns containing the pseudo.  */
	  for (curr_regno = lra_reg_info[regno].first;
	       curr_regno >= 0;
	       curr_regno = lra_reg_info[curr_regno].next)
	    bitmap_set_bit (&changed_pseudo_bitmap, curr_regno);
	}
    }
  free (assigned_pseudos);
  free (assign_candidates);
  bitmap_clear (&assign_candidates_bitmap);
  bitmap_clear (&best_spill_pseudos_bitmap);
  bitmap_clear (&spill_pseudos_bitmap);
  bitmap_clear (&ignore_pseudos_bitmap);
  free (reload_insn_num);
}


/* Entry function to assign hard registers to new reload pseudos
   starting with LRA_CONSTRAINT_NEW_REGNO_START (by possible spilling
   of old pseudos) and possibly to the old pseudos.  The function adds
   what insns to process for the next constraint pass.  Those are all
   insns who contains non-reload and non-inheritance pseudos with
   changed allocation.

   Return true if we did not spill any non-reload and non-inheritance
   pseudos.  */
bool
lra_assign (void)
{
  unsigned int u;
  bitmap_iterator bi;
  bitmap_head insns_to_process;
  bool no_spills_p;

  init_lives ();
  sorted_pseudos = (int *) xmalloc (sizeof (int) * max_reg_num ());
  sorted_reload_pseudos = (int *) xmalloc (sizeof (int) * max_reg_num ());
  bitmap_initialize (&all_spilled_pseudos, &reg_obstack);
  setup_live_pseudos_and_spill_after_equiv_moves (&all_spilled_pseudos);
  /* Setup insns to process.  */
  bitmap_initialize (&changed_pseudo_bitmap, &reg_obstack);
  init_live_reload_pseudos ();
  assign_by_spills ();
  finish_live_reload_pseudos ();
  bitmap_ior_into (&changed_pseudo_bitmap, &all_spilled_pseudos);
  bitmap_and_compl_into (&all_spilled_pseudos, &lra_inheritance_pseudos);
  no_spills_p = bitmap_empty_p (&all_spilled_pseudos);
  bitmap_clear (&all_spilled_pseudos);
  bitmap_initialize (&insns_to_process, &reg_obstack);
  EXECUTE_IF_SET_IN_BITMAP (&changed_pseudo_bitmap, 0, u, bi)
    bitmap_ior_into (&insns_to_process, &lra_reg_info[u].insn_bitmap);
  bitmap_clear (&changed_pseudo_bitmap);
  EXECUTE_IF_SET_IN_BITMAP (&insns_to_process, 0, u, bi)
    {
      lra_push_insn_by_uid (u);
      /* Invalidate alternatives for insn should be processed.  */
      lra_set_used_insn_alternative_by_uid (u, -1);
    }
  bitmap_clear (&insns_to_process);
  free (sorted_pseudos);
  free (sorted_reload_pseudos);
  finish_lives ();
  return no_spills_p;
}
