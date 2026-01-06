#include <stdio.h>
#include <string.h>

#define N 2   /* defines the number of employees */ 

typedef struct
{
        int age;
        float salary;
        char * fName;
        char * lName;
}employee;

/* the functions are now passed pointers the structure rather than the 
   structure itself. So the functions PrintInfo and RaiseSal are passed a 
   memory address not the value of a variable */

void PrintInfo ( employee *emp);
void RaiseSal  (employee *emp);

main()
{
   /* Create an array of size N and of type employee */
   employee emp_list[N] = { {24,100000.00, "Jack", "Hill"}, 
                            {25,200000.00, "Jill", "Hill"} 
                          };   
   int i;

   for (i=0;i<N;i++)
     {
       PrintInfo( &emp_list[i] ); /* PrintInfo called with argument the memory
				     address of emp_list[i] */  
       RaiseSal( &(emp_list[i]) ); /* ditto RaiseSal */
       PrintInfo( &emp_list[i] ); /* Printinfo again to see any changes */

     }    /* end of loop over i*/
}

void PrintInfo( employee *emp )
{
  /* now to print out the info. about emp_list[i] we use the pointer to the 
     structure, called emp: emp->fName is the same as (*emp).fName and *emp is
     the value of the variable of which emp is the address ie. it is 
     emp_list[i] therefore (*emp).fName is just emp_list[i].fName */

  printf("%s %s is %d years old.", emp->fName, emp->lName, emp->age);
  printf("\n%s's salary is %.2f.\n", emp->lName, emp->salary);

}

void RaiseSal(employee *emp)
{
 /* the same comments about pointers, as in PrintInfo apply here. 
    also this function is now declared as "void" ... this is because we have 
    not copied a structure to the function and we are not copying one out.
    the statement below is equivalent to (*emp).salary *=1.5 which means
    ( emp_list[i] ).salary is multiplied by 1.5.
    so we accomplish the change to emp_list[i].salary by "reference" rather 
    than by passing its value to the function.				   */

  emp->salary *= 1.5;
}

