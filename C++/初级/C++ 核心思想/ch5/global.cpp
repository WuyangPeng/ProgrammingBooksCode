#include <iostream>
#include <cmath>

using namespace std;

double balance;

/** 
   Accumulates interest in the global variable balance
   @param p the interest rate in percent
   @param n the number of periods the investment is held
*/
void future_value(double p, int n)
{  
   balance = balance * pow(1 + p / 100, n); 
}

int main()
{  
   balance = 10000;
   future_value(5, 10);
   cout << "After ten years, the balance is "
      << balance << "\n";
   return 0;
}
