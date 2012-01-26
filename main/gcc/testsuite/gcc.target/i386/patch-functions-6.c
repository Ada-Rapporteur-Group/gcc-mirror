/* { dg-do run} */
/* { dg-options "-mpatch-functions-for-instrumentation" } */

/* 'main' function should always be patched, irrespective of how small it is.
   Check there are nop-bytes at beginning and end of main.  */

/* { dg-final { scan-assembler ".byte\t0xeb,0x09(.*).byte\t0x90" } } */
/* { dg-final { scan-assembler "ret(.*).byte\t0x90(.*).byte\t0x90" } } */

int main(int argc, char **argv) {
  int x = 0;
  return 0;
}
