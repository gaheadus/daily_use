/*
  Demonstrates passing a function the reference (address) of a
  variable in order to permit the function to change the contents of
  the address.  Also demonstrates the declaration and use of a pointer
  to a function.  See the swap.c program for an example of why it's
  necessary to pass the addresses of the variables whose values are to
  be swapped rather than the values of the variables themselves. -- djh
*/

#include <stdio.h>

void swap(int *ap, int *bp)
{
  int tmp = *bp;
  *bp = *ap;
  *ap = tmp;
}

int main(void)
{
  void (*swapfunc)(int *, int *); /* declare pointer to function that
				     takes two pointers to integers as
				     arguments */
  int x = 23, y =87;

  swapfunc = &swap;		/* address of swap function is
				   assigned to swapfunc */
  (void) printf("1: x = %d y = %d\n", x, y);

  swap(&x, &y);			/* swap() is called directly */
  (void) printf("2: x = %d y = %d\n", x, y);

  (*swapfunc)(&x, &y);		/* swap() is called via pointer
				   dereference */
  (void) printf("3: x = %d y = %d\n", x, y);
  return 0;
}
