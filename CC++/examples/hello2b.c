/*
  Definition of the print_message() function removed from the hello.c
  file and placed into a separate file.  While in Java there is a
  direct relationship between the name of a class and the file
  containing the code for that class, C doesn't have this restriction.
  In other words, C does not enforce any relationship between the
  names of functions and variables and the names of the modules
  (files) tat contain them.  Nevertheless, it is good (and common)
  practice to group functionality into separate files as a way of
  indicating the programmer's design intentions for the logical
  structure of a program or system of programs.  This also speeds
  development time in that it aids in multiple developers working on
  the same code base as well as dividing the code base into separate
  compilation units. -- djh
*/

#include <stdio.h>

void print_message(const char *message)
{
  (void) printf("%s", message);
}
