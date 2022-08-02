#include <iostream>
#include <cmath>

using namespace std;

double future_value(double p)
{  
   double b = 1000 * pow(1 + p / 100, 10);
   return b;
}

int main()
{  
   cout << "Please enter the interest rate in percent: ";
   double rate;
   cin >> rate;

   double balance = future_value(rate);
   cout << "After 10 years, the balance is " 
      << balance << "\n";

   return 0;
}
