/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "do not override -mcpu" { powerpc*-*-* } { "-mcpu=*" } { "-mcpu=power9" } } */
/* { dg-require-effective-target lp64 } */
/* { dg-require-effective-target powerpc_p9vector_ok } */
/* { dg-skip-if "" { powerpc*-*-aix* } } */
/* { dg-options "-mcpu=power9" } */

/* This test should succeed only 64-bit configuration.  */
#include <altivec.h>

double get_exponent (unsigned int *exponent_p, 
		     unsigned long long int *signficand_p)
{
  unsigned int exponent = *exponent_p;
  unsigned long long int significand = *significand_p;

  return scalar_insert_exp (exponent, significand);
}

/* { dg-final { scan-assembler "xsiexpdp" } } */
