/*********************************************************************

  Filename:  reinter.cpp
  Section:   15.5   Casts
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>

int main()
{
   int    i, *ptri = &i;
   char*  ptrc;
   void*  gptr;

   i = 66;
   cout << " i = " << i << endl;
   ptrc = reinterpret_cast<char*>(ptri);
   cout << " i cast c =  " << *ptrc << endl;
   gptr = &ptri;      //okay: promotion to void*
   cout << " void* cast to char = " << reinterpret_cast<char*>(&gptr)<< endl;
   cout << " i + 1 via void* pointer = " << i << endl;
   reinterpret_cast<char*>(i) = ptrc;
   cout << " back to i = " << i << endl;
}


