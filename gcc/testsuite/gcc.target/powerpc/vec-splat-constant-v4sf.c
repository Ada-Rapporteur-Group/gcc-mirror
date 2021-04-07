/* { dg-do compile } */
/* { dg-require-effective-target power10_ok } */
/* { dg-options "-mdejagnu-cpu=power10 -O2 -save-temps" } */

#include <altivec.h>

/* Test whether XXSPLTIW is generated for V4SF vector constants.  */

vector float
v4sf_const_1 (void)
{
  return (vector float) { 1.0f, 1.0f, 1.0f, 1.0f };	/* XXSPLTIW.  */
}

vector float
v4sf_const_nan (void)
{
  return (vector float) { __builtin_nanf (""),
			  __builtin_nanf (""),
			  __builtin_nanf (""),
			  __builtin_nanf ("") };	/* XXSPLTIW.  */
}

vector float
v4sf_const_inf (void)
{
  return (vector float) { __builtin_inff (),
			  __builtin_inff (),
			  __builtin_inff (),
			  __builtin_inff () };		/* XXSPLTIW.  */
}

vector float
v4sf_const_m0 (void)
{
  return (vector float) { -0.0f, -0.0f, -0.0f, -0.0f };	/* XXSPLTIW.  */
}

vector float
v4sf_splats_1 (void)
{
  return vec_splats (1.0f);				/* XXSPLTIW.  */
}

vector float
v4sf_splats_nan (void)
{
  return vec_splats (__builtin_nanf (""));		/* XXSPLTIW.  */
}

vector float
v4sf_splats_inf (void)
{
  return vec_splats (__builtin_inff ());		/* XXSPLTIW.  */
}

vector float
v8hi_splats_m0 (void)
{
  return vec_splats (-0.0f);				/* XXSPLTIW.  */
}

/* { dg-final { scan-assembler-times {\mxxspltiw\M}  8 } } */
/* { dg-final { scan-assembler-not   {\mxxspltib\M}    } } */
/* { dg-final { scan-assembler-not   {\mlxvx?\M}       } } */
/* { dg-final { scan-assembler-not   {\mplxv\M}        } } */
