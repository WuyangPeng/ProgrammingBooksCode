/*********************************************************************

  Filename:  stats.cpp
  Section:   10     Functions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>

//stats finds a data sets average, max and min.

//stats finds a data sets average, max and min.
double stats(const double data[],   //data input
             int size,
             double& max,        //maximum element found
             double& min)        //minimum element
{
   double sum = max = min = data[0];

   for (int i = 1; i < size; ++i) {
      sum += data[i];
      if (data[i] > max)
         max = data[i];
      else if (data[i] < min)
         min = data[i];
   }
   return sum/size;
}


int main()
{
   double x[7] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
   double max, min;

   cout << " avg is " << stats(x, 5, max, min);
   cout << "   max is "  << max << "   min is " << min << endl;

   cout << "avg is " << stats(x, 3, max, min);
   cout << "   max is "  << max << "   min is " << min << endl;
}
