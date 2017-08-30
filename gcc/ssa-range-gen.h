/* Header file for ssa-range generator.
   Copyright (C) 2017 Free Software Foundation, Inc.
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

#ifndef GCC_SSA_RANGE_GEN_H
#define GCC_SSA_RANGE_GEN_H

#include "range.h"
#include "range-op.h"
#include "ssa-def-chain.h"
#include "ssa-range-stmt.h"


class ranger
{
  ssa_define_chain& def_chain;
  bool combine_range (range_stmt& stmt, irange& r, tree name, const irange& lhs,
		      bool op1_in_chain, bool op2_in_chain);
public:
  ranger (ssa_define_chain & dc);
  bool get_operand_range (irange& r, tree op);
  bool get_range (range_stmt& stmt, irange& r, tree name, const irange& lhs);
  bool get_range_from_stmt (gimple *stmt, irange& r, tree name,
			    const irange& lhs);
};

inline
ranger::ranger (ssa_define_chain& dc) : def_chain (dc)
{
}

class gori
{
  vec<bitmap> gori_map; 	/* Generates Outgoing Range Info.  */
  ssa_define_chain def_chain;
  ranger range_generator;
  bool remove_from_gori_map (basic_block bb, tree name);

  bool get_derived_range_stmt (range_stmt& stmt, tree name, basic_block bb);
  gimple *last_stmt_gori (basic_block bb);

  void build ();
  void build (basic_block bb);

public:
  gori ();

  /* True if NAME Generates range info on one or more outgoing edges of BB.  */
  bool range_p (basic_block bb, tree name);
  /* What is the static calculated range of NAME on outgoing edge E.  */
  bool range_on_edge (irange& r, tree name, edge e);
  /* What infomation does stmt g provide about name.  */
  bool range_on_stmt (irange& r, tree name, gimple *g);
  /* What infomation does stmt g provide about the defintion.  */
  bool range_of_def (irange& r, gimple *g);

  void dump (FILE *f);
  void exercise (FILE *f);   /* do a full mapping pass, dump if provided.  */
};




/* This class utilizes the basic block GORI map and is used to query the range
   of SSA_NAMEs across multiple basic blocks and edges.  */
class path_ranger : public gori
{
  public:
  path_ranger ();
  /* What is the known range of name from its DEF point to edge E.  */
  bool path_range_edge (irange& r, tree name, edge e);
  bool path_range_entry (irange& r, tree name, basic_block bb);
  bool path_range_stmt (irange& r, tree name, gimple *g);

  void dump (FILE *f);
  void exercise (FILE *f);   /* do a full mapping pass, dump if provided.  */
};

#endif /* GCC_SSA_RANGE_GEN_H */
