#include <stdio.h>
#include <math.h>

void swap (int *, int *);

main()
{
  int i = 3, j = 5;

  swap(&i,&j);

  printf("i = %d \nj = %d \n", i,j);
  
  exit(0);

}

void swap (int *p, int *q)
{
  int tmp;

  tmp = *p;
  *p = *q;
  *q = tmp;

}
