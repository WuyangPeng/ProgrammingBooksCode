/*********************************************************************

  Filename:  newtyp.cpp
  Section:   6      Types
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Types  newtyp.cpp
//Special conversions to char* (how about string--2nd program)

#include <iostream>
#include <iomanip.h>
//Print bool value as true, false not 1, 0
inline char* pr_bool(bool b)
{
   if (b)
      return  "true\t";
   else
      return "false\t";
}
//Prints wchar_t as 2 characters assumption sizeof = 2
inline char* pr_wchar_t(wchar_t b)
{

   char *c = new char[3];
   c[0] = b;
   c[1] = (b >> 8);
   c[2] = 0;
   return c;
}

int main()
{
   unsigned int k = 99;
   char c = '\t';
   bool flag = true;
   wchar_t  wc = L'ab';
   cout << "size of wchar_t = " << sizeof(wc) <<endl;  //2 bytes
   long double x = 1.234567890123456789L;
   double y = x;
   float z = y;
   cout << setprecision(20) << z << endl;
   cout << y << endl;
   cout << x << endl;
   cout << k << c << endl;
   cout << wc << endl;
   cout << pr_wchar_t(wc) << endl;
   cout << flag << !flag << endl;
   cout << pr_bool(flag) << pr_bool(!flag) << endl;

}
