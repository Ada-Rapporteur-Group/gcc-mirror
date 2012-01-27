#define HAVE_IO 1

#if HAVE_IO
#include <stdio.h>
#endif
#include <stdlib.h>

/* char __sec_reduce_add (int *); */
int main(int argc, char **argv)
{
  int ii,array[10], y = 0, y_int = 0, array2[10];
  double x, yy, array3[10], array4[10];
  for (ii = 0; ii < 10; ii++)
    {
      array[ii] = 1+ii;
      array2[ii]= 2; 
    }

  for (ii = 0; ii < 10; ii++)
    {
      if (ii%2 && ii)
	array3[ii] = (double)(1.0000/(double)ii);
      else
	array3[ii] = (double) ii + 0.10;
      array4[ii] = (double) (1.00000/ (double)(ii+1));
    }

  /* array[:] = 5; */
  x = __sec_reduce_max (array3[:] * array4[:]); 
  y = __sec_reduce_max_ind ( array3[:] * array4[:]); 
#if HAVE_IO
  for (ii = 0; ii < 10; ii++) 
    printf("%5.3f ", array3[ii] * array4[ii]);
  printf("\n");
  printf("Max = %5.3f\t Max Index = %2d\n", x, y);
#endif

  x = __sec_reduce_min (array3[:] * array4[:]); 
  y = __sec_reduce_min_ind ( array3[:] * array4[:]); 
#if HAVE_IO
  for (ii = 0; ii < 10; ii++) 
    printf("%5.3f ", array3[ii] * array4[ii]);
  printf("\n");
  printf("Min = %5.3f\t Min Index = %2d\n", x, y);
#endif

  x = __sec_reduce_add (array3[:] * array4[:]); 
  yy = __sec_reduce_mul ( array3[:] * array4[:]); 
#if HAVE_IO
  for (ii = 0; ii < 10; ii++) 
    printf("%5.3f ", array3[ii] * array4[ii]);
  printf("\n");
  printf("Add = %5.3f\t Mul = %f\n", x, yy);
#endif

  for (ii = 0; ii < 10; ii++)
    {
      if (ii%2 && ii)
	array3[ii] = (double)(1.0000/(double)ii);
      else
	array3[ii] = (double) ii + 0.00;
      array4[ii] = (double) (1.00000/ (double)(ii+1));
    }
  y_int = __sec_reduce_any_zeros (array3[:] * array4[:]); 
  y = __sec_reduce_all_zeros ( array3[:] * array4[:]); 
#if HAVE_IO
  for (ii = 0; ii < 10; ii++) 
    printf("%5.3f ", array3[ii] * array4[ii]);
  printf("\n");
  printf("Any Zeros = %d\t All Zeros = %d\n", y_int, y);
#endif
  return 0;
}
