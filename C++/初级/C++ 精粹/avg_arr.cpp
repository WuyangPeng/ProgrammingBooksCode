/*********************************************************************

  Filename:  avg_arr.cpp
  Section:   10.5   Overloading
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//Overload average array functions for doubles and ints
//  Title: avg_array

#include <iostream.h>

double avg_arr(const int a[], int size)
{
   int  sum = 0;

   for (int i = 0; i < size; ++i)
      sum += a[i];                   //int arithmetic
   return (static_cast<double>(sum)/ size);
}

double avg_arr(const double a[], int size)
{
   double  sum = 0.0;

   for (int i = 0; i < size; ++i)
      sum += a[i];      //double arithmetic
   return (sum / size);
}



int main()
{
   int    w[5] = {1, 2, 3, 4, 5};
   double x[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

   cout << avg_arr(w, 5) << "  int array average\n";
   cout << avg_arr(x, 5) << "  double array average\n";
}
