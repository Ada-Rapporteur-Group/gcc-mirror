/* Copyright (C) 2013-2014 Free Software Foundation, Inc.

   Contributed by Thomas Schwinge <thomas@codesourcery.com>.

   This file is part of the GNU OpenMP Library (libgomp).

   Libgomp is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   Libgomp is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* This file handles OpenACC constructs.  */

#include "openacc.h"
#include "libgomp.h"
#include "libgomp_g.h"
#include "gomp-constants.h"
#include "target.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <alloca.h>

#ifdef FUTURE
// device geometry per device type
struct devgeom
{
  int gangs;
  int workers;
  int vectors;
};
  

// XXX: acceptable defaults?
static __thread struct devgeom devgeom = { 1, 1, 1 };
#endif

#ifdef LATER
static void
dump_devaddrs(void)
{
  int i;
  struct devaddr *dp;

  gomp_notify("++++ num_devaddrs %d\n", num_devaddrs);
  for (dp = devaddrs, i = 1; dp != 0; dp = dp->next, i++)
    {
      gomp_notify("++++ %.02d) %p\n", i, dp->d);
    }
}
#endif

static void
dump_var(char *s, size_t idx, void *hostaddr, size_t size, unsigned char kind)
{
  gomp_notify(" %2zi: %3s 0x%.2x -", idx, s, kind & 0xff);

  switch (kind & 0xff)
    {
      case 0x00: gomp_notify(" ALLOC              "); break;
      case 0x01: gomp_notify(" ALLOC TO           "); break;
      case 0x02: gomp_notify(" ALLOC FROM         "); break;
      case 0x03: gomp_notify(" ALLOC TOFROM       "); break;
      case 0x04: gomp_notify(" POINTER            "); break;
      case 0x05: gomp_notify(" TO_PSET            "); break;

      case 0x08: gomp_notify(" FORCE_ALLOC        "); break;
      case 0x09: gomp_notify(" FORCE_TO           "); break;
      case 0x0a: gomp_notify(" FORCE_FROM         "); break;
      case 0x0b: gomp_notify(" FORCE_TOFROM       "); break;
      case 0x0c: gomp_notify(" FORCE_PRESENT      "); break;
      case 0x0d: gomp_notify(" FORCE_DEALLOC      "); break;
      case 0x0e: gomp_notify(" FORCE_DEVICEPTR    "); break;

      case 0x18: gomp_notify(" FORCE_PRIVATE      "); break;
      case 0x19: gomp_notify(" FORCE_FIRSTPRIVATE "); break;

      case (unsigned char) -1: gomp_notify(" DUMMY              "); break;
      default: gomp_notify("UGH! 0x%x\n", kind);
    }
    
  gomp_notify("- %d - %4d/0x%04x ", 1 << (kind >> 8), (int)size, (int)size);
  gomp_notify("- %p\n", hostaddr);

  return;
}

/* Ensure that the target device for DEVICE_TYPE is initialised (and that
   plugins have been loaded if appropriate).  The ACC_dev variable for the
   current thread will be set appropriately for the given device type on
   return.  */

attribute_hidden void
select_acc_device (int device_type)
{
  if (device_type == GOMP_IF_CLAUSE_FALSE)
    return;

  if (device_type == acc_device_none)
    device_type = acc_device_host;

  if (device_type >= 0)
    {
      /* NOTE: this will go badly if the surrounding data environment is set up
         to use a different device type.  We'll just have to trust that users
	 know what they're doing...  */
      acc_set_device_type (device_type);
    }

  ACC_lazy_initialize ();
}

void goacc_wait (int async, int num_waits, va_list ap);

void
GOACC_parallel (int device, void (*fn) (void *), const void *openmp_target,
		size_t mapnum, void **hostaddrs, size_t *sizes,
		unsigned short *kinds,
		int num_gangs, int num_workers, int vector_length,
		int async, int num_waits, ...)
{
  bool if_clause_condition_value = device != GOMP_IF_CLAUSE_FALSE;
  va_list ap;
  struct target_mem_desc *tgt;
  void **devaddrs;
  unsigned int i;
  struct splay_tree_key_s k;
  splay_tree_key tgt_fn_key;
  void (*tgt_fn);

  if (num_gangs != 1)
    gomp_fatal ("num_gangs (%d) different from one is not yet supported",
		num_gangs);
  if (num_workers != 1)
    gomp_fatal ("num_workers (%d) different from one is not yet supported",
		num_workers);

  gomp_notify ("%s: mapnum=%zd, hostaddrs=%p, sizes=%p, kinds=%p, async=%d\n",
	       __FUNCTION__, mapnum, hostaddrs, sizes, kinds, async);

  select_acc_device (device);

  /* Host fallback if "if" clause is false or if the current device is set to
     the host.  */
  if (!if_clause_condition_value)
    {
      ACC_save_and_set_bind (acc_device_host);
      fn (hostaddrs);
      ACC_restore_bind ();
      return;
    }
  else if (acc_device_type (ACC_dev->type) == acc_device_host)
    {
      fn (hostaddrs);
      return;
    }

  va_start (ap, num_waits);
  
  if (num_waits > 0)
    goacc_wait (async, num_waits, ap);

  va_end (ap);

  ACC_dev->openacc.async_set_async_func (async);

  if (!(ACC_dev->capabilities & TARGET_CAP_NATIVE_EXEC))
    {
      k.host_start = (uintptr_t) fn;
      k.host_end = k.host_start + 1;
      gomp_mutex_lock (&ACC_memmap->mem_map.lock);
      tgt_fn_key = splay_tree_lookup (&ACC_memmap->mem_map.splay_tree, &k);
      gomp_mutex_unlock (&ACC_memmap->mem_map.lock);

      if (tgt_fn_key == NULL)
	gomp_fatal ("target function wasn't mapped: perhaps -fopenacc was "
		    "used without -flto?");

      tgt_fn = (void (*)) tgt_fn_key->tgt->tgt_start;
    }
  else
    tgt_fn = (void (*)) fn;

  tgt = gomp_map_vars ((struct gomp_device_descr *) ACC_dev,
		       &ACC_memmap->mem_map, mapnum, hostaddrs,
		       NULL, sizes, kinds, true, false);

  devaddrs = alloca (sizeof (void *) * mapnum);
  for (i = 0; i < mapnum; i++)
    devaddrs[i] = (void *) (tgt->list[i]->tgt->tgt_start
			    + tgt->list[i]->tgt_offset);

  ACC_dev->openacc.exec_func (tgt_fn, mapnum, hostaddrs, devaddrs, sizes, kinds,
			      num_gangs, num_workers, vector_length, async,
			      tgt);

  /* If running synchronously, unmap immediately.  */
  if (async < acc_async_noval)
    gomp_unmap_vars (tgt, true);
  else
    {
      gomp_copy_from_async (tgt);
      ACC_dev->openacc.register_async_cleanup_func (tgt);
    }

  ACC_dev->openacc.async_set_async_func (acc_async_sync);
}

static __thread struct target_mem_desc *mapped_data = NULL;

void
GOACC_data_start (int device, const void *openmp_target, size_t mapnum,
		  void **hostaddrs, size_t *sizes, unsigned short *kinds)
{
  bool if_clause_condition_value = device != GOMP_IF_CLAUSE_FALSE;
  struct target_mem_desc *tgt;

  gomp_notify ("%s: mapnum=%zd, hostaddrs=%p, sizes=%p, kinds=%p\n",
	       __FUNCTION__, mapnum, hostaddrs, sizes, kinds);

  select_acc_device (device);

  /* Host fallback or 'do nothing'.  */
  if ((ACC_dev->capabilities & TARGET_CAP_SHARED_MEM)
      || !if_clause_condition_value)
    {
      tgt = gomp_map_vars (NULL, NULL, 0, NULL, NULL, NULL, NULL, true, false);
      tgt->prev = mapped_data;
      mapped_data = tgt;

      return;
    }

  gomp_notify ("  %s: prepare mappings\n", __FUNCTION__);
  tgt = gomp_map_vars ((struct gomp_device_descr *) ACC_dev,
		       &ACC_memmap->mem_map, mapnum, hostaddrs,
		       NULL, sizes, kinds, true, false);
  gomp_notify ("  %s: mappings prepared\n", __FUNCTION__);
  tgt->prev = mapped_data;
  mapped_data = tgt;
}

void
GOACC_data_end (void)
{
  struct target_mem_desc *tgt = mapped_data;

  gomp_notify ("  %s: restore mappings\n", __FUNCTION__);
  mapped_data = tgt->prev;
  gomp_unmap_vars (tgt, true);
  gomp_notify ("  %s: mappings restored\n", __FUNCTION__);
}


void
GOACC_kernels (int device, void (*fn) (void *), const void *openmp_target,
	       size_t mapnum, void **hostaddrs, size_t *sizes,
	       unsigned short *kinds,
	       int num_gangs, int num_workers, int vector_length,
	       int async, int num_waits, ...)
{
  gomp_notify ("%s: mapnum=%zd, hostaddrs=%p, sizes=%p, kinds=%p\n", __FUNCTION__,
	 mapnum, hostaddrs, sizes, kinds);

  va_list ap;

  select_acc_device (device);

  va_start (ap, num_waits);

  if (num_waits > 0)
    goacc_wait (async, num_waits, ap);

  va_end (ap);

  /* TODO.  */
  GOACC_parallel (device, fn, openmp_target, mapnum, hostaddrs, sizes, kinds,
		  num_gangs, num_workers, vector_length, async, num_waits);
}

void
goacc_wait (int async, int num_waits, va_list ap)
{
  int i;

  assert (num_waits >= 0);

  if (async == acc_async_sync && num_waits == 0)
    {
      acc_wait_all ();
      return;
    }

  if (async == acc_async_sync && num_waits)
    {
      for (i = 0; i < num_waits; i++)
        {
          int qid = va_arg (ap, int);

          if (acc_async_test (qid))
            continue;

          acc_wait (qid);
        }
      return;
    }

  if (async == acc_async_noval && num_waits == 0)
    {
      ACC_dev->openacc.async_wait_all_async_func (acc_async_noval);
      return;
    }

  for (i = 0; i < num_waits; i++)
    {
      int qid = va_arg (ap, int);

      if (acc_async_test (qid))
	continue;

      /* If we're waiting on the same asynchronous queue as we're launching on,
         the queue itself will order work as required, so there's no need to
	 wait explicitly.  */
      if (qid != async)
	ACC_dev->openacc.async_wait_async_func (qid, async);
    }
}

void
GOACC_update (int device, const void *openmp_target, size_t mapnum,
	      void **hostaddrs, size_t *sizes, unsigned short *kinds,
	      int async, int num_waits, ...)
{
  bool if_clause_condition_value = device != GOMP_IF_CLAUSE_FALSE;
  size_t i;

  select_acc_device (device);

  if ((ACC_dev->capabilities & TARGET_CAP_SHARED_MEM)
      || !if_clause_condition_value)
    return;

  if (num_waits > 0)
    {
      va_list ap;

      va_start (ap, num_waits);

      goacc_wait (async, num_waits, ap);

      va_end (ap);
    }

  ACC_dev->openacc.async_set_async_func (async);

  for (i = 0; i < mapnum; ++i)
    {
      unsigned char kind = kinds[i] & 0xff;

      dump_var("UPD", i, hostaddrs[i], sizes[i], kinds[i]);

      switch (kind)
	{
	  case GOMP_MAP_POINTER:
	     break;

	  case GOMP_MAP_FORCE_TO:
	     acc_update_device (hostaddrs[i], sizes[i]);
	     break;

	  case GOMP_MAP_FORCE_FROM:
	     acc_update_self (hostaddrs[i], sizes[i]);
	     break;

	  default:
	     gomp_fatal (">>>> GOACC_update UNHANDLED kind 0x%.2x", kind);
	     break;
	}
    }

  ACC_dev->openacc.async_set_async_func (acc_async_sync);
}

void
GOACC_wait (int async, int num_waits, ...)
{
  va_list ap;

  va_start (ap, num_waits);

  goacc_wait (async, num_waits, ap);

  va_end (ap);
}
