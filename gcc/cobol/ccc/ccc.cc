#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
  {
  char ach[128];
  _Float128 dddd = strtof128 ("1.23", NULL);

  _Float128 afloat      = cosf((float)1.23);
  _Float128 bdouble     = cos ((double)1.23);;
  _Float128 clongdouble = cosl((long double)1.23);
  _Float128 dfloat128   = cosf128(dddd);

  strfromf128(ach, sizeof(ach), "%.72f", afloat);
  printf("%s\n", ach);

  strfromf128(ach, sizeof(ach), "%.72f", bdouble);
  printf("%s\n", ach);

  strfromf128(ach, sizeof(ach), "%.72f", clongdouble);
  printf("%s\n", ach);

  strfromf128(ach, sizeof(ach), "%.72f", dfloat128 );
  printf("%s\n", ach);
  }
