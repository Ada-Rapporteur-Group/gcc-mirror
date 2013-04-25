/* Generic helper function for repacking arrays.
   Copyright (C) 2003-2013 Free Software Foundation, Inc.
   Contributed by Paul Brook <paul@nowt.org>

This file is part of the GNU Fortran runtime library (libgfortran).

Libgfortran is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

Libgfortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#include "libgfortran.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern void *internal_pack (gfc_array_char *);
export_proto(internal_pack);

void *
internal_pack (gfc_array_char * source)
{
  index_type count[GFC_MAX_DIMENSIONS];
  index_type extent[GFC_MAX_DIMENSIONS];
  index_type sm[GFC_MAX_DIMENSIONS];
  index_type dim;
  index_type ssize;
  index_type sm0;
  const char *src;
  char *dest;
  void *destptr;
  int n;
  int packed;
  index_type size;
  index_type type_size;

  if (source->base_addr == NULL)
    return NULL;

  type_size = GFC_DTYPE_TYPE_SIZE(source);
  switch (type_size)
    {
    case GFC_DTYPE_INTEGER_1:
    case GFC_DTYPE_LOGICAL_1:
    case GFC_DTYPE_DERIVED_1:
      return internal_pack_1 ((gfc_array_i1 *) source);

    case GFC_DTYPE_INTEGER_2:
    case GFC_DTYPE_LOGICAL_2:
      return internal_pack_2 ((gfc_array_i2 *) source);

    case GFC_DTYPE_INTEGER_4:
    case GFC_DTYPE_LOGICAL_4:
      return internal_pack_4 ((gfc_array_i4 *) source);
	
    case GFC_DTYPE_INTEGER_8:
    case GFC_DTYPE_LOGICAL_8:
      return internal_pack_8 ((gfc_array_i8 *) source);

#if defined(HAVE_GFC_INTEGER_16)
    case GFC_DTYPE_INTEGER_16:
    case GFC_DTYPE_LOGICAL_16:
      return internal_pack_16 ((gfc_array_i16 *) source);
#endif
    case GFC_DTYPE_REAL_4:
      return internal_pack_r4 ((gfc_array_r4 *) source);

    case GFC_DTYPE_REAL_8:
      return internal_pack_r8 ((gfc_array_r8 *) source);

/* FIXME: This here is a hack, which will have to be removed when
   the array descriptor is reworked.  Currently, we don't store the
   kind value for the type, but only the size.  Because on targets with
   __float128, we have sizeof(logn double) == sizeof(__float128),
   we cannot discriminate here and have to fall back to the generic
   handling (which is suboptimal).  */
#if !defined(GFC_REAL_16_IS_FLOAT128)
# if defined (HAVE_GFC_REAL_10)
    case GFC_DTYPE_REAL_10:
      return internal_pack_r10 ((gfc_array_r10 *) source);
# endif

# if defined (HAVE_GFC_REAL_16)
    case GFC_DTYPE_REAL_16:
      return internal_pack_r16 ((gfc_array_r16 *) source);
# endif
#endif

    case GFC_DTYPE_COMPLEX_4:
      return internal_pack_c4 ((gfc_array_c4 *) source);
	
    case GFC_DTYPE_COMPLEX_8:
      return internal_pack_c8 ((gfc_array_c8 *) source);

/* FIXME: This here is a hack, which will have to be removed when
   the array descriptor is reworked.  Currently, we don't store the
   kind value for the type, but only the size.  Because on targets with
   __float128, we have sizeof(logn double) == sizeof(__float128),
   we cannot discriminate here and have to fall back to the generic
   handling (which is suboptimal).  */
#if !defined(GFC_REAL_16_IS_FLOAT128)
# if defined (HAVE_GFC_COMPLEX_10)
    case GFC_DTYPE_COMPLEX_10:
      return internal_pack_c10 ((gfc_array_c10 *) source);
# endif

# if defined (HAVE_GFC_COMPLEX_16)
    case GFC_DTYPE_COMPLEX_16:
      return internal_pack_c16 ((gfc_array_c16 *) source);
# endif
#endif

    case GFC_DTYPE_DERIVED_2:
      if (GFC_UNALIGNED_2(source->base_addr))
	break;
      else
	return internal_pack_2 ((gfc_array_i2 *) source);

    case GFC_DTYPE_DERIVED_4:
      if (GFC_UNALIGNED_4(source->base_addr))
	break;
      else
	return internal_pack_4 ((gfc_array_i4 *) source);

    case GFC_DTYPE_DERIVED_8:
      if (GFC_UNALIGNED_8(source->base_addr))
	break;
      else
	return internal_pack_8 ((gfc_array_i8 *) source);

#ifdef HAVE_GFC_INTEGER_16
    case GFC_DTYPE_DERIVED_16:
      if (GFC_UNALIGNED_16(source->base_addr))
	break;
      else
	return internal_pack_16 ((gfc_array_i16 *) source);
#endif

    default:
      break;
    }

  dim = GFC_DESCRIPTOR_RANK (source);
  size = GFC_DESCRIPTOR_ELEM_LEN (source);
  ssize = size;
  packed = 1;
  for (n = 0; n < dim; n++)
    {
      count[n] = 0;
      sm[n] = GFC_DESCRIPTOR_SM(source,n);
      extent[n] = GFC_DESCRIPTOR_EXTENT(source,n);
      if (extent[n] <= 0)
        {
          /* Do nothing.  */
          packed = 1;
          break;
        }

      if (ssize != sm[n])
        packed = 0;

      ssize *= extent[n];
    }

  if (packed)
    return source->base_addr;

   /* Allocate storage for the destination.  */
  destptr = xmalloc (ssize * size);
  dest = (char *)destptr;
  src = source->base_addr;
  sm0 = sm[0];

  while (src)
    {
      /* Copy the data.  */
      memcpy(dest, src, size);
      /* Advance to the next element.  */
      dest += size;
      src += sm0;
      count[0]++;
      /* Advance to the next source element.  */
      n = 0;
      while (count[n] == extent[n])
        {
          /* When we get to the end of a dimension, reset it and increment
             the next dimension.  */
          count[n] = 0;
          /* We could precalculate these products, but this is a less
             frequently used path so probably not worth it.  */
          src -= sm[n] * extent[n];
          n++;
          if (n == dim)
            {
              src = NULL;
              break;
            }
          else
            {
              count[n]++;
              src += sm[n];
            }
        }
    }
  return destptr;
}
