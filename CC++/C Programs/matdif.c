#include <stdio.h>
#include <math.h>

#define N 2
#define M 2

void matrix_add(double c[][M], double a[][M], double b[][M]);

main()
{
  int i,j;
  double A[2][2] = {1.0,2.0,3.0,4.0},  /* a 2x2 mx with these entries */
         B[2][2] = {1.0,2.0,3.0,4.0},  /* a 2x2 mx with these entries */
	 C[N][M];                      /* we'll put the answer in C   */


  matrix_add(C, A, B);  /* call the function to add A and B ... notice we are
			   just using the array names eg A <-> &A[0] but we
			   have specified all other column sizes for A in the
			   function    */
 for (i=0;i<2;i++)
  for (j=0;j<2; j++)
    printf("%lf\n", C[i][j]) ;   /* prints all the components of the result
				    matrix C  */
}

void matrix_add(double c[][M], double a[][M], double b[][M])
{
  int i,j ;
  /* the for loops are exactly as before, we're just doing the calculation
     in a function rather than the main part of the program             */
  for (i=0;i<N;i++)
    {
      for (j=0;j<M; j++)                      
	{	
	  c[i][j] = a[i][j]  + b[i][j] ;	
	}}
}
