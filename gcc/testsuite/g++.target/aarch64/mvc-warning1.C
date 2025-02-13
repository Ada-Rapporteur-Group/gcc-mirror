/* { dg-do compile } */
/* { dg-require-ifunc "" } */
/* { dg-options "-O0" } */
/* { dg-additional-options "-Wno-experimental-fmv-target" } */

__attribute__((target_clones("default", "dotprod", "sve+sve2")))
int foo () {
  return 1;
}

__attribute__((target_clones("invalid1")))
int foo () { /* { dg-warning "invalid .target_clones. version .invalid1. ignored" } */
  return 2;
}
