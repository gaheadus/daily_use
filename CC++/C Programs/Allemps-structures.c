/* Program using structures to store and manipulate information about 
   employee(s) of a company. */

#include <stdio.h>
#include <string.h>

#define N 2                    /* defines the number of employees */ 

typedef struct
{
        int age;
        float salary;
        char *fName;
        char *lName;
}employee;

void PrintInfo ( employee );
employee RaiseSal (employee );

main()
{

/* Create an array of size N and of type employee 
   and initialise it ie give values to the members of the structure. 
*/
  employee emp_list[N] = { {24,100000.00, "Jack", "Hill"}, 
                            {25,200000.00, "Jill", "Hill"} 
                          };

  int i;

/* see notes for more about initialising structures.
   If a new employee is hired you simply change N -> N+1 and add their details
   ie. age etc. to the end of the arrays above. 

   3 function calls - each is passed the variable employee emp_list[i], 
   corresponding to a different employee for each i (with its assigned values)
*/

  for (i=0;i<N;i++)
    {
      PrintInfo( emp_list[i] );
      emp_list[i] = RaiseSal( emp_list[i] );
      PrintInfo( emp_list[i] );

    }    /* end of loop over i*/

}

void PrintInfo( employee emp )
{
  printf("%s %s is %d years old.", emp.fName, emp.lName, emp.age);
  printf("\n%s's salary is %.2f.\n", emp.lName, emp.salary);

/* the .2 in the 2nd print statement just specifies how many decimal places 
   in the output 
*/

}

employee RaiseSal( employee emp )
{
  emp.salary *= 1.5;
  return emp;
}

