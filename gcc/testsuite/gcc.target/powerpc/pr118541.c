/* { dg-do compile } */
/* { dg-options "-mdejagnu-cpu=power9 -O2" } */
/* { dg-require-effective-target powerpc_vsx } */

/* PR target/118541 says that the ordered comparison functions like isgreater
   should not optimize floating point conditional moves to use
   x{s,v}cmp{eq,gt,ge}{dp,qp} and xxsel since that instruction can cause traps
   if one of the arguments is a signaling NaN.  */

/* Verify isgreater, isgreaterequal, isless, and islessequal does not generate
   xscmpltdp, xscmpgtdp, or xscmpeqdp.  */

double
ordered_gt (double a, double b, double c, double d)
{
  /*
   * fcmpu 0,1,2
   * fmr 1,4
   * bnglr 0
   * fmr 1,3
   * blr
   */

  return __builtin_isgreater (a, b) ? c : d;
}

double
ordered_ge (double a, double b, double c, double d)
{
  /*
   * fcmpu 0,1,2
   * fmr 1,4
   * cror 2,0,3
   * beqlr 0
   * fmr 1,3
   * blr
   */

  return __builtin_isgreaterequal (a, b) ? c : d;
}

double
ordered_lt (double a, double b, double c, double d)
{
  /*
   * fcmpu 0,1,2
   * fmr 1,4
   * bnllr 0
   * fmr 1,3
   * blr
   */

  return __builtin_isless (a, b) ? c : d;
}

double
ordered_le (double a, double b, double c, double d)
{
  /*
   * fcmpu 0,1,2
   * fmr 1,4
   * cror 2,1,3
   * beqlr 0
   * fmr 1,3
   * blr
   */

  return __builtin_islessequal (a, b) ? c : d;
}

double
normal_gt (double a, double b, double c, double d)
{
  /*
   * xscmpgtdp 1,1,2
   * xxsel 1,4,3,1
   * blr
   */

  return a > b ? c : d;
}

double
normal_ge (double a, double b, double c, double d)
{
  /*
   * xscmpgedp 1,1,2
   * xxsel 1,4,3,1
   * blr
   */

  return a >= b ? c : d;
}

double
normal_lt (double a, double b, double c, double d)
{
  /*
   * xscmpgtdp 1,2,1
   * xxsel 1,4,3,1
   * blr
   */

  return a < b ? c : d;
}

double
normal_le (double a, double b, double c, double d)
{
  /*
   * xscmpgedp 1,2,1
   * xxsel 1,4,3,1
   * blr
   */

  return a <= b ? c : d;
}

double
normal_eq (double a, double b, double c, double d)
{
  /*
   * xscmpeqdp 1,1,2
   * xxsel 1,4,3,1
   * blr
   */

  return a == b ? c : d;
}

double
normal_ne (double a, double b, double c, double d)
{
  /*
   * xscmpeqdp 1,1,2
   * xxsel 1,3,4,1
   * blr
   */

  return a != b ? c : d;
}

/* { dg-final { scan-assembler-times {\mxscmpudp\M|\mfcmpu\M} 4 } } */
/* { dg-final { scan-assembler-times {\mxscmpeqdp\M}          2 } } */
/* { dg-final { scan-assembler-times {\mxscmpgedp\M}          2 } } */
/* { dg-final { scan-assembler-times {\mxscmpgtdp\M}          2 } } */
/* { dg-final { scan-assembler-times {\mxxsel\M}              6 } } */
