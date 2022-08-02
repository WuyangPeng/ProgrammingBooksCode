#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int BALANCES_ROWS = 11;
const int BALANCES_COLS = 6;

const double RATE_MIN = 5;
const double RATE_MAX = 10;
const double RATE_INCR = 
   (RATE_MAX - RATE_MIN) / (BALANCES_ROWS - 1);
const int YEAR_MIN = 5;
const int YEAR_MAX = 30;
const int YEAR_INCR = 
   (YEAR_MAX - YEAR_MIN) / (BALANCES_COLS - 1);


/**
   Prints a table of account balances.
   @param the table to print
   @param table_rows the number of rows in the table.
*/
void print_table(const double table[][BALANCES_COLS], 
   int table_rows)
{  
   const int WIDTH = 10;
   cout << setiosflags(ios::fixed) << setprecision(2);
   for (int i = 0; i < table_rows; i++)
   {  
      for (int j = 0; j < BALANCES_COLS; j++)
         cout << setw(WIDTH) << table[i][j];
      cout << "\n";
   }
}

/**
   Computes the value of an investment with compound interest
   @param initial_balance the initial value of the investment
   @param p the interest rate per period in percent
   @param n the number of periods the investment is held
   @return the balance after n periods
*/
double future_value(double initial_balance, double p, int n)
{
   double b = initial_balance * pow(1 + p / 100, n);
   return b;
}

int main()
{  
   double balances[BALANCES_ROWS][BALANCES_COLS];
   for (int i = 0; i < BALANCES_ROWS; i++)
      for (int j = 0; j < BALANCES_COLS; j++)
         balances[i][j] = future_value(10000, 
            RATE_MIN + i * RATE_INCR,
            YEAR_MIN + j * YEAR_INCR);

   print_table(balances, BALANCES_ROWS);

   return 0;
}
