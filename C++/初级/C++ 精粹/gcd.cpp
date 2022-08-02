/*********************************************************************

  Filename:  gcd.cpp
  Section:   1      Program Structure
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Compute the greatest common divisor of two integers
//Author: Laura Pohl. version 2.
//Organization: Cottage Consultants, Aptos, CA

#include<iostream.h>  //input/output library
#include <assert.h>   //assertion macro to test conditions

int gcd(int m, int n) //function definition
{                     //block
   int r;             //declaration of remainder

   while (n != 0) {   //not equal
      r = m % n ;     //modulos operator
      m = n;          //assignment
      n = r;
   }                  //end while loop
   return  m;         //exit gcd with value m
}

int main()
{
   int g, x, y;

   cout << "\nGreatest Common Divisor";
   cout << "\nEnter two non-zero integers: ";
   cin >> x >> y; //input two integers
   while(x * y != 0){
      cout << "\nGCD(" << x << ", " << y << ") = "
           << (g = gcd(x, y)) << endl;
      assert(x % g == 0 && y % g ==0);//postcondition
      cout << "\nEnter two integers: ";
      cin >> x >> y; //input two integers
   }
}
