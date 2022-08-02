/*********************************************************************

  Filename:  while.cpp
  Section:   9.4    The While Statement
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Demonstrate while statements with simple examples

#include <iostream.h>

main()
{

   int    i, sum;

   //while statement
   cout << "\n\n*****  While";
   cout << "\nSum of 55 and 11\n";
   i = 1;
   sum = 0;

   while (i <= 10) {
      sum += i;
      ++i;
   }

   cout << "\nSum = " << sum << "  I = " << i;
 }
