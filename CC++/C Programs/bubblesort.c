#include <stdio.h>
#define N 8

void bubble(int a[], int n);
void swap( int *x, int *y);

main()
{
  int a[N]={7,3,66,3,-5,22,-77,2}, i;

  bubble(a,N);
  
  for (i=0;i<N;i++)
   printf("%d\n", a[i]);

}

void bubble(int a[], int n)
{
  int i,j;
  for ( i=0;i< n-1; i++)
   for (j=n-1;j>i; j--)
    if ( a[j-1] > a[j] )
     swap( &a[j-1], &a[j]);
}

void swap( int *x, int *y)
{
  int tmp;
  
  tmp = *x;
  *x = *y;
  *y = tmp;
}
