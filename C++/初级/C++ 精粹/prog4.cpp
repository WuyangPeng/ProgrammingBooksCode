/*********************************************************************

  Filename:  prog4.cpp
  Section:   5      Linkage Rules
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

// The following programs work together: prog1, prog2, prog3, prog4
// to show linkage
#include <iostream.h>

char c;           //illegal second definition
extern float n;   //illegal type mismatch
extern int k;     //illegal no definition

int main ()
{
   cout << "Dummy program to show linkage errors" << endl;
}


