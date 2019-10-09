/* { dg-do compile } */
/* { dg-require-effective-target powerpc_pcrel_ok } */
/* { dg-options "-O2 -mdejagnu-cpu=future" } */

/* Tests for prefixed instructions testing whether pc-relative prefixed
   instructions are generated for V2DFmode.  */

#define TYPE vector double

#include "prefix-pcrel.h"

/* { dg-final { scan-assembler-times {\mplxv\M}  2 } } */
/* { dg-final { scan-assembler-times {\mpstxv\M} 2 } } */
