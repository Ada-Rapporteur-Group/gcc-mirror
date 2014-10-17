/* Copyright (C) 2014 Free Software Foundation, Inc.
   Contributed by Mentor Embedded.

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

/* Exported (non-hidden) functions exposing libgomp interface for plugins.  */

#include <stdlib.h>

#include "libgomp.h"
#include "libgomp-plugin.h"
#include "target.h"

void *
gomp_plugin_malloc (size_t size)
{
  return gomp_malloc (size);
}

void *
gomp_plugin_malloc_cleared (size_t size)
{
  return gomp_malloc_cleared (size);
}

void *
gomp_plugin_realloc (void *ptr, size_t size)
{
  return gomp_realloc (ptr, size);
}

void
gomp_plugin_error (const char *msg, ...)
{
  va_list ap;
  
  va_start (ap, msg);
  gomp_verror (msg, ap);
  va_end (ap);
}

void
gomp_plugin_notify (const char *msg, ...)
{
  va_list ap;
  
  va_start (ap, msg);
  gomp_vnotify (msg, ap);
  va_end (ap);
}

void
gomp_plugin_fatal (const char *msg, ...)
{
  va_list ap;
  
  va_start (ap, msg);
  gomp_vfatal (msg, ap);
  va_end (ap);
  
  /* Unreachable.  */
  abort ();
}

void
gomp_plugin_mutex_init (gomp_mutex_t *mutex)
{
  gomp_mutex_init (mutex);
}

void
gomp_plugin_mutex_destroy (gomp_mutex_t *mutex)
{
  gomp_mutex_destroy (mutex);
}

void
gomp_plugin_mutex_lock (gomp_mutex_t *mutex)
{
  gomp_mutex_lock (mutex);
}

void
gomp_plugin_mutex_unlock (gomp_mutex_t *mutex)
{
  gomp_mutex_unlock (mutex);
}
