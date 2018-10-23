/* Global ssa ranges. 
   Copyright (C) 2018 Free Software Foundation, Inc.
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

/* This "global" cache is used with the range engine until such time
   that we can unify everything to the ranges that are contained in 
   the ssa_name itself.  There appears to be some issues with reading an
   writing that at the moment, and there ought to be a central place to
   read/write global ranges anyway, rather than direct SSA_NAME read/write.

   When retreiving a global name, a check is first made to see if the 
   global irange cache has a range associated with it, and that is returned
   if it does.  If it does not, then any range assocaited with the
   existing SSA_NAME_RANGE_INFO field is extracted and that is used.

   Any SETs of ranges are localized to the global cache maintained here.

   At the end of range generation/processing, a call is made to
   copy_to_range_info() to flush this cache into the SSA_NAME_RANGE_INFO
   fields.  */


#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "insn-codes.h"
#include "rtl.h"
#include "tree.h"
#include "gimple.h"
#include "ssa.h"
#include "optabs-tree.h"
#include "gimple-pretty-print.h"
#include "diagnostic-core.h"
#include "gimple-range.h"
#include "ssa-range-global.h"

/* Initialize a global cache.  */
ssa_global_cache::ssa_global_cache ()
{
  m_tab.create (0);
  m_tab.safe_grow_cleared (num_ssa_names);
}

/* Deconstruct a global cache.  */
ssa_global_cache::~ssa_global_cache ()
{
  m_tab.release ();
}

/* Retrieve the global range of NAME from cache memory if it exists.  Return
   the value in R.  */
bool
ssa_global_cache::get_global_range (irange &r, tree name) const
{
  irange_storage *stow = m_tab[SSA_NAME_VERSION (name)];
  if (stow)
    {
      r = irange (TREE_TYPE (name), stow);
      return true;
    }
  r = range_from_ssa (name);
  return false;
}

/* Set the range for NAME to R in the glonbal cache.  */
void
ssa_global_cache::set_global_range (tree name, const irange& r)
{
  irange_storage *m = m_tab[SSA_NAME_VERSION (name)];

  if (m)
    m->set_irange (r);
  else
    {
      m = irange_storage::ggc_alloc_init (r);
      m_tab[SSA_NAME_VERSION (name)] = m;
    }
}

/* Set the range for NAME to R in the glonbal cache.  */
void
ssa_global_cache::clear_global_range (tree name)
{
  m_tab[SSA_NAME_VERSION (name)] = NULL;
}

/* Clear the global cache.  */
void
ssa_global_cache::clear ()
{
  memset (m_tab.address(), 0, m_tab.length () * sizeof (irange_storage *));
}

/* Dump the contents of the global cache to F.  */
void
ssa_global_cache::dump (FILE *f)
{
  unsigned x;
  irange r;
  for ( x = 1; x < num_ssa_names; x++)
    if (gimple_range::valid_ssa_p (ssa_name (x)) &&
	get_global_range (r, ssa_name (x)))
      {
        print_generic_expr (f, ssa_name (x), TDF_NONE);
	fprintf (f, "  : ");
        r.dump (f);
      }
}


