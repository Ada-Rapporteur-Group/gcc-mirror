/* Copyright (C) 1989-2020 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/* Decimal64 -> _Float128 conversion.  */

/* FINE_GRAINED_LIBRARIES is used so we can isolate just to dd_to_tf conversion
   function from dp-bits.c.  */
#define FINE_GRAINED_LIBRARIES	1
#define L_dd_to_tf		1
#define WIDTH			64

#if !defined(__LONG_DOUBLE_128__) || !defined(__LONG_DOUBLE_IEEE128__)
#error "Long double is not IEEE 128-bit"
#endif

/* If we don't have at least GLIBC 2.32, the strtold used by dfp-bit.c does not
   have support for float128.  Add an abort in case this is called.  */
#if ((__GLIBC__ * 1000) + __GLIBC_MINOR__) < 2032

#include <stdlib.h>
extern long double __dpd_extendddkf (_Decimal64);

long double
__dpd_extendddkf (_Decimal64 x __attribute__ ((unused)))
{
  abort ();
}

#else

/* Map the external name to the float128 default.  */
#define __dpd_extendddtf	__dpd_extendddkf

/* Use dfp-bit.c to do the real work.  */
#include "dfp-bit.c"
#endif
