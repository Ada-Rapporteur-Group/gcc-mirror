/* { dg-do assemble { target powerpc*-*-* } } */
/* { dg-require-effective-target power11_ok } */
/* { dg-options "-mdejagnu-cpu=power11 -O2" } */

/* Basic check to see if the compiler supports -mcpu=power11.  */

#ifndef _ARCH_PWR11
#error "-mcpu=power11 is not supported"
#endif

void foo (void)
{
}
