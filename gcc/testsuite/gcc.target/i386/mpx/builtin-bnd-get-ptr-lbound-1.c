/* { dg-do run } */
/* { dg-options "-fmpx" } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */

#include "mpx-check.h"

char buf[100];

int mpx_test (int argc, const char **argv)
{
  assert (buf == __bnd_get_ptr_lbound (buf));
  return 0;
}
