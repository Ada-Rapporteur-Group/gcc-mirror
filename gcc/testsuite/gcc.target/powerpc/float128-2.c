/* { dg-do run { target { powerpc*-*-linux* && lp64 } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-skip-if "" { powerpc*-*-*spe* } { "*" } { "" } } */
/* { dg-require-effective-target ppc_recip_hw } */
/* { dg-options "-O2 -mfloat128-ref -static-libgcc" } */

int
main (void)
{
  __float128 one = 1.0q;
  __float128 two = 2.0q;
  __float128 three = 3.0q;
  __float128 four = 4.0q;
  __float128 result = ((1.0q + 2.0q) * 3.0q) / 4.0q;
  __float128 xresult;

  __asm__ (" #prevent constant folding, %0" : "+d" (one));
  __asm__ (" #prevent constant folding, %0" : "+d" (two));
  __asm__ (" #prevent constant folding, %0" : "+d" (three));
  __asm__ (" #prevent constant folding, %0" : "+d" (four));

  xresult = ((one + two) * three) / four;
  if (result != xresult)
    __builtin_abort ();

  return 0;
}
