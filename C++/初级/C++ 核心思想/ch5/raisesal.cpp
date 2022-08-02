#include <iostream>

using namespace std;

#include "ccc_empl.cpp"

/**
   Raise an employee salary 
   @param e employee receiving raise
   @param by the percentage of the raise
*/
void raise_salary(Employee& e, double by)
{  
   double new_salary = e.get_salary() * (1 + by / 100);
   e.set_salary(new_salary);
}

int main()
{  
   Employee harry("Hacker, Harry", 45000.00);
   raise_salary(harry, 5);
   cout << "New salary: " << harry.get_salary() << "\n";
   return 0;
}
