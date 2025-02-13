/* { dg-do compile } */
/* { dg-require-ifunc "" } */
/* { dg-options "-O0" } */
/* { dg-additional-options "-Wno-experimental-fmv-target" } */

__attribute__ ((target_version ("dotprod"))) int
foo () { return 3; } /* { dg-message "previous definition" } */

__attribute__ ((target_clones ("dotprod", "sve"))) int
foo () { return 1; } /* { dg-error "conflicting .dotprod. versions" } */
