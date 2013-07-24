/* { dg-do run { xfail *-*-* } } */
/* { dg-options "-fmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */

#define XFAIL

#include "mpx-check.h"

struct s {
  int a;
  int *p;
} s;

int buf[100];

struct s s1 = {0, buf};

int mpx_test (int argc, const char *argv[])
{
  printf ("%d\n", s1.p[100]);

  return 0;
}
