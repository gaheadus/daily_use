#include <math.h>
#include <stdio.h>

#define N 20
#define a 0.0
#define b 2.0

double f(double x);

main()    
{
  int c, k=1;                         /* Counters in the algorithm */
  double x, h, SUM;

/*  FILE *fp;   Declares a pointer to a file */
/*  fp=fopen("simpson.out","w");  Opens the file for output of data */


  printf("\nSimpson's Rule for numerical integration of f(x)\n");
  printf("\n From a=%lf to b=%lf", a,b);
  printf("\n\nIntervals\t\tStep Size\t\tSimpson Sum\n");

  SUM=f(a);                      /* Initial function value */
  c=2;
  h=(b-a)/N;                     /* Step size h=(b-a)/N */

  while (k <= N-1)               /* Steps through the iteration */
    {
      c=6-c;                    /* gives the 4,2,4,2,... in the algorithm    */
      SUM = SUM + c*f(a+k*h);   /* Adds on the next area                     */
      k++;                      /* Increases k, the no. of steps taken, by 1 */
    }

  SUM = ( SUM + f(b) )*h/3 ;    /* add the value f(b) to the sum and multiply*/
                                /* by overall factor, h/3                    */


  printf("%d  \t\t%lf \t\t%lf\n", N, h, SUM );  /* print the answer   */
                                                       
  /* the '\t' here is just to format the output. It corresponds to hitting
     the TAB key on the keyboard ie. skips a number of spaces before printing the next output. */

}

double f(double x)         
    {
     double function;
     function = x*x*x*x;
     return(function);   
    }
