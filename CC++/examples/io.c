/*
  Read a line of input from the terminal and convert/print the integer
  portion of that input if possible, otherwise print error message.
  Same as example I/O code supplied as part of programming assignment
  #1. -- djh
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BUFSIZE 80

int main(void)
{
  int ret = 0;
  long number;
  char buffer[BUFSIZE], *ptr = (char *) NULL;

  if (fgets(buffer, BUFSIZE, stdin) != (char *) NULL)
    if (!(number = strtol(buffer, &ptr, 10)) && ptr == buffer) {
      (void) fprintf(stderr, "invalid input: %s\n", buffer);
      ret = 1;
    } else
      (void) printf("%ld\n", number);
  else if (ferror(stdin)) {
    perror("fgets");
    ret = 2;
  }
  return ret;
}
