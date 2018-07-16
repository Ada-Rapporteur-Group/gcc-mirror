/* Header file for wide int auxillary routines.
   Copyright (C) 2018 Free Software Foundation, Inc.
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

#ifndef WIDE_INT_AUX_H
#define WIDE_INT_AUX_H


extern bool do_cross_product (enum tree_code code, signop s, wide_int& lb,
			      wide_int& ub, const wide_int& lh_lb,
			      const wide_int& lh_ub, const wide_int& rh_lb,
			      const wide_int& rh_ub);

#endif /* WIDE_INT_AUX_H */
