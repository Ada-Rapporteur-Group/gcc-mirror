/* FIXME: remove -fno-var-tracking and -fno-exceptions from dg-options.  */

/* { dg-do run } */
/* { dg-options "-fno-inline -fno-var-tracking -fno-exceptions" } */

#include <stdio.h>
#include <stdlib.h>

#pragma acc routine (fact)


int fact (int n)
{
  if (n == 0 || n == 1)
    return 1;

  return n * fact (n - 1);
}

int
main()
{
  int *a, i, n = 10;

  a = (int *)malloc (sizeof (int) * n);

#pragma acc parallel copy (a[0:n]) vector_length (5)
  {
#pragma acc loop
    for (i = 0; i < n; i++)
      a[i] = fact (i);
  }

  for (i = 0; i < n; i++)
    if (a[i] != fact (i))
      abort ();

  free (a);

  return 0;
}
