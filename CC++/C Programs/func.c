#include <stdio.h>
#include <math.h>

double f( double x, double y);

main()
{

 double a,b,c;

 a = 2.0;
 b = 3.0;

 c = f(a,b);

 printf("the function returns = %lf\n", c);

}

double f( double x, double y)
{

  double result;
  result = (sin (x) + 3.0*cos(y) )/( tan(x) + 5.0*log(y) );
  return result;

  /* note that I could also have written                           */
  /*   return( (sin (x) + 3.0*cos(y) )/( tan(x) + 5.0*log(y) ) );  */

}
