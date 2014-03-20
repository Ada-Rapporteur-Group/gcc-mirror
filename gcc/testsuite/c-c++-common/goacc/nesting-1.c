void
f_acc_parallel (void)
{
#pragma acc parallel
  {
    int i;

#pragma acc loop
    for (i = 0; i < 2; ++i)
      ;
  }
}


void
f_acc_kernels (void)
{
#pragma acc kernels
  {
    int i;

#pragma acc loop
    for (i = 0; i < 2; ++i)
      ;
  }
}


void
f_acc_data (void)
{
#pragma acc data
  {
    int i;

#pragma acc parallel
    ;

#pragma acc parallel
    {
#pragma acc loop
      for (i = 0; i < 2; ++i)
	;
    }

#pragma acc kernels
    ;

#pragma acc data
    ;

#pragma acc loop
    for (i = 0; i < 2; ++i)
      ;
  }
}
