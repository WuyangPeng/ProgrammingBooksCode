/*********************************************************************

  Filename:  forloop.cpp
  Section:   9.6    For statements
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Demonstrate for statements with simple examples

#include <iostream.h>
#include <math.h>
#include <ctype.h>

main()
{
   int     i, sum, n, factorial;
   double  x;
   char    c;

   //for statement
   cout << "\n\n*****  For statement";
   cout << "\nSum of 55 and 11";
   sum = 0;
   for (i = 1; i <= 10; ++i)
      sum += i;
   cout << "\nSum = " << sum << "  I = " << i;

   n = 5;
   for (factorial = n, i = n - 1; i >= 1; --i)
   factorial *= i;
   cout << "\nFactorial on 5 = " << factorial << endl;


   // for statement with break
   cout << "\n\n*****  For statement with break";
   cout << "\nInput 10 numbers for square root but break if negative\n";

   for (i = 0; i < 10; ++i) {
      cin >> x;
      if (x < 0.0) {
         cout << "All done" << endl;
         break;        // exit loop if value is negative
      }
      cout << sqrt(x) << endl;
   }
   // break jumps to here


   //For statement with continue
   cout << "\n\n*****  For statement with continue";
   cout << "\nEnter 10 chars in one string and count non-digits\n";
   for (i = 0; i < 10; ++i) {
      cin.get(c);
      if (isdigit(c))
         continue;
       // process other characters
      cout << "\nNon-digit encountered: " << c;   // process other characters
   // continue jumps to here
   }
}
