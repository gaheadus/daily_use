/*
  Demonstrates the behavior of the passing of parameters "by value" in
  C.  The badswap() function does not have the expected behavior of
  swapping the contents of two variables because it passes NOT the
  addresses of those variables, but the values of the variables.
  Because the parameters of badswap() are local copies, any
  modifications to those values will have no effect outside the scope
  of the function.  The parameters of goodswap() are still passed by
  value, but the values in this case are the addresses of the
  variables to be swapped; this permits the contents of the variables
  to be swapped.  Note that this kind of functionality should be used
  with care, as it may lead to unintended results since variables are
  being modified essentially as a side effect of the calling of a
  function. -- djh
*/

#include <stdio.h>

void badswap(int a, int b)	/* integer parameters */
{
  int tmp = b;
  b = a;
  a = tmp;
}

void goodswap(int *ap, int *bp)	/* integer pointer parameters */
{
  int tmp = *bp;
  *bp = *ap;
  *ap = tmp;
}

int main(void)
{
  int x = 10, y = 4;

  (void) printf("1: x = %d y = %d\n", x, y);
  badswap(x, y);		/* passing the values of x and y */
  (void) printf("2: x = %d y = %d\n", x, y);
  goodswap(&x, &y);		/* passing the addresses of x and y */
  (void) printf("3: x = %d y = %d\n", x, y);
  return 0;
}
