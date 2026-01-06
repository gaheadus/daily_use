
/* a program that calculates the square root of a number using the C Maths 
   Library function sqrt() 

*/

#include <stdio.h>
#include <math.h>

main()
{

  double x, sqrt_x;

  printf(" enter x ");
  scanf("%lf", &x);
  printf(" x = %lf\n", &x);

  sqrt_x = sqrt(x);
  
  printf(" the square root of %lf is %lf\n", x, sqrt_x);

}
