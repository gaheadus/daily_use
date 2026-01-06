/*
  Variant of temps.c which uses floating point variables to represent
  the temperatures.  Note that, while the computation of 5/9's is
  directly stated here, the use of the decimal points is required to
  force a floating point result. -- djh
*/

#include <stdio.h>

int main(void)
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;			/* lower limit of temperature table */
  upper = 300;			/* upper limit */
  step = 20;			/* step size */

  fahr = lower;
  while (fahr <= upper) {
    celsius = 5.0 / 9.0 * (fahr - 32.0); /* 5.0/9.0 to force floating point */
    (void) printf("%3.0f\t%6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
  return 0;
}
