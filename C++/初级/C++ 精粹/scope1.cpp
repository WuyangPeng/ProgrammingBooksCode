/*********************************************************************

  Filename:  scope1.cpp
  Section:   4      Declarations and Scope Rules
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//  ::  scope resolution operator
//  Title: scope_operator

#include <iostream.h>

int i = 1;           // external i

void foo(int i)     //parameter i
{
   cout << i  << " foo i <> ::i  " << ::i << "\n";
   i = ::i;        //parameter i is assigned external i
   cout << i  << " foo i <> ::i  " << ::i << "\n";
}


int main()
{
   int   i = 2;         //redeclares i locally

   {
       cout << "enter inner block\n";
       int  n = i;      //the global i is still visible
       int  i = 3;      //hides both the global i and external i

       /// print the local i and external i
       cout << i  << "  i <> ::i  " << ::i << "\n";
       cout << "n = " << n << "\n";
   }
   cout << "enter outer block\n";
   cout << i  << "  i <> ::i  " << ::i << "\n";
   foo(5);
}
