/* Test for strings cast through integer types: should not be treated
   as format strings unless the types are of the same width as
   pointers (intptr_t or similar).  */
/* Origin: Joseph Myers <joseph@codesourcery.com> */
/* { dg-do compile } */
/* { dg-options "-Wformat" } */

#include "format.h"

void
f (int x)
{
  printf("%s", x); /* { dg-warning "format" } */
  printf((char *)(__UINTPTR_TYPE__)"%s", x); /* { dg-warning "format" } */
  printf((char *)(char)"%s", x); /* { dg-warning "cast from pointer to integer of different size" } */
  /* { dg-warning "cast from provenance-free integer type to pointer type will give pointer that can not be dereferenced" "" { target { aarch64_capability_any } } .-1 } */
}
