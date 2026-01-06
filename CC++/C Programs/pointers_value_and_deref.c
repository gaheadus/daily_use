#include <stdio.h>
#include <math.h>

main()
{
  int i, *p;
  
  i = 7;
  p = &i;

  printf("\nthe value of i is %d\nthe location of i is %x\n", *p, p);

  exit(0);
}
