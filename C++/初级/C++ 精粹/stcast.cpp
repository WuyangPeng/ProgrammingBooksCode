/*********************************************************************

  Filename:  stcast.cpp
  Section:   15.5   Casts
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>

enum peer {king, princess, earl} a;
enum animal {horse, frog, snake} b;

int main()
{
	a = king;
	b = horse;
	cout << "\nThis should print 00 then 10 then " << endl;
	cout << a << b << endl;
   a = static_cast<peer>(frog);
   cout << a << b << endl;
}
