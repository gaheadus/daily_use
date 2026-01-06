/*
  Example code to show the use of the -> shorthand for accessing the
  member of a structure via pointer dereference.  Note the error in
  the last assignment statement, caused by the fact that the
  precedence of the structure member operator (.) is higher (i.e.,
  binds more tightly) than the indirection operator (*).  The effect
  is that the compiler attempts to reference the member "x" in locp,
  which is not of type structure or union.  Because this code does not
  compile, it is not included in the "all" target of the Makefile.
  The compiler errors may be seen by running 'make struct_ptrs'. -- djh
*/

#include <stdio.h>

struct point {
  int x;
  int y;
};

int main(void)
{

  struct point loc;		/* declares variable of type struct point */
  struct point *locp;		/* declares pointer to struct point */

  locp = &loc;			/* locp gets address of loc */

  (*locp).x = 10;		/* okay */
  locp->x = 10;			/* okay; shorthand for above */
  *locp.x = 10;			/* compile-time error */
  return 0;
}
