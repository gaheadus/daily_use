/*
  A simple program to demonstrate how to access the command line
  arguments to a C program.  When a C program is called from the Unix
  command line, argc is set to the number of command line arguments
  (the name of the program counts as an argument, thus argc is always
  at least 1), while argv is an array of character pointers (i.e.,
  strings, in this case) to each of the command line args.  Thus, if
  the program were called as './command_args hello world', argv[0]
  would be "./command_args", argv[1] "hello", and argv[2] "world".
  Note that the main function in a C program may take only zero (i.e.,
  void) or two (i.e., argc and argv) arguments. -- djh
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  int index;
  for (index = 0 ; index < argc ; index++)
    (void) printf("argv[%d] = %s\n", index, argv[index]);
  return 0;
}
