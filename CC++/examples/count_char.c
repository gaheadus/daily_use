/*
  Count the number of input characters.  Works from stdin (i.e.,
  terminal input), but can also count characters in a file using shell
  redirection.  Output should match that of 'wc -c' in Unix. -- djh
*/

#include <stdio.h>

int main(void)
{
  long nc = 0;			/* declare and initialize counter variable */

  while (getchar() != EOF)	/* get characters and increment counter */
    ++nc;			/* until end of file is detected */
  (void) printf("%ld\n", nc);
  return 0;
}
