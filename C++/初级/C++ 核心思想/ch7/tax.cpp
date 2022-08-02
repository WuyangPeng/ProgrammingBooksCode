#include <iostream>
#include <string>

using namespace std;

int main()
{  
   const double SINGLE_LEVEL1 = 21450.00;
   const double SINGLE_LEVEL2 = 51900.00;

   const double SINGLE_TAX1 = 3217.50;
   const double SINGLE_TAX2 = 11743.50;

   const double MARRIED_LEVEL1 = 35800.00;
   const double MARRIED_LEVEL2 = 86500.00;

   const double MARRIED_TAX1 = 5370.00;
   const double MARRIED_TAX2 = 19566.00;

   const double RATE1 = 0.15;
   const double RATE2 = 0.28;
   const double RATE3 = 0.31;

   double income;
   double tax;

   cout << "Please enter your income: ";
   cin >> income;

   cout << "Please enter s for single, m for married: ";
   string marital_status;
   cin >> marital_status;

   if (marital_status == "s")
   {  
      if (income <= SINGLE_LEVEL1)
         tax =  RATE1 * income;
      else if (income <= SINGLE_LEVEL2)
         tax = SINGLE_TAX1 
            + RATE2 * (income - SINGLE_LEVEL1);
      else
         tax = SINGLE_TAX2 
            + RATE3 * (income - SINGLE_LEVEL2);
   }
   else
   {  
      if (income <= MARRIED_LEVEL1)
         tax =  RATE1 * income;
      else if (income <= MARRIED_LEVEL2)
         tax = MARRIED_TAX1 
            + RATE2 * (income - MARRIED_LEVEL1);
      else
         tax = MARRIED_TAX2 
            + RATE3 * (income - MARRIED_LEVEL2);
   }
   cout << "The tax is $" << tax << "\n";
   return 0;
}

