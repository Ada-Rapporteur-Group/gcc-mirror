void
f (void)
{
#pragma acc update /* { dg-error "'#pragma acc update' must contain at least one 'device' or 'host/self' clause" } */

  int i = 0;
  int a[10];
#pragma acc update device(i)
#pragma acc update host(i)
#pragma acc update self(i)
#pragma acc update host(a(1:3)) /* { dg-error "expected '\\\)' before '\\\(' token" } */
}
