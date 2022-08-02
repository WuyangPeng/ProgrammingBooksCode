// Soln7_01.cpp

#include <iostream>                   // For stream input/output

using std::cout;
using std::endl;

struct Sample
{
   int one;
   int two;
};

int main()
{
   Sample a;
   Sample b;

   a.one = 1;
   a.two = 2;
   b.one = b.two = 9999;

   cout << "a=(" << a.one << "," << a.two << ")" << endl;

   // b contains values 9999
   cout << "b=(" << b.one << "," << b.two << ")" << endl;

   b = a;
   cout << "After assigning a to b:" << endl;
   cout << "b=(" << b.one << "," << b.two << ")" << endl;

   return 0;
}
