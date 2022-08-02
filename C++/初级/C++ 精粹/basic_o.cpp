/*********************************************************************

  Filename:  basic_o.cpp
  Section:   16.1   Formatted Output and iomanip.h
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>

int main()
{

   char* str = "ABCDEFGHI";
   int  i = 8, j = 9, x;

   cout.put('A');               //output A
   cout.write(str + 2, 3);      //output CDE
   cout.flush();      //write contents of buffered stream   int c = 'A';

   cout << endl;
   cout << i << j ;               //confused: prints 89
   cout << i << "   " << j;       //better: prints 8   9
   cout << "i= " << i << " j= " << j;  //best: i= 8 j= 9
   cout << endl;
   x = 1;
   cout << "x = " << x << endl;
   cout << "x = " << x << flush;
}
