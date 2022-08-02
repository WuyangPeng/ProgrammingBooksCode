/*********************************************************************

  Filename:  basic_i.cpp
  Section:   16.4   The Input Class istream
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//  Title: basic_input

#include <fstream.h>

main()
{
   double x;
   int    i;
   char   c;
   char   s[100];  //max of 99 chars

   cout << "\nEnter one character: ";
   cin.get(c);            //one character

   cout << "\nCharacter is " << c << endl;

   cout << "\nEnter a float and an int: ";
   cin.ignore(100, '\n');      //flush input buffer up to 100 chars to \n
   cin >> x >> i;
   cout << "\nFloat is " << x << "  int is " << i << endl;

   cout << "\nEnter up to 40 character string:\n";
   cin.ignore(100, '\n');          //flush chars out of cin buffer
   cin.get(s, 40);        //length 40 or terminated by '\n'
   cout << "\nString is: " << s;


   cout << "\nEnter a string (will terminate at length 10 or by *):\n";
   cin.ignore(100, '\n');         //flush chars out of cin buffer
   cin.get(s, 10, '*');   //length 10 or terminated by *
   cout << "\nString is: " << s;

   cout << "\nEnter a string (will terminate at length 40 or by \\n" << endl;
   cin.ignore(100,'\n');        //flush chars out of cin buffer
   cin.getline(s, 40);    //same as get but '\n' discarded
   cout << "\nString is: " << s;
   cout << endl;

   cout << "\nEnd of test\n";
}
