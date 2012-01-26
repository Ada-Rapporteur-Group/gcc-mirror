/* { dg-do run} */
/* { dg-options "-mpatch-functions-for-instrumentation -mpatch-functions-ignore-loops -mno-patch-functions-main-always" } */

/* Function is too small to be patched when ignoring the loop.
   Check there aren't any nop-bytes at beginning and end of function.  */

/* { dg-final { scan-assembler-not ".byte\t0xeb,0x09(.*).byte\t0x90" } } */
/* { dg-final { scan-assembler-not "ret(.*).byte\t0x90(.*).byte\t0x90" } } */

void foo() {
  int x = 0;
  while (++x);
}

int main() {
  foo();
  return 0;
}
