/*********************************************************************

  Filename:  for_scop.cpp
  Section:   4      Declarations and Scope Rules
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//For scope current rules
//Print averages of random number generation

#include <iostream>
#include <stdlib.h>
const int N = 100;

int main()
{
   int a[N];
   int b[N][N];
   double sum = 0.0;

   for (int i = 0; i < N; ++i) {  //scope of i
      a[i] = rand();
      sum += a[i];
   }                              //i out of scope
   cout << "average rand() is " << sum/N << endl;
   sum = 0.0;
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) {
         b[i][j] = rand();
         sum += b[i][j];
      }
   cout << "average rand() is " << sum/(N * N) << endl;
}
