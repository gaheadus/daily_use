/*
  Demonstrates the definition of a structure, declaration of pointers
  to a structure, allocation/deallocation of memory associated with a
  structure, and the dangers of dereferencing memory locations that
  have been freed for reuse.  Note that this program is, at least
  partly, a BAD example of pointer handling, specifically the
  dereferencing of ptr1 AFTER the memory associated with this pointer
  has been freed.  Good practice in the management of pointers is that
  a two step process be followed in memory deallocation: (1) free the
  memory associated with the pointer then, (2) set the value of the
  pointer to NULL.  While this would not fully solve the problem at
  the end of the code below, in that it changes the behavior to that
  of dereferencing a NULL pointer, the pointer error would be more
  informative and easier to detect at runtime rather than the
  mysterious modification of the fields of the struct pointed to by
  ptr2.  Note also the use of %p in the printf() format strings to
  indicate that the value being printed is that of a pointer.
  Finally, notice the use of the explicit casts of values being
  assigned to the pointers.  In this case, such casts are not required
  (malloc(), for example returns the "universal" value of type void
  *), but it is still good practice to place such casts in the code as
  they can help to increase readability and improve compile time type
  checking. -- djh
*/

#include <stdio.h>
#include <stdlib.h>

struct point {
  int x, y;
};

int main(void)
{
  struct point *ptr1, *ptr2;	/* declare to pointers to struct */

  ptr1 = ptr2 = (struct point *) NULL; /* initialize pointers */

  (void) printf("before malloc(): address of ptr1 = %p\n\n", ptr1);

  ptr1 = (struct point *) malloc(sizeof(struct point));
  (void) printf("after malloc(): address of ptr1 = %p\n", ptr1);
  ptr1 -> x = 14;
  ptr1 -> y = 28;
  (void) printf("ptr1 -> x = %d\tptr1 -> y = %d\n\n", ptr1 -> x, ptr1 -> y);

  free(ptr1);
  (void) printf("after free(): address of ptr1 = %p\n\n", ptr1);

  ptr2 = (struct point *) malloc(sizeof(struct point));
  (void) printf("after malloc(): address of ptr2 = %p\n", ptr2);
  (void) printf("ptr2 -> x = %d\tptr2 -> y = %d\n\n", ptr2 -> x, ptr2 -> y);

  ptr1 -> x = 87;
  ptr1 -> y = 21;
  (void) printf("ptr2 -> x = %d\tptr2 -> y = %d\n", ptr2 -> x, ptr2 -> y);

  return 0;
}
