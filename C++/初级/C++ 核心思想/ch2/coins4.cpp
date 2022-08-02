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

   int value = pennies + 5 * nickels + 10 * dimes 
      + 25 * quarters;
   int dollar = value / 100;
   int cents = value % 100;

   cout << "Total value = " << dollar << " dollar and "
      << cents << " cents\n";

   return 0;
}

