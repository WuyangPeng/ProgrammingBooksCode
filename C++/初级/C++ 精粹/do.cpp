/*********************************************************************

  Filename:  do.cpp
  Section:   9.6    The Do Statement
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Demonstrate do statements with simple examples

#include <iostream.h>

main()
{

   int    i, sum;

   //while statement
   //do statement
   cout << "\n\n*****  Do Statement";
   cout << "\nEnter numbers as long as number > 0 and sum them\n";
   i = 0;
   sum = 0;

   do {
      sum += i;
      cin >> i;
   } while (i > 0);
   cout << "\nSum of input numbers is " << sum;
}
