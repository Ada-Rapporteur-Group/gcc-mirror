/* Header file for SSA range cache classes.
   Copyright (C) 2017-2018 Free Software Foundation, Inc.
   Contributed by Andrew MacLeod <amacleod@redhat.com>.

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

#ifndef GCC_SSA_RANGE_CACHE_H
#define GCC_SSA_RANGE_CACHE_H

// This global cache is used with the range engine as markers for what
// has been visited during this incarnation.  Once the ranger evaluates
// a name, it is typically not re-evaluated again.   
//

class ssa_global_cache
{
public:
  ssa_global_cache ();
  ~ssa_global_cache ();
  bool get_global_range (irange& r, tree name) const;
  void set_global_range (tree name, const irange&r);
  void clear_global_range (tree name);
  void clear ();
  void dump (FILE *f = stderr);
private:
  vec<irange_storage *> m_tab;
};

// Class used to track non-null references of an ssa-name
// A vector of bitmaps indexed by ssa-name is maintained. When indexed by 
// Basic Block, an on-bit indicates there is a non-null dereference for
// that ssa_name in that basic block.

class non_null_ref
{
public:
  non_null_ref ();
  ~non_null_ref ();
  bool non_null_deref_p (tree name, basic_block bb);
private:
  vec <bitmap> m_nn;
  void process_name (tree name);
};

// This class manages a vector of pointers to ssa_block ranges.
// THis provides the basis for the "range on entry" cache for
// all ssa-names.

class block_range_cache
{
public:
  block_range_cache ();
  ~block_range_cache ();

  // Hide the details of the block cache with these wrappers
  void set_bb_range (tree name, const basic_block bb, const irange &r);
  void set_bb_varying (tree name, const basic_block bb);
  bool get_bb_range (irange &r, tree name, const basic_block bb);
  bool bb_range_p (tree name, const basic_block bb);

  void dump (FILE *f);
  void dump (FILE *f, basic_block bb, bool print_varying = true);
private:
  vec<class ssa_block_ranges *> m_ssa_ranges;
  ssa_block_ranges& get_block_ranges (tree name);
};

class gori_cache : public gori_compute
{
public:
  gori_cache ();
  ~gori_cache ();
  bool non_null_deref_p (tree name, basic_block bb);
  bool block_range (irange &r, basic_block bb, tree name, bool calc = true);
  void dump_block (FILE *f, basic_block bb);

private:
  void add_to_update (basic_block bb);
  bool edge_range (irange &r, edge e, tree name);
  void fill_block_cache (tree name, basic_block bb, basic_block def_bb);
  void iterative_cache_update (tree name);

  block_range_cache m_on_entry;
  non_null_ref m_non_null;
  vec<basic_block> m_workback;
  vec<basic_block> m_update_list;
};

#endif // GCC_SSA_RANGE_CACHE_H
