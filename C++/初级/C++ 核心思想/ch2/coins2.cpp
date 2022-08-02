#include <iostream>

using namespace std;

int main()
{  
   cout << "How many pennies do you have? ";
   int pennies;
   cin >> pennies;
   
   cout << "How many nickels do you have? ";
   int nickels;
   cin >> nickels;
   
   cout << "How many dimes do you have? ";
   int dimes;
   cin >> dimes;
   
   cout << "How many quarters do you have? ";
   int quarters;
   cin >> quarters;
   
   double total = pennies * 0.01 + nickels * 0.05 
      + dimes * 0.10 + quarters * 0.25;
      /* total value of the coins */

   cout << "Total value = " << total << "\n";

   return 0;
}
