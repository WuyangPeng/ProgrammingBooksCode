#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{  
   const double RATE_MIN = 5;
   const double RATE_MAX = 10;
   const double RATE_INCR = 0.5;
   const int YEAR_MIN = 5;
   const int YEAR_MAX = 30;
   const int YEAR_INCR = 5;

   /* print table header */

   int year;
   cout << " Rate  ";
   for (year = YEAR_MIN; year <= YEAR_MAX; 
        year = year + YEAR_INCR)
   {  
      cout << setw(2) << year << " years  ";
   }
   cout << "\n";

   cout << fixed << setprecision(2);

   double initial_balance = 10000;
   double rate;
   for (rate = RATE_MIN; rate <= RATE_MAX; 
        rate = rate + RATE_INCR)
   {  
      /* print table row */
       cout << setw(5) << rate;
       for (int year = YEAR_MIN; year <= YEAR_MAX;
          year = year + YEAR_INCR)
       {  
          double balance = 
             initial_balance * pow(1 + rate / 100, year);
          cout << setw(10) << balance;
       }
       cout << "\n";
   }

   return 0;
}
