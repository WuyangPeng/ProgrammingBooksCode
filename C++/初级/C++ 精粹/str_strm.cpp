/*********************************************************************

  Filename:  str_strm.cpp
  Section:   16.6   Using Strings and Streams
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <strstrea.h>

int main ()
{

   char name[15];
   int total;
   char* scores[4] = {"Dave 2","Ida 5","Jim 4","Ira 8" };
   istrstream ist(scores[3]);//p points to string

   ist >> name >> total;    //name: Ira , total = 8
   cout << name << "  " << total << endl;
}
