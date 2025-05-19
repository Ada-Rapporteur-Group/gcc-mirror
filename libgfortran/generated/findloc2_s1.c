/* Implementation of the FINDLOC intrinsic
   Copyright (C) 2018-2025 Free Software Foundation, Inc.
   Contributed by Thomas König <tk@tkoenig.net>

This file is part of the GNU Fortran 95 runtime library (libgfortran).

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

#ifdef HAVE_GFC_UINTEGER_1
index_type findloc2_s1 (gfc_array_s1 * const restrict array,
			   const GFC_UINTEGER_1 * restrict value, GFC_LOGICAL_4 back,
			   gfc_charlen_type len_array, gfc_charlen_type len_value);
export_proto(findloc2_s1);

index_type
findloc2_s1 (gfc_array_s1 * const restrict array, const GFC_UINTEGER_1 * restrict value,
		      GFC_LOGICAL_4 back,
		      gfc_charlen_type len_array, gfc_charlen_type len_value)
{
  index_type i;
  index_type sspacing;
  index_type extent;
  const GFC_UINTEGER_1 * restrict src;

  extent = GFC_DESCRIPTOR_EXTENT(array,0);
  if (extent <= 0)
    return 0;

  sspacing = GFC_DESCRIPTOR_SPACING(array,0);
  if (back)
    {
      src = (const GFC_UINTEGER_1*) (((const char*) array->base_addr) + (extent - 1) * sspacing);
      for (i = extent; i >= 0; i--)
	{
	  if (compare_string (len_array, (char *) src, len_value, (char *) value) == 0)
	    return i;
	  src = (const GFC_UINTEGER_1*) (((char*)src) - sspacing);
	}
    }
  else
    {
      src = array->base_addr;
      for (i = 1; i <= extent; i++)
	{
	  if (compare_string (len_array, (char *) src, len_value, (char *) value) == 0)
	    return i;
	  src = (const GFC_UINTEGER_1*) (((char*)src) + sspacing);
	}
    }
  return 0;
}

index_type mfindloc2_s1 (gfc_array_s1 * const restrict array,
			 const GFC_UINTEGER_1 * restrict value,
			 gfc_array_l1 *const restrict mask, GFC_LOGICAL_4 back,
			 gfc_charlen_type len_array, gfc_charlen_type len_value);
export_proto(mfindloc2_s1);

index_type
mfindloc2_s1 (gfc_array_s1 * const restrict array,
			   const GFC_UINTEGER_1 * restrict value, gfc_array_l1 *const restrict mask,
			   GFC_LOGICAL_4 back, gfc_charlen_type len_array,
			   gfc_charlen_type len_value)
{
  index_type i;
  index_type sspacing;
  index_type extent;
  const GFC_UINTEGER_1 * restrict src;
  const GFC_LOGICAL_1 * restrict mbase;
  int mask_kind;
  index_type mspacing;

  extent = GFC_DESCRIPTOR_EXTENT(array,0);
  if (extent <= 0)
    return 0;

  mask_kind = GFC_DESCRIPTOR_SIZE (mask);
  mbase = mask->base_addr;

  if (mask_kind == 1 || mask_kind == 2 || mask_kind == 4 || mask_kind == 8
#ifdef HAVE_GFC_LOGICAL_16
      || mask_kind == 16
#endif
      )
    mbase = GFOR_POINTER_TO_L1 (mbase, mask_kind);
  else
    internal_error (NULL, "Funny sized logical array");

  sspacing = GFC_DESCRIPTOR_SPACING(array,0);
  mspacing = GFC_DESCRIPTOR_SPACING(mask,0);

  if (back)
    {
      src = (const GFC_UINTEGER_1*) (((char*) array->base_addr) + (extent - 1) * sspacing);
      mbase += (extent - 1) * mspacing;
      for (i = extent; i >= 0; i--)
	{
	  if (*mbase && (compare_string (len_array, (char *) src, len_value, (char *) value) == 0))
	    return i;
	  src = (const GFC_UINTEGER_1*) (((char*)src) - sspacing);
	  mbase -= mspacing;
	}
    }
  else
    {
      src = array->base_addr;
      for (i = 1; i <= extent; i++)
	{
	  if (*mbase && (compare_string (len_array, (char *) src, len_value, (char *) value) == 0))
	    return i;
	  src = (const GFC_UINTEGER_1*) (((char*)src) + sspacing);
	  mbase += mspacing;
	}
    }
  return 0;
}
index_type sfindloc2_s1 (gfc_array_s1 * const restrict array,
			 const GFC_UINTEGER_1 * restrict value,
			 GFC_LOGICAL_4 *const restrict mask, GFC_LOGICAL_4 back,
			 gfc_charlen_type len_array, gfc_charlen_type len_value);
export_proto(sfindloc2_s1);

index_type
sfindloc2_s1 (gfc_array_s1 * const restrict array,
			   const GFC_UINTEGER_1 * restrict value, GFC_LOGICAL_4 *const restrict mask,
			   GFC_LOGICAL_4 back, gfc_charlen_type len_array,
			   gfc_charlen_type len_value)
{
  if (mask == NULL || *mask)
    {
      return findloc2_s1 (array, value, back, len_array, len_value);
    }
  return 0;
}
#endif
