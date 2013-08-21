/* { dg-do run { xfail *-*-* } } */
/* { dg-options "-fcheck-pointers -mmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */

#define XFAIL

#include "mpx-check.h"

char *str="dddd";

int foo1 (char** ptr)
{
  *ptr=str;
}

int foo (char *ptr)
{
  char *tmp = 0;
  foo1 (&ptr);
  tmp = ptr;
  return tmp[5];
}

int mpx_test (int argc, const char **argv)
{
  printf ("%d\n", foo ("ddddd"));
  return 0;
}
