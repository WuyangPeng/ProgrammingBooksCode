// Ex6_07.cpp
// Using overloaded functions
#include <iostream>
using std::cout;
using std::endl;
        
int max(const int data[],const size_t len);               // Prototypes for
long max(const long data[],const size_t len);             // a set of overloaded
double max(const double data[],const size_t len);         // functions
        
int main()
{
   int small[] {1, 24, 34, 22};
   long medium[] {23, 245, 123, 1, 234, 2345};
   double large[] {23.0, 1.4, 2.456, 345.5, 12.0, 21.0};

   const size_t lensmall { _countof(small) };
   const size_t lenmedium{ _countof(medium) };
   const size_t lenlarge{ _countof(large) };

   cout << endl << max(small, lensmall);
   cout << endl << max(medium, lenmedium);
   cout << endl << max(large, lenlarge);
        
   cout << endl;
   return 0;
}
        
// Maximum of ints
int max(const int x[],const size_t len)
{
  int maximum { x[0] };
  for (size_t i { 1 }; i < len; i++)
      if(maximum < x[i])
         maximum = x[i];
   return maximum;
}
        
// Maximum of longs
long max(const long x[], const size_t len)
{
  long maximum { x[0] };
  for (size_t i{ 1 }; i < len; i++)
      if(maximum < x[i])
         maximum = x[i];
   return maximum;
}
        
// Maximum of doubles
double max(const double x[], const size_t len)
{
  double maximum { x[0] };
  for (size_t i{ 1 }; i < len; i++)
      if(maximum < x[i])
         maximum = x[i];
   return maximum;
}
