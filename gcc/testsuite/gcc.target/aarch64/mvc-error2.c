/* { dg-do compile } */
/* { dg-require-ifunc "" } */
/* { dg-options "-O0" } */

__attribute__ ((target_clones ("default, dotprod"))) float
foo () { return 3; } /* { dg-message "previous definition of .foo." } */

__attribute__ ((target_clones ("dotprod", "sve"))) float
foo () { return 3; } /* { dg-error "conflicting .dotprod. version declarations of .foo." } */
