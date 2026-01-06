/*
  Declaration of the print_message() function.  This file (hello2.h)
  would be included by any module using print_message().  Note that
  "extern" is not strictly speaking required in this case, but its use
  makes clear the nature of the declaration. -- djh
*/

extern void print_message(const char *message);
