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

/* An interface to various libgomp-internal functions for use by plugins.  */

#ifndef LIBGOMP_PLUGIN_H
#define LIBGOMP_PLUGIN_H 1

#include "mutex.h"

/* alloc.c */

extern void *gomp_plugin_malloc (size_t) __attribute__((malloc));
extern void *gomp_plugin_malloc_cleared (size_t) __attribute__((malloc));
extern void *gomp_plugin_realloc (void *, size_t);

/* error.c */

extern void gomp_plugin_notify(const char *msg, ...);
extern void gomp_plugin_error (const char *, ...)
	__attribute__((format (printf, 1, 2)));
extern void gomp_plugin_fatal (const char *, ...)
	__attribute__((noreturn, format (printf, 1, 2)));

/* mutex.c */

extern void gomp_plugin_mutex_init (gomp_mutex_t *mutex);
extern void gomp_plugin_mutex_destroy (gomp_mutex_t *mutex);
extern void gomp_plugin_mutex_lock (gomp_mutex_t *mutex);
extern void gomp_plugin_mutex_unlock (gomp_mutex_t *mutex);

/* target.c */

extern void gomp_plugin_async_unmap_vars (void *ptr);

#endif
