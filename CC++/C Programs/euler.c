#include <stdio.h>
#include <math.h>
 
#define STEPSIZE 0.5                /* stepsize in t */
#define STOPPING_POINT 4.0                 /* max for t */ 
 
FILE *output;                   /* internal filename */

main()
{
  double t, y;
  int j;                         /* j keeps track of the step number */

  output=fopen("euler.dat", "w"); /* external filename */

  y=1;                            /* initial condition */
  fprintf(output, "0\t%lf\n", y);

  for (j=1;STEPSIZE*j<=STOPPING_POINT;j++)       /* the time loop */
    {
      t=j*STEPSIZE;
      y-=STEPSIZE*y;
 
      fprintf (output, "%lf\t%lf\n", t, y);
    }

  /* start again - this time printing the true solution */
   fprintf (output, "& \n");

   y=1;                            /* initial condition */
   fprintf(output, "0\t%lf\n", y);
   for (j=1;STEPSIZE*j<=STOPPING_POINT;j++)       /* the time loop */
     {
       t=j*STEPSIZE;
       y=exp(-t);
       fprintf (output, "%lf\t%lf\n", t, y);
     }

   fclose(output);

}
