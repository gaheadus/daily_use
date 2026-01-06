/*
  Same fuctionality as count_char.c, but uses a for loop instead of a
  while, for compactness.  Note that all of the I/O and computation
  work is done in the for loop expressions, hence the null statement
  (single semicolon) for the body of the loop.  This program uses a
  double as the counter to increase size of input characters which may
  be counted.  Note the formatting string for the counter variable in
  the printf(). -- djh
*/

#include <stdio.h>

int main(void)
{
  double nc;

  for (nc = 0 ; getchar() != EOF ; ++nc)
    ;				/* null statement in C */
  (void) printf("%.0f\n", nc);
  return 0;
}
