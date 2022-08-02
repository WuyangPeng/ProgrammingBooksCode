#include <iostream>

using namespace std;

int main()
{  
   double rate = 5;
   double initial_balance = 10000;
   double balance = initial_balance;
   int year = 0;

   while (balance < 2 * initial_balance)
   {  
      balance = balance * (1 + rate / 100);
      year++;
   }

   cout << "The investment doubled after "
      << year << " years.\n";

   return 0;
}
