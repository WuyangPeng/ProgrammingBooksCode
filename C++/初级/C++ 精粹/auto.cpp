/*********************************************************************

  Filename:  auto.cpp
  Section:   8.2    Autoincrement and Autodecrement Expressions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Demonstrate auto increment and decrement with simple examples

#include <iostream.h>

int main()
{
   int    i, j;

   //pre and post fix increments
   cout << "\n\n*****  Pre and Post fix";
   cout << "\nJ should be 1, 1, then I should be 2 and undetermined\n";
   i = 0;
   j = ++i;
   cout << "\nJ = " << j;
   j = i++;
   cout << "\nJ = " << j << "\nI = " << i;
   i = ++i + i++;  // hazardous practice that is system dependent
   cout << "\nI = " << i;
}
