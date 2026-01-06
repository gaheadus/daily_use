/*
  Another variant of the temperature conversion and printing program,
  this time using the more compact for loop notation and the embedding
  of computations directly in the argument list of printf(). -- djh
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  float fahr;
  int lower, upper, step;

  lower = 0;			/* lower limit of temperature table */
  upper = 300;			/* upper limit */
  step = 20;			/* step size */

  for (fahr = lower ; fahr <= upper ; fahr = fahr + step)
    (void) printf("%3.0f\t%6.1f\n", fahr, 5.0/9.0 * (fahr - 32.0));
  return 0;
}
