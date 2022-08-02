#include <string>
#include <iostream>

using namespace std;

#include "ccc_empl.h"

/**
   A department in an organization.
*/
class Department
{
public:
   Department(string n);
   Department(string n, Employee e);
   ~Department();
   Department& operator=(const Department& b);
   Department(const Department& b);
   void print() const;
private:
   string name;
   Employee* receptionist;
};

/**
   Constructs a department with a given name and no receptionist.
   @param n the department name
*/
Department::Department(string n)
{
   name = n;
   receptionist = NULL;

   cout << "Constructor: ";
   print();
}

/**
   Constructs a department with a given name and receptionist.
   @param n the department name
   @param e the receptionist
*/
Department::Department(string n, Employee e)
{
   name = n;
   receptionist = new Employee(e.get_name(), e.get_salary());
   
   cout << "Constructor: ";
   print();
}

/**
   Deletes the Employee object that this Department
   object manages.
*/
Department::~Department()
{
   cout << "Destructor: ";
   print();

   delete receptionist; 
}

/**
   Constructs a Department object as a copy of another
   Department object.
   @param b the object to copy
*/
Department::Department(const Department& b)
{
   cout << "Copy constructor: ";
   b.print();

   name = b.name;
   if (b.receptionist == NULL)
      receptionist = NULL;
   else
      receptionist = new Employee(b.receptionist->get_name(),
         b.receptionist->get_salary());
}

/**
   Sets this Department object to a copy of another
   Department object.
   @param b the object to copy
*/
Department& Department::operator=(const Department& b)
{
   cout << "Assignment: ";
   print();
   cout << "= ";
   b.print();
   
   if (this != & b)
   {
      name = b.name;
      delete receptionist;
      if (b.receptionist == NULL)
         receptionist = NULL;
      else
         receptionist = new Employee(b.receptionist->get_name(),
            b.receptionist->get_salary());
   }
   return *this;
}

/**
   Prints a description of this department.
*/
void Department::print() const
{
   cout << "[name=" << name << ",receptionist=";
   if (receptionist == NULL)
      cout << "NULL";
   else
      cout << receptionist->get_name();
   cout << "]\n";
}

int main()
{
   Department shipping("Shipping");
   Department qc("Quality Control", 
      Employee("Tester, Tina", 50000));
   Department dept(qc); 
   dept = shipping;
   return 0;
}



