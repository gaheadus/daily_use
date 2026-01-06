/*
  Variant on filecopy.c, but with the input now imbedded in the test
  portion of the while loop.  Note the use of parentheses around the
  assignement from getchar() to the variable c.  This is necessary
  because the operator precedence of assignment (=) is less than that
  of inequality (!=). -- djh
*/

#include <stdio.h>

int main(void)
{
  int c;

  while ((c = getchar()) != EOF)
    putchar(c);
  return 0;
}
