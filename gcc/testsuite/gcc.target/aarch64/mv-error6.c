/* { dg-do compile } */
/* { dg-require-ifunc "" } */
/* { dg-options "-O0" } */

__attribute__ ((target_version ("sve+sve2"))) int
foo () { /* { dg-message "previous definition of .foo." "note" } */
	return 1;
}

__attribute__ ((target_version ("sve"))) int
foo () {
	return 1;
}

int bar () { return foo (); } /* { dg-error "implicit declaration of function .foo." } */

__attribute__ ((target_version ("sve+sve2"))) int
foo2(); /* { dg-message "previous declaration of .foo2." "note" } */

int bar2 () { return foo2 (); } /* { dg-error "implicit declaration of function .foo2." } */
