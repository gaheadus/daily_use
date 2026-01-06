/*
  Functionality equivalent to temps3.c but using the more readable and
  maintainable convention of specifying constant values with #define.
  Note that these are not like constants in the Java sense; #define is
  a C preprocessor directive, such that, prior to compilation all
  occurrences of #defined tokens will be replaced by their definition,
  e.g., in the code below LOWER will be replaced by 0, UPPER by 300,
  and so on.  The convention in C programming style is that variables
  use lower case, while #defines use upper case.  Also note that there
  is no semicolon after the #define directives; if there were, this
  would become part of the preprocessor substitution. -- djh
*/

#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main(int argc, char *argv[])
{
  float fahr;

  for (fahr = LOWER ; fahr <= UPPER ; fahr = fahr + STEP)
    (void) printf("%3.0f\t%6.1f\n", fahr, 5.0/9.0 * (fahr - 32.0));
  return 0;
}
