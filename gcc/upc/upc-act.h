/* upc-act.h: define interfaces to UPC-related actions
   Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
   2010, 2011
   Free Software Foundation, Inc.
   Contributed by Gary Funck <gary@intrepid.com>
     and Nenad Vukicevic <nenad@intrepid.com>.
   Based on original implementation
     by Jesse M. Draper <jdraper@super.org>
     and William W. Carlson <wwc@super.org>.

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

#ifndef _UPC_ACT_H_
#define _UPC_ACT_H_


extern bool upc_handle_option (size_t, const char *, int, int, location_t,
                              const struct cl_option_handlers *);
extern bool upc_lang_init (void);
extern void upc_finish (void);
extern void upc_write_global_declarations (void);
extern void upc_write_init_func (void);
extern void upc_free_unshared_var_table (void);
extern void upc_check_decl (tree);
extern int upc_types_compatible_p (tree, tree);
extern int upc_inner_shared_ref_p (tree);

/* used by c-parser */
extern tree upc_build_sync_stmt (location_t, tree, tree);
extern tree upc_affinity_test (location_t, tree);
extern struct c_expr upc_blocksizeof_expr (location_t, struct c_expr);
extern struct c_expr upc_blocksizeof_type (location_t, struct c_type_name *);
extern struct c_expr upc_elemsizeof_expr (location_t, struct c_expr);
extern struct c_expr upc_elemsizeof_type (location_t, struct c_type_name *);
extern struct c_expr upc_localsizeof_expr (location_t, struct c_expr);
extern struct c_expr upc_localsizeof_type (location_t, struct c_type_name *);

/* UPC-specific routines */
extern tree upc_num_threads (void);
extern int is_valid_pts_p (tree);

#endif /* !_UPC_ACT_H_ */
