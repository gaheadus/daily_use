/*
  A variant on the "classic" hello world program to demonstrate a
  decision based upon character input and a basic function call.  Note
  the declaration of the parameter of print_message as "const char *".
  While not strictly speaking necessary, this was done to have the
  type of the parameter conform to the type expected as the first
  argument of printf() as declared in stdio.h.  Where possible, it it
  good form to have parameters declared as explicitly as possible in
  order to indicate the intent of the program designer/author. -- djh
*/

#include <stdio.h>

void print_message(const char *message)
{
  (void) printf("%s", message);
}

int main(void)
{
  if (getc(stdin) == 'y')
    print_message("Hello world\n");
  else
    print_message("Goodbye world\n");
  return 0;
}
