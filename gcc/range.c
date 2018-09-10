/* SSA range analysis implementation. -*- C++ -*-
   Copyright (C) 2017 Free Software Foundation, Inc.
   Contributed by Aldy Hernandez <aldyh@redhat.com>.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "tree.h"
#include "gimple.h"
#include "gimple-pretty-print.h"
#include "fold-const.h"
#include "ssa.h"
#include "range.h"
#include "selftest.h"
#include "wide-int-range.h"

static bool
range_compatible_p (tree t1, tree t2)
{
  if (POINTER_TYPE_P (t1) && POINTER_TYPE_P (t2))
    return true;

  // FORTRAN has different precision booleans that trigger a false
  // from types_compatible_p.
  if (TREE_CODE (t1) == BOOLEAN_TYPE && TREE_CODE (t2) == BOOLEAN_TYPE)
      return true;

  return types_compatible_p (t1, t2);
}

/* Subtract 1 from X and set OVERFLOW if the operation overflows.  */

static wide_int inline
subtract_one (const wide_int &x, tree type, wi::overflow_type &overflow)
{
  /* A signed 1-bit bit-field, has a range of [-1,0] so subtracting +1
     overflows, since +1 is unrepresentable.  This is why we have an
     addition of -1 here.  */
  if (TYPE_SIGN (type) == SIGNED)
    return wi::add (x, -1 , SIGNED, &overflow);
  else
    return wi::sub (x, 1, UNSIGNED, &overflow);
}

/* Set range from a TYPE and some bounds (LBOUND and UBOUND).

   RT is PLAIN if it is a normal range, or INVERSE if it is an inverse
   range.  */

void
irange::set_range (tree typ, const wide_int &lbound,
		   const wide_int &ubound, kind rt)
{
  gcc_assert (INTEGRAL_TYPE_P (typ) || POINTER_TYPE_P (typ));
  gcc_assert (TYPE_PRECISION (typ) == lbound.get_precision ());
  gcc_assert (lbound.get_precision () == ubound.get_precision ());
  overflow = false;
  type = typ;
  gcc_assert (wi::le_p (lbound, ubound, TYPE_SIGN (type)));
  if (rt == INVERSE)
    {
      /* We calculate INVERSE([I,J]) as [-MIN, I-1][J+1, +MAX].  */
      wi::overflow_type ovf;
      nitems = 0;
      wide_int min = wi::min_value (TYPE_PRECISION (type), TYPE_SIGN (type));
      wide_int max = wi::max_value (TYPE_PRECISION (type), TYPE_SIGN (type));

      /* If we will overflow, don't bother.  This will handle unsigned
	 underflow which doesn't set the overflow bit.

	 Note: Perhaps all these &ovf checks are unecessary since we
	 are manually checking for overflow with the if() below.  */
      if (lbound != min)
	{
	  bounds[nitems++] = min;
	  bounds[nitems++] = subtract_one (lbound, type, ovf);
	  if (ovf)
	    nitems = 0;
	}
      /* If we will overflow, don't bother.  This will handle unsigned
	 overflow which doesn't set the overflow bit.  */
      if (ubound != max)
	{
	  bounds[nitems++] = wi::add (ubound, 1, TYPE_SIGN (type), &ovf);
	  if (ovf)
	    nitems--;
	  else
	    bounds[nitems++] = max;
	}

      /* If we get here with N==0, it means we tried to calculate the
	 inverse of [-MIN, +MAX] which is actually the empty set, and
	 N==0 maps nicely to the empty set :).  */
    }
  else
    {
      nitems = 2;
      bounds[0] = lbound;
      bounds[1] = ubound;
    }
  gcc_assert (!CHECKING_P || valid_p ());
}

/* Set range from type T and integer bounds X, Y.

   RT is PLAIN if it is a normal range, or INVERSE if it is an inverse
   range.  */

void
irange::set_range (tree t, int x, int y, kind rt)
{
  int precision = TYPE_PRECISION (t);
  wide_int xi, yi;
  if (TYPE_UNSIGNED (t))
    {
      xi = wi::uhwi (x, precision);
      yi = wi::uhwi (y, precision);
    }
  else
    {
      xi = wi::shwi (x, precision);
      yi = wi::shwi (y, precision);
    }
  set_range (t, xi, yi, rt);
}

// Set range from an IRANGE_STORAGE and TYPE.

void
irange::set_range (const irange_storage *storage, tree typ)
{
  overflow = false;
  type = typ;
  nitems = 0;
  unsigned i = 0;
  unsigned precision = wi::get_precision (storage->trailing_bounds[0]);
  gcc_assert (precision == TYPE_PRECISION (typ));
  while (i < max_pairs * 2)
    {
      wide_int lo = storage->trailing_bounds[i];
      wide_int hi = storage->trailing_bounds[i + 1];
      // A nonsensical sub-range of [1,0] marks the end of valid ranges.
      if (lo == wi::one (precision) && hi == wi::zero (precision))
	break;
      bounds[i] = lo;
      bounds[i + 1] = hi;
      i += 2;
    }
  nitems = i;
  gcc_assert (!CHECKING_P || valid_p ());
}

/* Set range from an SSA_NAME's available range.  If there is no
   available range, build a range for its entire domain.  */

void
irange::set_range (tree ssa)
{
  tree t = TREE_TYPE (ssa);
  gcc_assert (INTEGRAL_TYPE_P (t) || POINTER_TYPE_P (t));
  if (!SSA_NAME_RANGE_INFO (ssa) || POINTER_TYPE_P (t))
    {
      set_range_for_type (t);
      return;
    }
  wide_int min, max;
  enum value_range_type kind = get_range_info (ssa, &min, &max);
  value_range_to_irange (*this, t, kind, min, max);
//  irange_storage *storage = SSA_NAME_RANGE_INFO (ssa);
//  set_range (storage, t);
}

/* Set range from the full domain of type T.  */

void
irange::set_range_for_type (tree t)
{
  gcc_assert (TYPE_P (t));
  gcc_assert (INTEGRAL_TYPE_P (t) || POINTER_TYPE_P (t));
  wide_int min = wi::min_value (TYPE_PRECISION (t), TYPE_SIGN (t));
  wide_int max = wi::max_value (TYPE_PRECISION (t), TYPE_SIGN (t));
  set_range (t, min, max);
}

irange::irange (const irange &r)
{
  type = r.type;
  overflow = false;
  nitems = r.nitems;
  for (unsigned i = 0; i < nitems; ++i)
    bounds[i] = r.bounds[i];
  gcc_assert (!CHECKING_P || valid_p ());
}

bool
irange::operator== (const irange &r) const
{
  if (!range_compatible_p (type, r.type)
      || nitems != r.nitems || overflow != r.overflow)
    return false;
  for (unsigned i = 0; i < nitems; ++i)
    if (!wi::eq_p (bounds[i], r.bounds[i]))
      return false;
  return true;
}

irange&
irange::operator= (const irange &r)
{
  type = r.type;
  nitems = r.nitems;
  overflow = r.overflow;
  for (unsigned i = 0; i < nitems; ++i)
    bounds[i] = r.bounds[i];
  return *this;
}


irange&
irange::operator= (tree t)
{
  set_range (t);
  return *this;
}

// Return true if this range is the full range for it's type

bool
irange::range_for_type_p () const
{
  irange tmp;
  tmp.set_range_for_type (type);
  /* Clear the overflow bit so two [MIN,MAX] ranges will compare
     correctly with and without overflow.  */
  tmp.overflow = overflow;
  return (*this == tmp);
}


bool
irange::valid_p () const
{
  if (type == NULL_TREE
      || nitems % 2
      || nitems > max_pairs * 2)
    return false;

  /* An empty range is valid, as long as it has a type.  */
  if (!nitems)
    return true;

  /* Check that the bounds are in the right order.

     So for [a,b][c,d][e,f] we must have:
     a <= b < c <= d < e <= f.  */
  if (wi::gt_p (bounds[0], bounds[1], TYPE_SIGN (type)))
    return false;
  for (unsigned i = 2; i < nitems; i += 2)
    {
      if (wi::le_p (bounds[i], bounds[i-1], TYPE_SIGN (type)))
	return false;
      if (wi::gt_p (bounds[i], bounds[i+1], TYPE_SIGN (type)))
	return false;
    }
  return true;
}

/* Convert the current range in place into a range of type NEW_TYPE.  */

void
irange::cast (tree new_type)
{
  /* If nothing changed, this is a simple type conversion between two
     variants of the same type.  */
  bool sign_change = TYPE_SIGN (new_type) != TYPE_SIGN (type);
  unsigned old_precision = TYPE_PRECISION (type);
  unsigned new_precision = TYPE_PRECISION (new_type);
  signop old_sign = TYPE_SIGN (type);
  signop new_sign = TYPE_SIGN (new_type);
  if (!nitems
      || (!sign_change && old_precision == new_precision))
    {
      type = new_type;
      return;
    }

  /* If the entire range doesn't fit in the new range type, bail.  */
  wide_int orig_lowest = lower_bound ();
  wide_int orig_highest = upper_bound ();
  wide_int tmp1, tmp2;
  if (!wide_int_range_convert (tmp1, tmp2,
			       old_sign, old_precision,
			       new_sign, new_precision,
			       orig_lowest, orig_highest))
    {
      bounds[0] = wi::min_value (new_precision, new_sign);
      bounds[1] = wi::max_value (new_precision, new_sign);
      type = new_type;
      nitems = 2;
      return;
    }

  wide_int new_type_min = wi::min_value (new_precision, new_sign);
  wide_int new_type_max = wi::max_value (new_precision, new_sign);
  for (unsigned i = 0; i < nitems; i += 2)
    {
      /* If the new bounds are in the right order, we can do a
	 straight up conversion.  */
      wide_int new_min = wide_int::from (bounds[i], new_precision, old_sign);
      wide_int new_max = wide_int::from (bounds[i + 1], new_precision, old_sign);
      if (wi::le_p (new_min, new_max, new_sign))
	{
	  bounds[i] = new_min;
	  bounds[i + 1] = new_max;
	}
      /* Otherwise, the bounds have wrapped and we must handle them
	 specially as [-MIN,Y][X,MAX].  */
      else
	{
	  /* If we're about to go over the maximum number of ranges,
	     convert to something conservative and cast again.  */
	  if (nitems >= max_pairs * 2)
	    {
	      bounds[0] = orig_lowest;
	      bounds[1] = orig_highest;
	      nitems = 2;
	      cast (new_type);
	      return;
	    }
	  /* Handle wrapping of [X,Y] as [-MIN,Y][X,MAX].  */
	  bounds[i] = new_type_min;
	  bounds[i + 1] = new_max;
	  /* If we're about to construct [-MIN, MAX], no sense
	     calculating anything else.  */
	  if (bounds[i + 1] == new_type_max)
	    {
	      bounds[0] = new_type_min;
	      bounds[1] = new_type_max;
	      nitems = 2;
	      type = new_type;
	      return;
	    }
	  bounds[nitems++] = new_min;
	  bounds[nitems++] = new_type_max;
	}
    }
  type = new_type;
  canonicalize ();
}

// Return TRUE if the current range contains ELEMENT.

bool
irange::contains_p (const wide_int &element) const
{
  for (unsigned i = 0; i < nitems; i += 2)
    if (wi::ge_p (element, bounds[i], TYPE_SIGN (type))
	&& wi::le_p (element, bounds[i + 1], TYPE_SIGN (type)))
      return true;
  return false;
}

// Like above, but ELEMENT can be an INTEGER_CST of any type.

bool
irange::contains_p (tree element) const
{
  gcc_assert (INTEGRAL_TYPE_P (TREE_TYPE (element)));
  tree t = fold_convert (type, element);
  if (TREE_OVERFLOW (t))
    return false;
  wide_int wi = wi::to_wide (t);
  return contains_p (wi);
}

// Like above, but element is an int.

bool
irange::contains_p (int element) const
{
  if (TYPE_UNSIGNED (type))
    return contains_p (wi::uhwi (element, TYPE_PRECISION (type)));
  else
    return contains_p (wi::shwi (element, TYPE_PRECISION (type)));
}

// Canonicalize the current range.

void
irange::canonicalize ()
{
  if (nitems < 2)
    return;

  /* Fix any out of order ranges: [10,20][-5,5] into [-5,5][10,20].  */
  for (unsigned i = 0; i < (unsigned) nitems; i += 2)
    for (unsigned j = i + 2; j < (unsigned) nitems; j += 2)
      if (wi::gt_p (bounds[i], bounds[j], TYPE_SIGN (type)))
	{
	  wide_int t1 = bounds[i];
	  wide_int t2 = bounds[i + 1];
	  bounds[i] = bounds[j];
	  bounds[i + 1] = bounds[j + 1];
	  bounds[j] = t1;
	  bounds[j + 1] = t2;
	}

  /* Merge any edges that touch.
     [9,10][11,20] => [9,20].  */
  for (unsigned i = 1; i < (unsigned) (nitems - 2); i += 2)
    {
      wi::overflow_type ovf;
      wide_int x = wi::add (bounds[i], 1, TYPE_SIGN (type), &ovf);
      /* No need to check for overflow here for the +1, since the
	 middle ranges cannot have MAXINT.  */
      if (x == bounds[i + 1])
	{
	  bounds[i] = bounds[i + 2];
	  remove (i + 1, i + 2);
	}
    }
  gcc_assert (!CHECKING_P || valid_p ());
}

// Remove the bound entries from [i..j].

void
irange::remove (unsigned i, unsigned j)
{
  gcc_assert (i < nitems && i < j);
  unsigned dst = i;
  unsigned ndeleted = j - i + 1;
  for (++j; j < nitems; ++j)
    bounds[dst++] = bounds[j];
  nitems -= ndeleted;
}

// THIS = THIS U [X,Y]

irange &
irange::union_ (const wide_int &x, const wide_int &y)
{
  if (empty_p ())
    {
      bounds[0] = x;
      bounds[1] = y;
      nitems = 2;
      gcc_assert (!CHECKING_P || valid_p ());
      return *this;
    }
  irange tmp (type, x, y);
  return union_ (tmp);
}

// THIS = THIS U R

irange &
irange::union_ (const irange &r)
{
  gcc_assert (range_compatible_p (type, r.type));

  if (empty_p ())
    {
      *this = r;
      return *this;
    }
  else if (r.empty_p ())
    return *this;

  // Build a union of 2 ranges here.  Make sure we dont have to worry about
  // merging and such by reserving twice as many pairs as needed, and simply
  // sort the 2 ranges into this intermediate form.
  // The intermediate result will have the property that the beginning of
  // each range is <= the beginning of the next range
  // There may be overlapping ranges at this point.
  // ie this would be valid 
  // 	[ -20, 10], [-10, 0], [0, 20], [40, 90] 
  // as it satisfies this contraint : -20 < -10 < 0 < 40
  // When the range is rebuilt into r, the merge is performed.
  //
  // [Xi,Yi]..[Xn,Yn]  U  [Xj,Yj]..[Xm,Ym]   -->  [Xk,Yk]..[Xp,Yp]

  signop sign = TYPE_SIGN (type);
  wide_int res[max_pairs * 4];
  wide_int u1 ;
  wi::overflow_type ovf;
  unsigned i = 0, j = 0, k = 0;

  while (i < nitems && j < r.nitems)
    {
      // lower of Xi and Xj is the lowest point.
      if (wi::le_p (bounds[i], r.bounds[j], sign))
        {
	  res[k++] = bounds[i];
	  res[k++] = bounds[i + 1];
	  i += 2;
	}
      else
        {
	  res[k++] = r.bounds[j];
	  res[k++] = r.bounds[j + 1];
	  j += 2;
	}
    }

  for ( ; i < nitems; i += 2)
    {
      res[k++] = bounds[i];
      res[k++] = bounds[i + 1];
    }

  for ( ; j < r.nitems; j += 2)
    {
      res[k++] = r.bounds[j];
      res[k++] = r.bounds[j + 1];
    }

  // Now normalize the vector removing any overlaps.
  
  i = 2;
  int prec = TYPE_PRECISION (type);
  wide_int max_val = wi::max_value (prec, sign);
  for (j = 2; j < k ; j += 2)
    {
      if (res[i - 1] == max_val)
        break;
      u1 = wi::add (res[i - 1], 1, sign, &ovf);

      // Overflow indicates we are at MAX already
      // wide int bug requires the previous max_val check
      // trigger: gcc.c-torture/compile/pr80443.c  with -O3
      if (ovf)
        break;

      // Current upper+1 is >= lower bound next pair, then we merge ranges.
      if (wi::ge_p (u1, res[j], sign))
        {
	  // New upper bounds is greater of current or the next one.
	  if (wi::gt_p (res[j + 1], res [i - 1], sign))
	    res [i - 1] = res[j + 1];
	}
      else
        {
	  // this is a new distinct range, but no point in copying it if its
	  // in the right place.
	  if (i != j)
	    {
	      res[i++] = res[j];
	      res[i++] = res[j + 1];
	    }
	  else
	    i += 2;

	}
    }
  
  // At This point, the vector should have i ranges, none overlapping. Now
  // it simply needs to be copied, and if there are too many ranges,
  // merge some.  WE wont do any analysis as to what the "best" merges are,
  // simply combine the final ranges into one.
  if (i > max_pairs * 2)
    {
      res[max_pairs * 2 - 1] = res[i - 1];
      i = max_pairs * 2;
    }

  for (j = 0; j < i ; j++)
    bounds[j] = res [j];
  nitems = i;
    
  overflow |= r.overflow;

  gcc_assert (!CHECKING_P || valid_p ());
  return *this;
}

// Intersect this range with a bitmask MASK.
// Based on the bits in the mask, each lower bound is rounded up and each
// upper bounds is rounded down.
void
irange::intersect_mask (const wide_int& mask)
{
  signop sign = TYPE_SIGN (type);
  unsigned pos = 0;
  
  // Remove zero from the current range.
  //
  // seems to be a bug., I can't specify:
  //
  //   irange nz (type, 0, 0, INVERSE);
  irange nz (type, 0 ,0);
  nz.invert ();

  intersect (nz);

  for (unsigned i = 0; i < nitems; i += 2)
    {
      wide_int ub = wi::round_down_for_mask (bounds[i + 1], mask);
      // Have to check for ub > lb immediately due to signed values
      // potentially wrapping.  skip if not a valid range.
      if (wi::gt_p (bounds[i], ub, sign))
        continue;
      wide_int lb = wi::round_up_for_mask (bounds[i], mask);

      // If this is not a valid range, skip it
      if (wi::gt_p (lb, ub, sign))
        continue;
      bounds[pos++] = lb;
      bounds[pos++] = ub ;
    }
  nitems = pos;

  // 0 is always a possible result, even if it wasn't in the original range.
  union_ (irange (type, 0 , 0));
}

// THIS = THIS ^ [X,Y].

irange &
irange::intersect (const wide_int &x, const wide_int &y)
{
  unsigned pos = 0;

  for (unsigned i = 0; i < nitems; i += 2)
    {
      wide_int newlo = wi::max (bounds[i], x, TYPE_SIGN (type));
      wide_int newhi = wi::min (bounds[i + 1], y, TYPE_SIGN (type));
      if (wi::gt_p (newlo, newhi, TYPE_SIGN (type)))
	{
	  /* If the new sub-range doesn't make sense, it's an
	     impossible range and must be kept out of the result.  */
	}
      else
	{
	  bounds[pos++] = newlo;
	  bounds[pos++] = newhi;
	}
    }
  nitems = pos;
  gcc_assert (!CHECKING_P || valid_p ());
  return *this;
}

// THIS = THIS ^ R.

irange &
irange::intersect (const irange &r)
{
  gcc_assert (range_compatible_p (type, r.type));
  irange orig_range (*this);

  /* Intersection with an empty range is an empty range.  */
  clear ();
  if (orig_range.empty_p () || r.empty_p ())
    return *this;

  /* The general algorithm is as follows.

     Intersect each sub-range of R with all of ORIG_RANGE one at a time, and
     join/union the results of these intersections together.  I.e:

     [10,20][30,40][50,60] ^ [15,25][38,51][55,70]

     Step 1: [10,20][30,40][50,60] ^ [15,25] => [15,20]
     Step 2: [10,20][30,40][50,60] ^ [38,51] => [38,40]
     Step 3: [10,20][30,40][50,60] ^ [55,70] => [55,60]
     Final:  [15,20] U [38,40] U [55,60] => [15,20][38,40][55,60]

     ?? We should probably stop making a copy of ORIG_RANGE at every step.  */
  for (unsigned i = 0; i < r.nitems; i += 2)
    union_ (irange (orig_range).intersect (r.bounds[i], r.bounds[i + 1]));

  /* Overflow is sticky only if both ranges overflowed.  */
  overflow = (orig_range.overflow && r.overflow);
  /* There is no valid_p() check here because the calls to union_
     above would have called valid_p().  */
  return *this;
}

// Set THIS to the inverse of its range.

irange &
irange::invert ()
{
  /* We always need one more set of bounds to represent an inverse, so
     if we're at the limit, we can't properly represent things.

     For instance, to represent the inverse of a 2 sub-range set
     [5, 10][20, 30], we would need a 3 sub-range set
     [-MIN, 4][11, 19][31, MAX].

     In this case, return the most conservative thing.

     However, if any of the extremes of the range are -MIN/+MAX, we
     know we will not need an extra bound.  For example:

	INVERT([-MIN,20][30,40]) => [21,29][41,+MAX]
	INVERT([-MIN,20][30,MAX]) => [21,29]
  */
  wide_int min = wi::min_value (TYPE_PRECISION (type), TYPE_SIGN (type));
  wide_int max = wi::max_value (TYPE_PRECISION (type), TYPE_SIGN (type));
  if (nitems == max_pairs * 2
      && bounds[0] != min
      && bounds[nitems] != max)
    {
      bounds[1] = max;
      nitems = 2;
      return *this;
    }

  /* The inverse of the empty set is the entire domain.  */
  if (empty_p ())
    {
      set_range_for_type (type);
      return *this;
    }

  /* The algorithm is as follows.  To calculate INVERT ([a,b][c,d]), we
     generate [-MIN, a-1][b+1, c-1][d+1, MAX].

     If there is an over/underflow in the calculation for any
     sub-range, we eliminate that subrange.  This allows us to easily
     calculate INVERT([-MIN, 5]) with: [-MIN, -MIN-1][6, MAX].  And since
     we eliminate the underflow, only [6, MAX] remains.  */

  unsigned i = 0;
  wi::overflow_type ovf;

  /* Construct leftmost range.  */
  irange orig_range (*this);
  nitems = 0;
  /* If this is going to underflow on the MINUS 1, don't even bother
     checking.  This also handles subtracting one from an unsigned 0,
     which doesn't set the underflow bit.  */
  if (min != orig_range.bounds[i])
    {
      bounds[nitems++] = min;
      bounds[nitems++] = subtract_one (orig_range.bounds[i], type, ovf);
      if (ovf)
	nitems = 0;
    }
  i++;
  /* Construct middle ranges if applicable.  */
  if (orig_range.nitems > 2)
    {
      unsigned j = i;
      for (; j < (unsigned) (orig_range.nitems - 2); j += 2)
	{
	  /* The middle ranges cannot have MAX/MIN, so there's no need
	     to check for unsigned overflow on the +1 and -1 here.  */
	  bounds[nitems++]
	    = wi::add (orig_range.bounds[j], 1, TYPE_SIGN (type), &ovf);
	  bounds[nitems++]
	    = subtract_one (orig_range.bounds[j + 1], type, ovf);
	  if (ovf)
	    nitems -= 2;
	}
      i = j;
    }
  /* Construct rightmost range.

     However, if this will overflow on the PLUS 1, don't even bother.
     This also handles adding one to an unsigned MAX, which doesn't
     set the overflow bit.  */
  if (max != orig_range.bounds[i])
    {
      bounds[nitems++]
	= wi::add (orig_range.bounds[i], 1, TYPE_SIGN (type), &ovf);
      bounds[nitems++] = max;
      if (ovf)
	nitems -= 2;
    }

  gcc_assert (!CHECKING_P || valid_p ());
  return *this;
}

/* Returns the upper bound of PAIR.  */

wide_int
irange::upper_bound (unsigned pair) const
{
  gcc_assert (nitems != 0 && pair <= num_pairs ());
  return bounds[pair * 2 + 1];
}

/* Dump the current range onto BUFFER.  */

void
irange::dump (pretty_printer *buffer) const
{
  if (POINTER_TYPE_P (type) && non_zero_p ())
    pp_string (buffer, "[ non-zero pointer ]");
  else
    for (unsigned i = 0; i < nitems; ++i)
      {
	if (i % 2 == 0)
	  pp_character (buffer, '[');

	/* Wide ints may be sign extended to the full extent of the
	   underlying HWI storage, even if the precision we care about
	   is smaller.  Chop off the excess bits for prettier output.  */
	signop sign = TYPE_UNSIGNED (type) ? UNSIGNED : SIGNED;
	widest_int val = widest_int::from (bounds[i], sign);
	val &= wi::mask<widest_int> (bounds[i].get_precision (), false);

	if (val > 0xffff)
	  print_hex (val, pp_buffer (buffer)->digit_buffer);
	else
	  print_dec (bounds[i], pp_buffer (buffer)->digit_buffer, sign);
	pp_string (buffer, pp_buffer (buffer)->digit_buffer);
	if (i % 2 == 0)
	  pp_string (buffer, ", ");
	else
	  pp_character (buffer, ']');
      }
  if (!nitems)
    pp_string (buffer, "[]");

  pp_character (buffer, ' ');
  dump_generic_node (buffer, type, 0, TDF_NONE, false);
  if (overflow)
    pp_string (buffer, " (overflow)");
  pp_newline_and_flush (buffer);
}

/* Dump the current range onto FILE F.  */

void
irange::dump (FILE *f) const
{
  pretty_printer buffer;
  buffer.buffer->stream = f;
  dump (&buffer);
}

/* Like above but dump to STDERR.

   ?? You'd think we could have a default parameter for dump(FILE),
   but gdb currently doesn't do default parameters gracefully-- or at
   all, and since this is a function we need to be callable from the
   debugger... */

void
irange::dump () const
{
  dump (stderr);
}

/* Initialize the current irange_storage to the irange in IR.  */

void
irange_storage::set_irange (const irange &ir)
{
  unsigned precision = TYPE_PRECISION (ir.get_type ());
  trailing_bounds.set_precision (precision);
  unsigned i;
  for (i = 0; i < ir.num_pairs () * 2; ++i)
    trailing_bounds[i] = ir.bounds[i];

  /* Build nonsensical [1,0] pairs for the remaining empty ranges.
     These will be recognized as empty when we read the structure
     back.  */
  for (; i < irange::max_pairs * 2; i += 2)
    {
      trailing_bounds[i] = wi::one (precision);
      trailing_bounds[i + 1] = wi::zero (precision);
    }
}

bool
make_irange (irange *result, tree lb, tree ub, tree type)
{
  irange r (TREE_TYPE (lb), lb, ub);
  *result = r;
  if (result->valid_p () && !result->empty_p ())
    {
      if (type)
        result->cast (type);
      return true;
    }
  return false;
}

bool
make_irange_not (irange *result, tree not_exp, tree type)
{
  irange r (TREE_TYPE (not_exp), not_exp, not_exp, irange::INVERSE);
  *result = r;
  if (result->valid_p () && !result->empty_p ())
    {
      if (type)
        result->cast (type);
      return true;
    }
  return false;
}

void
range_one (irange *r, tree type)
{
  tree one = build_int_cst (type, 1);
  r->set_range (type, one, one);
}

void
range_zero (irange *r, tree type)
{
  tree zero = build_int_cst (type, 0);
  r->set_range (type, zero, zero);
}

bool
range_non_zero (irange *r, tree type)
{
  tree zero = build_int_cst (type, 0);
  return make_irange_not (r, zero, type);
}

/* Convert irange  to a value_range_type.  */

void
irange_to_value_range (value_range &vr, const irange &r)
{
  vr.equiv = NULL;
  if (r.range_for_type_p ())
    {
      vr.type = VR_VARYING;
      vr.min = vr.max = NULL_TREE;
      return;
    }
  tree type = r.get_type ();
  unsigned int precision = TYPE_PRECISION (type);
  if (r.num_pairs () == 2
      && r.lower_bound () == wi::min_value (precision, TYPE_SIGN (type))
      && r.upper_bound () == wi::max_value (precision, TYPE_SIGN (type)))
    {
      irange tmp = irange_invert (r);
      vr.min = wide_int_to_tree (type, tmp.lower_bound ());
      vr.max = wide_int_to_tree (type, tmp.upper_bound ());
      vr.type = VR_ANTI_RANGE;
    }
  else
    {
      vr.min = wide_int_to_tree (type, r.lower_bound ());
      vr.max = wide_int_to_tree (type, r.upper_bound ());
      vr.type = VR_RANGE;
    }
}

#ifdef CHECKING_P
namespace selftest {


#define INT(N) build_int_cst (integer_type_node, (N))
#define UINT(N) build_int_cstu (unsigned_type_node, (N))
#define INT16(N) build_int_cst (short_integer_type_node, (N))
#define UINT16(N) build_int_cstu (short_unsigned_type_node, (N))
#define INT64(N) build_int_cstu (long_long_integer_type_node, (N))
#define UINT64(N) build_int_cstu (long_long_unsigned_type_node, (N))
#define UINT128(N) build_int_cstu (u128_type, (N))
#define UCHAR(N) build_int_cstu (unsigned_char_type_node, (N))
#define SCHAR(N) build_int_cst (signed_char_type_node, (N))

#define RANGE3(A,B,C,D,E,F) 				\
( i1 = irange (integer_type_node, INT (A), INT (B)),	\
  i2 = irange (integer_type_node, INT (C), INT (D)),	\
  i3 = irange (integer_type_node, INT (E), INT (F)),	\
  i1.union_ (i2),					\
  i1.union_ (i3),					\
  i1 )

// Run all of the selftests within this file.

void
irange_tests ()
{
  tree u128_type = build_nonstandard_integer_type (128, /*unsigned=*/1);
  irange i1, i2, i3;
  irange r0, r1, rold;
  ASSERT_FALSE (r0.valid_p ());

  /* Test that NOT(255) is [0..254] in 8-bit land.  */
  irange not_255;
  make_irange_not (&not_255, UCHAR(255), unsigned_char_type_node);
  ASSERT_TRUE (not_255 == irange (unsigned_char_type_node, 0, 254));

  /* Test that NOT(0) is [1..255] in 8-bit land.  */
  irange not_zero;
  range_non_zero (&not_zero, unsigned_char_type_node);
  ASSERT_TRUE (not_zero == irange (unsigned_char_type_node, 1, 255));

  /* Check that [0,127][0x..ffffff80,0x..ffffff]
     => ~[128, 0x..ffffff7f].  */
  r0 = irange (u128_type, 0, 127);
  tree high = build_minus_one_cst (u128_type);
  /* low = -1 - 127 => 0x..ffffff80.  */
  tree low = fold_build2 (MINUS_EXPR, u128_type, high, UINT128(127));
  r1 = irange (u128_type, low, high); // [0x..ffffff80, 0x..ffffffff]
  /* r0 = [0,127][0x..ffffff80,0x..fffffff].  */
  r0.union_ (r1);
  /* r1 = [128, 0x..ffffff7f].  */
  r1 = irange (u128_type,
	       UINT128(128),
	       fold_build2 (MINUS_EXPR, u128_type,
			    build_minus_one_cst (u128_type),
			    UINT128(128)));
  r0.invert ();
  ASSERT_TRUE (r0 == r1);

  r0.set_range_for_type (integer_type_node);
  tree minint = wide_int_to_tree (integer_type_node, r0.lower_bound ());
  tree maxint = wide_int_to_tree (integer_type_node, r0.upper_bound ());

  r0.set_range_for_type (short_integer_type_node);
  tree minshort = wide_int_to_tree (short_integer_type_node, r0.lower_bound ());
  tree maxshort = wide_int_to_tree (short_integer_type_node, r0.upper_bound ());

  r0.set_range_for_type (unsigned_type_node);
  tree maxuint = wide_int_to_tree (unsigned_type_node, r0.upper_bound ());

  /* Check that ~[0,5] => [6,MAX] for unsigned int.  */
  r0 = irange (unsigned_type_node, 0, 5);
  r0.invert ();
  ASSERT_TRUE (r0 == irange (unsigned_type_node, UINT(6), maxuint));

  /* Check that ~[10,MAX] => [0,9] for unsigned int.  */
  r0 = irange (unsigned_type_node, UINT(10), maxuint, irange::PLAIN);
  r0.invert ();
  ASSERT_TRUE (r0 == irange (unsigned_type_node, 0, 9));

  /* Check that ~[0,5] => [6,MAX] for unsigned 128-bit numbers.  */
  r0.set_range (u128_type, 0, 5, irange::INVERSE);
  r1 = irange (u128_type, UINT128(6), build_minus_one_cst (u128_type));
  ASSERT_TRUE (r0 == r1);

  /* Check that [~5] is really [-MIN,4][6,MAX].  */
  r0.set_range (integer_type_node, 5, 5, irange::INVERSE);
  r1 = irange (integer_type_node, minint, INT(4));
  ASSERT_FALSE (r1.union_ (irange (integer_type_node,
				   INT(6), maxint)).empty_p ());

  ASSERT_TRUE (r0 == r1);

  r1.set_range (integer_type_node, 5, 5);
  ASSERT_TRUE (r1.valid_p ());
  irange r2 (r1);
  ASSERT_TRUE (r1 == r2);

  r1 = irange (integer_type_node, 5, 10);
  ASSERT_TRUE (r1.valid_p ());

  r1 = irange (integer_type_node,
	       wi::to_wide (INT(5)), wi::to_wide (INT(10)));
  ASSERT_TRUE (r1.valid_p ());
  ASSERT_TRUE (r1.contains_p (INT (7)));
  ASSERT_TRUE (r1.contains_p (7));

  r1 = irange (signed_char_type_node, 0, 20);
  ASSERT_TRUE (r1.contains_p (INT(15)));
  ASSERT_FALSE (r1.contains_p (INT(300)));

  /* If a range is in any way outside of the range for the converted
     to range, default to the range for the new type.  */
  r1 = irange (integer_type_node, integer_zero_node, maxint);
  r1.cast (short_integer_type_node);
  ASSERT_TRUE (r1.lower_bound () == wi::to_wide (minshort)
	       && r1.upper_bound() == wi::to_wide (maxshort));

  /* (unsigned char)[-5,-1] => [251,255].  */
  r0 = rold = irange (signed_char_type_node, -5, -1);
  r0.cast (unsigned_char_type_node);
  ASSERT_TRUE (r0 == irange (unsigned_char_type_node, 251, 255));
  r0.cast (signed_char_type_node);
  ASSERT_TRUE (r0 == rold);

  /* (signed char)[15, 150] => [-128,-106][15,127].  */
  r0 = rold = irange (unsigned_char_type_node, 15, 150);
  r0.cast (signed_char_type_node);
  r1 = irange (signed_char_type_node, 15, 127);
  r2 = irange (signed_char_type_node, -128, -106);
  r1.union_ (r2);
  ASSERT_TRUE (r1 == r0);
  r0.cast (unsigned_char_type_node);
  ASSERT_TRUE (r0 == rold);

  /* (unsigned char)[-5, 5] => [0,5][251,255].  */
  r0 = rold = irange (signed_char_type_node, -5, 5);
  r0.cast (unsigned_char_type_node);
  r1 = irange (unsigned_char_type_node, 251, 255);
  r2 = irange (unsigned_char_type_node, 0, 5);
  r1.union_ (r2);
  ASSERT_TRUE (r0 == r1);
  r0.cast (signed_char_type_node);
  ASSERT_TRUE (r0 == rold);

  /* (unsigned char)[-5,5] => [0,5][251,255].  */
  r0 = irange (integer_type_node, -5, 5);
  r0.cast (unsigned_char_type_node);
  r1 = irange (unsigned_char_type_node, 0, 5);
  r1.union_ (irange (unsigned_char_type_node, 251, 255));
  ASSERT_TRUE (r0 == r1);

  /* (unsigned char)[5U,1974U] => [0,255].  */
  r0 = irange (unsigned_type_node, 5, 1974);
  r0.cast (unsigned_char_type_node);
  ASSERT_TRUE (r0 == irange (unsigned_char_type_node, 0, 255));
  r0.cast (integer_type_node);
  /* Going to a wider range should not sign extend.  */
  ASSERT_TRUE (r0 == irange (integer_type_node, 0, 255));

  /* (unsigned char)[-350,15] => [0,255].  */
  r0 = irange (integer_type_node, -350, 15);
  r0.cast (unsigned_char_type_node);
  ASSERT_TRUE (r0 == irange (unsigned_char_type_node,
			     TYPE_MIN_VALUE (unsigned_char_type_node),
			     TYPE_MAX_VALUE (unsigned_char_type_node)));

  /* Casting [-120,20] from signed char to unsigned short.
     => [0, 20][0xff88, 0xffff].  */
  r0 = irange (signed_char_type_node, -120, 20);
  r0.cast (short_unsigned_type_node);
  r1 = irange (short_unsigned_type_node, 0, 20);
  r2 = irange (short_unsigned_type_node, 0xff88, 0xffff);
  r1.union_ (r2);
  ASSERT_TRUE (r0 == r1);
  /* Casting back to signed char (a smaller type), would be outside of
     the range, we it'll be the entire range of the signed char.  */
  r0.cast (signed_char_type_node);
  ASSERT_TRUE (r0 == irange (signed_char_type_node,
			     TYPE_MIN_VALUE (signed_char_type_node),
			     TYPE_MAX_VALUE (signed_char_type_node)));

  /* unsigned char -> signed short
	(signed short)[(unsigned char)25, (unsigned char)250]
     => [(signed short)25, (signed short)250].  */
  r0 = rold = irange (unsigned_char_type_node, 25, 250);
  r0.cast (short_integer_type_node);
  r1 = irange (short_integer_type_node, 25, 250);
  ASSERT_TRUE (r0 == r1);
  r0.cast (unsigned_char_type_node);
  ASSERT_TRUE (r0 == rold);

  /* Test casting a wider signed [-MIN,MAX] to a narrower unsigned.  */
  r0 = irange (long_long_integer_type_node,
	       TYPE_MIN_VALUE (long_long_integer_type_node),
	       TYPE_MAX_VALUE (long_long_integer_type_node));
  r0.cast (short_unsigned_type_node);
  r1 = irange (short_unsigned_type_node,
	       TYPE_MIN_VALUE (short_unsigned_type_node),
	       TYPE_MAX_VALUE (short_unsigned_type_node));
  ASSERT_TRUE (r0 == r1);

  /* Test that casting a range with MAX_PAIRS that changes sign is
     done conservatively.

        (unsigned short)[-5,5][20,30][40,50]...
     => (unsigned short)[-5,50]
     => [0,50][65531,65535].  */
  r0 = irange (short_integer_type_node, -5, 5);
  gcc_assert (r0.max_pairs * 2 * 10 + 10 < 32767);
  unsigned i;
  for (i = 2; i < r0.max_pairs * 2; i += 2)
    {
      r1 = irange (short_integer_type_node, i * 10, i * 10 + 10);
      r0.union_ (r1);
    }
  r0.cast(short_unsigned_type_node);
  r1 = irange (short_unsigned_type_node, 0, (i - 2) * 10 + 10);
  r2 = irange (short_unsigned_type_node, 65531, 65535);
  r1.union_ (r2);
  ASSERT_TRUE (r0 == r1);

  /* NOT([10,20]) ==> [-MIN,9][21,MAX].  */
  r0 = r1 = irange (integer_type_node, 10, 20);
  r2 = irange (integer_type_node, minint, INT(9));
  ASSERT_FALSE (r2.union_ (irange (integer_type_node,
				   INT(21), maxint)).empty_p ());
  r1.invert ();
  ASSERT_TRUE (r1 == r2);
  /* Test that NOT(NOT(x)) == x.  */
  r2.invert ();
  ASSERT_TRUE (r0 == r2);

  /* NOT(-MIN,+MAX) is the empty set and should return false.  */
  r0 = irange (integer_type_node, minint, maxint);
  ASSERT_TRUE (r0.invert ().empty_p ());
  r1.clear ();
  ASSERT_TRUE (r0 == r1);

  /* Test that booleans and their inverse work as expected.  */
  range_zero (&r0, boolean_type_node);
  ASSERT_TRUE (r0 == irange (boolean_type_node, 0, 0));
  r0.invert();
  ASSERT_TRUE (r0 == irange (boolean_type_node, 1, 1));

  /* Casting NONZERO to a narrower type will wrap/overflow so
     it's just the entire range for the narrower type.

     "NOT 0 at signed 32-bits" ==> [-MIN_32,-1][1, +MAX_32].  This is
     is outside of the range of a smaller range, return the full
     smaller range.  */
  range_non_zero (&r0, integer_type_node);
  r0.cast (short_integer_type_node);
  r1 = irange (short_integer_type_node,
	       TYPE_MIN_VALUE (short_integer_type_node),
	       TYPE_MAX_VALUE (short_integer_type_node));
  ASSERT_TRUE (r0 == r1);

  /* Casting NONZERO from a narrower signed to a wider signed.

     NONZERO signed 16-bits is [-MIN_16,-1][1, +MAX_16].
     Converting this to 32-bits signed is [-MIN_16,-1][1, +MAX_16].  */
  range_non_zero (&r0, short_integer_type_node);
  r0.cast (integer_type_node);
  r1 = irange (integer_type_node, -32768, -1);
  r2 = irange (integer_type_node, 1, 32767);
  r1.union_ (r2);
  ASSERT_TRUE (r0 == r1);

  if (irange::max_pairs > 2)
    {
      /* ([10,20] U [5,8]) U [1,3] ==> [1,3][5,8][10,20].  */
      r0 = irange (integer_type_node, 10, 20);
      r1 = irange (integer_type_node, 5, 8);
      r0.union_ (r1);
      r1 = irange (integer_type_node, 1, 3);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == RANGE3 (1, 3, 5, 8, 10, 20));

      /* [1,3][5,8][10,20] U [-5,0] => [-5,3][5,8][10,20].  */
      r1 = irange (integer_type_node, -5, 0);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == RANGE3 (-5, 3, 5, 8, 10, 20));
    }

  /* [10,20] U [30,40] ==> [10,20][30,40].  */
  r0 = irange (integer_type_node, 10, 20);
  r1 = irange (integer_type_node, 30, 40);
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange_union (irange (integer_type_node, 10, 20),
				   irange (integer_type_node, 30, 40)));
  if (irange::max_pairs > 2)
    {
      /* [10,20][30,40] U [50,60] ==> [10,20][30,40][50,60].  */
      r1 = irange (integer_type_node, 50, 60);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == RANGE3 (10, 20, 30, 40, 50, 60));
      /* [10,20][30,40][50,60] U [70, 80] ==> [10,20][30,40][50,60][70,80].  */
      r1 = irange (integer_type_node, 70, 80);
      r0.union_ (r1);

      r2 = RANGE3 (10, 20, 30, 40, 50, 60);
      r2.union_ (irange (integer_type_node, 70, 80));
      ASSERT_TRUE (r0 == r2);
    }

  /* Make sure NULL and non-NULL of pointer types work, and that
     inverses of them are consistent.  */
  tree voidp = build_pointer_type (void_type_node);
  range_zero (&r0, voidp);
  r1 = r0;
  r0.invert ();
  r0.invert ();
  ASSERT_TRUE (r0 == r1);

  if (irange::max_pairs > 2)
    {
      /* [10,20][30,40][50,60] U [6,35] => [6,40][50,60].  */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = irange (integer_type_node, 6, 35);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == irange_union (irange (integer_type_node, 6, 40),
				       irange (integer_type_node, 50, 60)));

      /* [10,20][30,40][50,60] U [6,60] => [6,60] */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = irange (integer_type_node, 6, 60);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == irange (integer_type_node, 6, 60));

      /* [10,20][30,40][50,60] U [6,70] => [6,70].  */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = irange (integer_type_node, 6, 70);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == irange (integer_type_node, 6, 70));

      /* [10,20][30,40][50,60] U [35,70] => [10,20][30,70].  */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = irange (integer_type_node, 35, 70);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == irange_union (irange (integer_type_node, 10, 20),
				       irange (integer_type_node, 30, 70)));
    }

  /* [10,20][30,40] U [25,70] => [10,70].  */
  r0 = irange_union (irange (integer_type_node, 10, 20),
		     irange (integer_type_node, 30, 40));
  r1 = irange (integer_type_node, 25, 70);
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange_union (irange (integer_type_node, 10, 20),
				   irange (integer_type_node, 25, 70)));

  if (irange::max_pairs > 2)
    {
      /* [10,20][30,40][50,60] U [15,35] => [10,40][50,60].  */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = irange (integer_type_node, 15, 35);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == irange_union (irange (integer_type_node, 10, 40),
				       irange (integer_type_node, 50, 60)));
    }

  /* [10,20] U [15, 30] => [10, 30].  */
  r0 = irange (integer_type_node, 10, 20);
  r1 = irange (integer_type_node, 15, 30);
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange (integer_type_node, 10, 30));

  /* [10,20] U [25,25] => [10,20][25,25].  */
  r0 = irange (integer_type_node, 10, 20);
  r1 = irange (integer_type_node, 25, 25);
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange_union (irange (integer_type_node, 10, 20),
				   irange (integer_type_node, 25, 25)));

  if (irange::max_pairs > 2)
    {
      /* [10,20][30,40][50,60] U [35,35] => [10,20][30,40][50,60].  */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = irange (integer_type_node, 35, 35);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == RANGE3 (10, 20, 30, 40, 50, 60));
    }

  /* [15,40] U [] => [15,40].  */
  r0 = irange (integer_type_node, 15, 40);
  r1.clear ();
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange (integer_type_node, 15, 40));

  /* [10,20] U [10,10] => [10,20].  */
  r0 = irange (integer_type_node, 10, 20);
  r1 = irange (integer_type_node, 10, 10);
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange (integer_type_node, 10, 20));

  /* [10,20] U [9,9] => [9,20].  */
  r0 = irange (integer_type_node, 10, 20);
  r1 = irange (integer_type_node, 9, 9);
  r0.union_ (r1);
  ASSERT_TRUE (r0 == irange (integer_type_node, 9, 20));

  if (irange::max_pairs > 2)
    {
      /* [10,10][12,12][20,100] ^ [15,200].  */
      r0 = RANGE3 (10, 10, 12, 12, 20, 100);
      r1 = irange (integer_type_node, 15, 200);
      r0.intersect (r1);
      ASSERT_TRUE (r0 == irange (integer_type_node, 20,100));

      /* [10,20][30,40][50,60] ^ [15,25][38,51][55,70]
	 => [15,20][38,40][50,51][55,60].  */
      r0 = RANGE3 (10, 20, 30, 40, 50, 60);
      r1 = RANGE3 (15, 25, 38, 51, 55, 70);
      r0.intersect (r1);
      if (irange::max_pairs == 3)
	{
	  /* When pairs==3, we don't have enough space, so
	     conservatively handle things.  Thus, the ...[50,60].  */
	  ASSERT_TRUE (r0 == RANGE3 (15, 20, 38, 40, 50, 60));
	}
      else
	{
	  r2 = RANGE3 (15, 20, 38, 40, 50, 51);
	  r2.union_ (irange (integer_type_node, 55, 60));
	  ASSERT_TRUE (r0 == r2);
	}

      /* [15,20][30,40][50,60] ^ [15,35][40,90][100,200]
	 => [15,20][30,35][40,60].  */
      r0 = RANGE3 (15, 20, 30, 40, 50, 60);
      r1 = RANGE3 (15, 35, 40, 90, 100, 200);
      r0.intersect (r1);
      if (irange::max_pairs == 3)
	{
	  /* When pairs==3, we don't have enough space, so
	     conservatively handle things.  */
	  ASSERT_TRUE (r0 == RANGE3 (15, 20, 30, 35, 40, 60));
	}
      else
	{
	  r2 = RANGE3 (15, 20, 30, 35, 40, 40);
	  r2.union_ (irange (integer_type_node, 50, 60));
	  ASSERT_TRUE (r0 == r2);
	}

      /* Test cases where a union inserts a sub-range inside a larger
	 range.

	 [8,10][135,255] U [14,14] => [8,10][14,14][135,255].  */
      r0 = irange_union (irange (integer_type_node, 8, 10),
			 irange (integer_type_node, 135, 255));
      r1 = irange (integer_type_node, 14, 14);
      r0.union_ (r1);
      ASSERT_TRUE (r0 == RANGE3 (8, 10, 14, 14, 135, 255));
    }

  /* [10,20] ^ [15,30] => [15,20].  */
  r0 = irange (integer_type_node, 10, 20);
  r1 = irange (integer_type_node, 15, 30);
  r0.intersect (r1);
  ASSERT_TRUE (r0 == irange (integer_type_node, 15, 20));

  /* [10,20][30,40] ^ [40,50] => [40,40].  */
  r0 = irange_union (irange (integer_type_node, 10, 20),
		     irange (integer_type_node, 30, 40));
  r1 = irange (integer_type_node, 40, 50);
  r0.intersect (r1);
  ASSERT_TRUE (r0 == irange (integer_type_node, 40, 40));

  /* Test non-destructive intersection.  */
  r0 = rold = irange (integer_type_node, 10, 20);
  ASSERT_FALSE (irange_intersect (r0,
				  irange (integer_type_node, 15, 30)).empty_p ());
  ASSERT_TRUE (r0 == rold);

  /* Test the internal sanity of wide_int's wrt HWIs.  */
  ASSERT_TRUE (wi::max_value (TYPE_PRECISION (boolean_type_node),
			      TYPE_SIGN (boolean_type_node))
	       == wi::uhwi (1, TYPE_PRECISION (boolean_type_node)));

  /* Test irange_storage.  */
  r0.set_range (integer_type_node, 5, 10);
  irange_storage *stow = irange_storage::ggc_alloc_init (r0);
  stow->extract_irange (r1, integer_type_node);
  ASSERT_TRUE (r0 == r1);

  /* Test zero_p().  */
  r0.set_range (integer_type_node, 0, 0);
  ASSERT_TRUE (r0.zero_p ());

  /* Test non_zero_p().  */
  r0 = irange (integer_type_node, 0, 0);
  r0.invert ();
  ASSERT_TRUE (r0.non_zero_p ());

  /* Test irange / value_range conversion functions.  */
  r0.set_range (integer_type_node, 10, 20, irange::INVERSE);
  value_range vr;
  irange_to_value_range (vr, r0);
  ASSERT_TRUE (vr.type == VR_ANTI_RANGE);
  ASSERT_TRUE (wi::eq_p (10, wi::to_wide (vr.min))
	       && wi::eq_p (20, wi::to_wide (vr.max)));
  value_range_to_irange (r1, integer_type_node, vr);
  ASSERT_TRUE (r0 == r1);
}

} // namespace selftest
#endif // CHECKING_P
