/* { dg-final { scan-assembler "simdsimd"  } } */

/* This test will create 2 clones of the function below,
 * for the pentium4 with sse3 processor.
 */

#define My_Type float
__attribute__ ((vector(vectorlength(4), processor (core_2_duo_sse_4_1), linear(y), uniform (x))))
My_Type ef_add (My_Type x, My_Type y) 

{
  return x + y;
}

