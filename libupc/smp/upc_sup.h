/* Copyright (C) 2001 Free Software Foundation, Inc.
   This file is part of the UPC runtime Library.
   Written by Gary Funck <gary@intrepid.com>
   and Nenad Vukicevic <nenad@intrepid.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2, or (at
   your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA.

   As a special exception, if you link this library with files
   compiled with a GNU compiler to produce an executable, this does
   not cause the resulting executable to be covered by the GNU General
   Public License.  This exception does not however invalidate any
   other reasons why the executable file might be covered by the GNU
   General Public License.  */

#ifndef _UPC_SUP_H_
#define _UPC_SUP_H_

/* Internal runtime routines and external symbols.  */

//begin lib_runtime_api

extern void *__cvtaddr (upc_shared_ptr_t);
extern void *__getaddr (upc_shared_ptr_t);
extern void __upc_barrier (int barrier_id);
extern void __upc_notify (int barrier_id);
extern void __upc_wait (int barrier_id);
extern void __upc_exit (int status) __attribute__ ((__noreturn__));
extern void __upc_fatal (const char *msg) __attribute__ ((__noreturn__));

/* Profiled versions of runtime routines.  */
extern void *__cvtaddrg (upc_shared_ptr_t, const char *filename, const int linenum);
extern void *__getaddrg (upc_shared_ptr_t, const char *filename, const int linenum);
extern void __upc_barrierg (int barrier_id, const char *filename, const int linenum);
extern void __upc_notifyg (int barrier_id, const char *filename, const int linenum);
extern void __upc_waitg (int barrier_id, const char *filename, const int linenum);
extern void __upc_exitg (int status, const char *filename, const int linenum)
                        __attribute__ ((__noreturn__));
extern void __upc_funcg (int start, const char *funcname,
                         const char *filename, const int linenum);
extern void __upc_forallg (int start, const char *filename, const int linenum);
//end lib_runtime_api

//begin lib_heap_api

extern void __upc_acquire_alloc_lock (void);
extern void __upc_release_alloc_lock (void);
//end lib_heap_api

//begin lib_vm_api

extern void *__upc_vm_map_addr (upc_shared_ptr_t);
extern void __upc_vm_alloc (upc_page_num_t);
extern upc_page_num_t __upc_vm_get_cur_page_alloc (void);
//end lib_vm_api

extern void __upc_heap_init (upc_shared_ptr_t, size_t);
extern int __upc_start (int argc, char *argv[]);
extern void __upc_validate_pgm_info (char *);
extern void __upc_vm_init_per_thread (void);
extern void __upc_vm_init (upc_page_num_t);

//begin lib_sptr_to_addr

/* To speed things up, the last two unique (page, thread)
   lookups are cached.  Caller must validate the pointer
   'p' (check for NULL, etc.) before calling this routine. */
__attribute__((__always_inline__))
static inline
void *
__upc_sptr_to_addr (upc_shared_ptr_t p)
{
  extern GUPCR_THREAD_LOCAL unsigned long __upc_page1_ref, __upc_page2_ref;
  extern GUPCR_THREAD_LOCAL void *__upc_page1_base, *__upc_page2_base;
  void *addr;
  size_t offset, p_offset;
  upc_page_num_t pn;
  unsigned long this_page;
  offset = GUPCR_PTS_OFFSET (p);
  p_offset = offset & GUPCR_VM_OFFSET_MASK;
  pn = (offset >> GUPCR_VM_OFFSET_BITS) & GUPCR_VM_PAGE_MASK;
  this_page = (pn << GUPCR_THREAD_SIZE) | GUPCR_PTS_THREAD (p);
  if (this_page == __upc_page1_ref)
    addr = __upc_page1_base + p_offset;
  else if (this_page == __upc_page2_ref)
    addr = __upc_page2_base + p_offset;
  else
    addr = __upc_vm_map_addr (p);
  return addr;
}
//end lib_sptr_to_addr

#endif /* _UPC_SUP_H_ */
