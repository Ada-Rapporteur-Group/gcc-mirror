/* { dg-do compile } */
/* { dg-require-ifunc "" } */
/* { dg-options "-O0" } */

__attribute__ ((target_version ("sve+sve2"))) int
foo(); /* { dg-message "previous declaration of .foo. with type " } */

int bar () { return foo (); } /* { dg-error "implicit declaration of function .foo." } */
