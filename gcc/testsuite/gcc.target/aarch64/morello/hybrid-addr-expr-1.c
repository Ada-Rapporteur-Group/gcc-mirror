/* { dg-do assemble } */
/* { dg-additional-options "-mcmodel=tiny -fno-PIC -fgimple -g0 -save-temps" } */
/* { dg-final { check-function-bodies "**" "" } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-mabi=purecap" "-mfake-capability" } { "" } }  */

/*
** foo:
**	ldr	c0, \.LC0
**	ret
*/
int x;
__GIMPLE int *__capability foo() {
  int *__capability res;

  res = __CAP_ADDR x;
  return res;
}

/* { dg-final { scan-assembler {\t\.section\t\.data\.rel\.ro\.local,"aw"\n\t\.align\t4\n\t\.type\t\.LC0, %object\n} } } */
/* { dg-final { scan-assembler {\t\.size\t\.LC0, 16\n\.LC0:\n\t\.chericap\tx\n} } } */
