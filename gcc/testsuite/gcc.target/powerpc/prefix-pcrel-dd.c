/* { dg-do compile } */
/* { dg-require-effective-target powerpc_pcrel_ok } */
/* { dg-options "-O2 -mdejagnu-cpu=future" } */

/* Tests for prefixed instructions testing whether pc-relative prefixed
   instructions are generated for SImode.  */

#define TYPE _Decimal64

#include "prefix-pcrel.h"

/* { dg-final { scan-assembler-times {\mplfd\M}  2 } } */
/* { dg-final { scan-assembler-times {\mpstfd\M} 2 } } */
