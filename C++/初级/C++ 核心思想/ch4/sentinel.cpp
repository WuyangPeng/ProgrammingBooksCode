#include <iostream>

using namespace std;

int main()
{  
   double sum = 0;
   int count = 0;
   double salary = 0;
   while (salary != -1)
   {  
      cout << "Enter a salary, -1 to finish: ";
      cin >> salary;
      if (salary != -1) 
      {  
         sum = sum + salary;
         count++;
      }
   }
   if (count > 0)
      cout << "Average salary: " << sum / count << "\n";
   return 0;
}
