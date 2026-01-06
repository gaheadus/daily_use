/*
  Exactly the same functionality as hello.c except that the function
  declaration and definition are divided into separate files.  Note
  the inclusion of hello2.h in order to get the function prototype for
  print_message(). -- djh
*/

#include "stdio.h"
#include "hello2.h"

int main(void)
{
  if (getc(stdin) == 'y')
    print_message("Hello world\n");
  else
    print_message("Goodbye world\n");
  return 0;
}
