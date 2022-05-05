/* { dg-do assemble } */
/* { dg-additional-options "-fno-signed-zeros -save-temps" } */
/* { dg-final { check-function-bodies "**" ""  { {-O[123s]} } } } */
/* { dg-skip-if "" { *-*-* } { "-mabi=purecap" "-mfake-capability" } { "" } }  */

/*
** foo:
**	str	xzr, \[c0\]
**	str	xzr, \[c0, #?8\]
**	ret
*/
void
foo (long double *__capability ptr)
{
  *ptr = -0.0;
}
