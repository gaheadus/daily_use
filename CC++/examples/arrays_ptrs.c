/*
  Simple program to demonstrate the similarities between arrays and
  pointers with respect to pointer arithmetic. -- djh
*/

/*
  Notes:

  1. Makes use of the implicit sizing of an array via initialization.

  2. Computes the number of elements in an array by dividing the size
     of an array by the size of an element array.

  3. While sizeof() can be used in this manner on a declared array,
     using it on a pointer to that same array will produce different
     results.  Why?  Because sizeof(<some pointer>) does not compute
     the size of the thing pointed to, but rather the size of the
     pointer itself (in other words, the size required to store an
     address).  Why, then, cannot sizeof() be used inside
     print_array()?  Because, from the perspective of the function
     declaration, the first argument is treated exactly like a pointer
     to an integer.
*/

#include <stdio.h>

void print_array(int a[], int array_size)
{
  int index;

  for (index = 0 ; index < (array_size / sizeof(int)) ; index++)
    (void) printf("a[%d] = %d\n", index, a[index]);
  (void) printf("\n");
}

int main(void)
{
  int a[] = { 10, 20, 30, 40 }; /* declare and initialize integer
				   array of size 4 */
  int *ap;			/* declare pointer to an integer */

  print_array(a, sizeof(a));
  a[1] = 5;			/* assign 5 to second element of array
				   a, using array notation*/
  print_array(a, sizeof(a));
  *(a + 1) = 6;			/* assign 6 to second element of array
				   a, using pointer arithmetic */
  print_array(a, sizeof(a));
  ap = a;			/* ap now points to address of array a */
  *(ap + 1) = 30;		/* assign 30 to second element of
				   array pointed to by ap, using
				   pointer arithmetic */
  print_array(a, sizeof(a));
  ap[1] = 35;			/* assign 35 to second element of
				   array pointed to by ap, using array
				   notation */
  print_array(a, sizeof(a));

  return 0;
}
