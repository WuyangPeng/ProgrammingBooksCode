/*********************************************************************

  Filename:  lval.cpp
  Section:   8.9    Address and Indirection Expressions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//lval.cpp  illustrating simple lvalue rvalue relations

#include<iostream>
int main()
{
   int    a = 5;      //declaration of a
   int*   p = &a;     //p points to a
   int&   ref_a = a;  //alias for a

   cout << "address of(lvalue) a = " << p << endl;
   cout << "address of ref_a = " << &ref_a << endl;
   cout << "rvalue of a = " << *p << endl;
   *p += a;  //same as *p += *p;
   cout << "rvalue of a = " << ref_a << endl;
   int i; cin >> i;
}
