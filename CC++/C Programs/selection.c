#include <stdio.h>
#define N 8

void selection(int a[], int n);
void swap( int *x, int *y);

main()
{
  int a[N]={7,3,66,3,-5,22,-77,2}, i;

  selection(a,N);
  
  for (i=0;i<N;i++)
   printf("%d ", a[i]);

}

void selection(int a[], int n)
{
  int i, j, current_max_index;

  for(j = n-1; j > 0; j--)
    {    
      current_max_index = 0;
      
      for ( i=0; i< j+1 ; i++)
	if ( a[i] > a[current_max_index] )
	  current_max_index = i; 

      swap( &a[current_max_index], &a[j]);
    }

}

void swap( int *x, int *y)
{
  int tmp;
  
  tmp = *x;
  *x = *y;
  *y = tmp;
}
