/*
  Copies stdin (i.e., terminal input) to stdout (i.e., terminal
  output) a character at a time.  Will also operate on files using
  shell redirection under Unix. -- djh
*/

#include <stdio.h>

int main(void)
{
  int c;			/* getchar() returns a value of type
				   int */
  c = getchar();
  while (c != EOF) {		/* until EOF write the current */
    putchar(c);			/* character and read a new one */
    c = getchar();
  }
  return 0;
}
