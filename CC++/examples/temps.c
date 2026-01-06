/*
  Demonstrates some simple iterative arithemtic processing and output.
  Note the separation of the division of 5 by 9 in the conversion from
  Fahrenheit to Celsius in order to avoid an implicit use of integer
  arithmetic. -- djh
*/

#include <stdio.h>

int main(void)
{
  int fahr, celsius;
  int lower, upper, step;

  lower = 0;			/* lower limit of temperature table */
  upper = 300;			/* upper limit */
  step = 20;			/* step size */

  fahr = lower;
  while (fahr <= upper) {
    celsius = 5 * (fahr - 32) / 9; /* cannot use 5 / 9 */
    (void) printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + step;
  }
  return 0;
}
