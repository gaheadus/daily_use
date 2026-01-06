/* Program using structures to store and manipulate information about 
employee(s) of a company. */

#include <stdio.h>
#include <string.h>

typedef struct
{
        int age;
        float salary;
        char *fName;
        char *lName;
}employee;

void PrintInfo ( employee );
employee RaiseSal (employee );

void main()
{
        employee Jill;   /* Jill is a variable of type employee */

/* initialising Jill ie given values to the members of the structure */

        Jill.age = 24;		
        Jill.salary = 100000.00;
        Jill.fName = "Jill" ;
        Jill.lName = "Smith";

/* 3 function calls - each is passed the variable Jill (with its assigned 
   values */

        PrintInfo( Jill );
	Jill = RaiseSal( Jill );
        PrintInfo( Jill );
}

void PrintInfo( employee emp )
{
        printf("%s %s is %d years old.", emp.fName, emp.lName, emp.age);
        printf("\n%s's salary is %.2f.\n", emp.lName, emp.salary);

/* try changing the .2 in the second print statement and see how it affects the output*/

}

employee RaiseSal(employee emp)
{
  emp.salary *= 1.5;
  return emp;
}

