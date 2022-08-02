#include <iostream>
#include <vector>

using namespace std;

#include "ccc_empl.cpp"

/** 
   Finds an employee in a sorted vector.
   @param v the sorted vector with the employees to search
   @param from the start of the range to search
   @param to the end of the range to search
   @param n the employee name to search for
   @return the index of the first match, or -1 if not found
*/
int binary_search(vector<Employee> v, int from, int to, string n)
{  
   if (from > to)
      return -1;
   int mid = (from + to) / 2;
   if (v[mid].get_name() == n)
      return mid;
   else if (v[mid].get_name() < n)
      return binary_search(v, mid + 1, to, n);
   else
      return binary_search(v, from, mid - 1, n);
}

int main()
{  
   vector<Employee> staff(5);
   staff[0] = Employee("Cracker, Carl", 48000.0);
   staff[1] = Employee("Hacker, Harry", 35000.0);
   staff[2] = Employee("Lam, Larry", 78000.0);
   staff[3] = Employee("Reindeer, Rudolf", 63000.0);
   staff[4] = Employee("Sandman, Susan", 51500.0);

   cout << "Enter name of employee to search for: ";
   string name;
   getline(cin, name);

   int i = binary_search(staff, 0, staff.size() - 1, name);

   if (i >= 0)
      cout << staff[i].get_name() << " "
         << staff[i].get_salary() << "\n";
   else
      cout << "Not found.\n";

   return 0;
}

