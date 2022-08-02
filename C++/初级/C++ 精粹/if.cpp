/*********************************************************************

  Filename:  if.cpp
  Section:   9.3    The if and if-else statments
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Demonstrate if statements with simple examples

#include <iostream.h>

main()
{
   int    temperature = 35;

   //if statement
   cout << "\n\n*****  If statement";
   cout << "\n Next line should have above freezing temp of 35\n";
   if (temperature >= 32)
      cout << "Above Freezing!\n";
   cout << "Fahrenheit is " << temperature << endl;

   // if else statement
   cout << "\n\n*****  If Else";
   if (temperature >= 32)
      cout << "Above Freezing!\n";
   else if (temperature >= 212)
      cout << "Above Boiling!\n";
   else
      cout << "Boy it's cold " << temperature << endl;
}

