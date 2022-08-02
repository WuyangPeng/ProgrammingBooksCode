// Ex2_06.cpp
// Exercising the comma operator
#include <iostream>

using std::cout;
using std::endl;

int main()
{
  long num1 {}, num2 {}, num3 {}, num4 {};

   num4 = (num1 = 10L, num2 = 20L, num3 = 30L);
   cout << endl
        << "The value of a series of expressions "
        << "is the value of the rightmost: "
        << num4;
   cout << endl;

   return 0;
}
