/* { dg-do compile } */
/* { dg-options } */

int main (int argc, char **argv)
{
  int array[10][10], array2[10];
  
  array2[:] = array2[: ;  /* { dg-error "start index " } */

  return 0;
} 
