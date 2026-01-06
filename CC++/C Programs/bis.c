/* You can find this program at http://www.maths.tcd.ie/~ryan/teaching.html */
                           /* Bisection method */
#include <math.h>
#include <stdio.h>
#define MAX_ITER 40

double fof(double x);
main()
{
  double a,b,mid, f_a,f_b,f_mid;
  double error_bound,tolerance;

  int iteration;

  printf("enter the range\n");
  scanf("%lf %lf",&a,&b);

  mid = 0.5 * (b+a);
  f_a = fof(a);
  f_b = fof(b);

  if (f_a * f_b > 0.0)
  { 
   printf("Sorry: bad initial points -- may not bracket a root\n Try again\n");
   exit(1);
   }

  f_mid = fof(mid);
  iteration = 0; 
  tolerance = .0001;
  error_bound = .5 * (b - a);

  printf("i   a    b      mid    f_of_a   f_of_b   f_mid  err_bound\n");
  printf("%d %1.4lf %1.4lf %1.4lf %1.4lf %1.4lf %1.4lf %1.4lf\n",
	             iteration,a,b,mid,f_a,f_b,f_mid,error_bound);

  while ((error_bound > tolerance) && (iteration < MAX_ITER))
    {
	if (f_a * f_mid < 0.0) {
		b = mid;
		f_b = f_mid;
		mid = .5 * (a+mid);
	}
	else {
		a = mid;
		f_a = f_mid;
		mid = .5 * (b+mid);
	}
	f_mid = fof(mid);
	error_bound = .5 * (b - a);
	iteration++;
	printf("%d %lf %lf %lf %lf %lf %lf %lf\n",
	                 iteration,a,b,mid,f_a,f_b,f_mid,error_bound);
    }

  printf("\nSolution is x = %lf function = %lf iterations = %d 
                  error_bound = %lf\n\n\n", mid,f_mid,iteration,error_bound);
}

double fof(double x)
{
  /* You can chose any functional form you want and write it here */
	return(x*x*x - x - 1.0);
}
