dnl Support macro file for intrinsic functions.
dnl Contains the generic sections of the array functions.
dnl This file is part of the GNU Fortran Runtime Library (libgfortran)
dnl Distributed under the GNU GPL with exception.  See COPYING for details.
define(START_FOREACH_FUNCTION,
`
extern void name`'rtype_qual`_'atype_code (rtype * const restrict retarray, 
	atype * const restrict array, GFC_LOGICAL_4);
export_proto(name`'rtype_qual`_'atype_code);

void
name`'rtype_qual`_'atype_code (rtype * const restrict retarray, 
	atype * const restrict array, GFC_LOGICAL_4 back)
{
  index_type count[GFC_MAX_DIMENSIONS];
  index_type extent[GFC_MAX_DIMENSIONS];
  index_type sspacing[GFC_MAX_DIMENSIONS];
  index_type dspacing;
  const atype_name *base;
  rtype_name * restrict dest;
  index_type rank;
  index_type n;

  rank = GFC_DESCRIPTOR_RANK (array);
  if (rank <= 0)
    runtime_error ("Rank of array needs to be > 0");

  if (retarray->base_addr == NULL)
    {
      GFC_DESCRIPTOR_DIMENSION_SET(retarray, 0, 0, rank-1, sizeof (rtype_name));
      retarray->dtype.rank = 1;
      retarray->offset = 0;
      retarray->base_addr = xmallocarray (rank, sizeof (rtype_name));
    }
  else
    {
      if (unlikely (compile_options.bounds_check))
	bounds_iforeach_return ((array_t *) retarray, (array_t *) array,
				"u_name");
    }

  dspacing = GFC_DESCRIPTOR_SPACING(retarray,0);
  dest = retarray->base_addr;
  for (n = 0; n < rank; n++)
    {
      sspacing[n] = GFC_DESCRIPTOR_SPACING(array,n);
      extent[n] = GFC_DESCRIPTOR_EXTENT(array,n);
      count[n] = 0;
      if (extent[n] <= 0)
	{
	  /* Set the return value.  */
	  for (n = 0; n < rank; n++)
	    GFC_DESCRIPTOR1_ELEM (rtype_name, retarray, n) = 0;
	  return;
	}
    }

  base = array->base_addr;

  /* Initialize the return value.  */
  for (n = 0; n < rank; n++)
    GFC_DESCRIPTOR1_ELEM (rtype_name, retarray, n) = 1;
  {
')dnl
define(START_FOREACH_BLOCK,
`  while (base)
    {
	  /* Implementation start.  */
')dnl
define(FINISH_FOREACH_FUNCTION,
`	  /* Implementation end.  */
	  /* Advance to the next element.  */
	  base = (atype_name *) (((char*)base) + sspacing[0]);
	}
      while (++count[0] != extent[0]);
      n = 0;
      do
	{
	  /* When we get to the end of a dimension, reset it and increment
	     the next dimension.  */
	  count[n] = 0;
	  /* We could precalculate these products, but this is a less
	     frequently used path so probably not worth it.  */
	  base = (atype_name *) (((char*)base) - sspacing[n] * extent[n]);
	  n++;
	  if (n >= rank)
	    {
	      /* Break out of the loop.  */
	      base = NULL;
	      break;
	    }
	  else
	    {
	      count[n]++;
	      base = (atype_name *) (((char*)base) + sspacing[n]);
	    }
	}
      while (count[n] == extent[n]);
    }
  }
}')dnl
define(START_MASKED_FOREACH_FUNCTION,
`
extern void `m'name`'rtype_qual`_'atype_code (rtype * const restrict, 
	atype * const restrict, gfc_array_l1 * const restrict,
	GFC_LOGICAL_4);
export_proto(`m'name`'rtype_qual`_'atype_code);

void
`m'name`'rtype_qual`_'atype_code (rtype * const restrict retarray, 
	atype * const restrict array,
	gfc_array_l1 * const restrict mask, GFC_LOGICAL_4 back)
{
  index_type count[GFC_MAX_DIMENSIONS];
  index_type extent[GFC_MAX_DIMENSIONS];
  index_type sspacing[GFC_MAX_DIMENSIONS];
  index_type mspacing[GFC_MAX_DIMENSIONS];
  index_type dspacing;
  rtype_name *dest;
  const atype_name *base;
  GFC_LOGICAL_1 *mbase;
  int rank;
  index_type n;
  int mask_kind;


  if (mask == NULL)
    {
      name`'rtype_qual`_'atype_code (retarray, array, back);
      return;
    }

  rank = GFC_DESCRIPTOR_RANK (array);
  if (rank <= 0)
    runtime_error ("Rank of array needs to be > 0");

  if (retarray->base_addr == NULL)
    {
      GFC_DESCRIPTOR_DIMENSION_SET(retarray, 0, 0, rank - 1, sizeof (rtype_name));
      retarray->dtype.rank = 1;
      retarray->offset = 0;
      retarray->base_addr = xmallocarray (rank, sizeof (rtype_name));
    }
  else
    {
      if (unlikely (compile_options.bounds_check))
	{

	  bounds_iforeach_return ((array_t *) retarray, (array_t *) array,
				  "u_name");
	  bounds_equal_extents ((array_t *) mask, (array_t *) array,
				  "MASK argument", "u_name");
	}
    }

  mask_kind = GFC_DESCRIPTOR_SIZE (mask);

  mbase = mask->base_addr;

  if (mask_kind == 1 || mask_kind == 2 || mask_kind == 4 || mask_kind == 8
#ifdef HAVE_GFC_LOGICAL_16
      || mask_kind == 16
#endif
      )
    mbase = GFOR_POINTER_TO_L1 (mbase, mask_kind);
  else
    runtime_error ("Funny sized logical array");

  dspacing = GFC_DESCRIPTOR_SPACING(retarray,0);
  dest = retarray->base_addr;
  for (n = 0; n < rank; n++)
    {
      sspacing[n] = GFC_DESCRIPTOR_SPACING(array,n);
      mspacing[n] = GFC_DESCRIPTOR_SPACING(mask,n);
      extent[n] = GFC_DESCRIPTOR_EXTENT(array,n);
      count[n] = 0;
      if (extent[n] <= 0)
	{
	  /* Set the return value.  */
	  for (n = 0; n < rank; n++)
	    GFC_DESCRIPTOR1_ELEM (rtype_name, retarray, n) = 0;
	  return;
	}
    }

  base = array->base_addr;

  /* Initialize the return value.  */
  for (n = 0; n < rank; n++)
    GFC_DESCRIPTOR1_ELEM (rtype_name, retarray, n) = 0;
  {
')dnl
define(START_MASKED_FOREACH_BLOCK, `START_FOREACH_BLOCK')dnl
define(FINISH_MASKED_FOREACH_FUNCTION,
`	  /* Implementation end.  */
	  /* Advance to the next element.  */
	  base = (atype_name*) (((char*)base) + sspacing[0]);
	  mbase += mspacing[0];
	}
      while (++count[0] != extent[0]);
      n = 0;
      do
	{
	  /* When we get to the end of a dimension, reset it and increment
	     the next dimension.  */
	  count[n] = 0;
	  /* We could precalculate these products, but this is a less
	     frequently used path so probably not worth it.  */
	  base = (atype_name*) (((char*)base) - sspacing[n] * extent[n]);
	  mbase -= mspacing[n] * extent[n];
	  n++;
	  if (n >= rank)
	    {
	      /* Break out of the loop.  */
	      base = NULL;
	      break;
	    }
	  else
	    {
	      count[n]++;
	      base = (atype_name*) (((char*)base) + sspacing[n]);
	      mbase += mspacing[n];
	    }
	}
      while (count[n] == extent[n]);
    }
  }
}')dnl
define(FOREACH_FUNCTION,
`START_FOREACH_FUNCTION
$1
START_FOREACH_BLOCK
$2
FINISH_FOREACH_FUNCTION')dnl
define(MASKED_FOREACH_FUNCTION,
`START_MASKED_FOREACH_FUNCTION
$1
START_MASKED_FOREACH_BLOCK
$2
FINISH_MASKED_FOREACH_FUNCTION')dnl
define(SCALAR_FOREACH_FUNCTION,
`
extern void `s'name`'rtype_qual`_'atype_code (rtype * const restrict, 
	atype * const restrict, GFC_LOGICAL_4 *, GFC_LOGICAL_4);
export_proto(`s'name`'rtype_qual`_'atype_code);

void
`s'name`'rtype_qual`_'atype_code (rtype * const restrict retarray, 
	atype * const restrict array,
	GFC_LOGICAL_4 * mask, GFC_LOGICAL_4 back)
{
  index_type rank;
  index_type dspacing;
  index_type n;
  rtype_name *dest;

  if (mask == NULL || *mask)
    {
      name`'rtype_qual`_'atype_code (retarray, array, back);
      return;
    }

  rank = GFC_DESCRIPTOR_RANK (array);

  if (rank <= 0)
    runtime_error ("Rank of array needs to be > 0");

  if (retarray->base_addr == NULL)
    {
      GFC_DESCRIPTOR_DIMENSION_SET(retarray, 0, 0, rank-1, sizeof(rtype_name));
      retarray->dtype.rank = 1;
      retarray->offset = 0;
      retarray->base_addr = xmallocarray (rank, sizeof (rtype_name));
    }
  else if (unlikely (compile_options.bounds_check))
    {
       bounds_iforeach_return ((array_t *) retarray, (array_t *) array,
			       "u_name");
    }

  dspacing = GFC_DESCRIPTOR_SPACING(retarray,0);
  dest = retarray->base_addr;
  for (n = 0; n<rank; n++)
    GFC_DESCRIPTOR1_ELEM (rtype_name, retarray, n) = $1 ;
}')dnl
