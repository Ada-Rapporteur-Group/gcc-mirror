/* c-upc-low.h: declarations for upc-low.c
   Copyright (C) 2006-2014 Free Software Foundation, Inc.
   Contributed by Gary Funck <gary@intrepid.com>
     and Nenad Vukicevic <nenad@intrepid.com>.

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

#ifndef GCC_C_FAMILY_UPC_LOW_H
#define GCC_C_FAMILY_UPC_LOW_H 1

extern void upc_genericize (tree);
extern void upc_genericize_init (void);
extern void upc_genericize_finish (void);

extern int upc_check_decl_init (tree, tree);
extern void upc_decl_init (tree, tree);
extern void upc_write_global_declarations (void);

#endif /* !GCC_C_FAMILY_UPC_LOW_H */
