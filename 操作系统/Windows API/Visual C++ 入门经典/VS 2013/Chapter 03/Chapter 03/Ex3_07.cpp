// Ex3_07.cpp
// Creating a loop with an if and a goto
#include <iostream>

using std::cout;
using std::endl;

int main()
{
  int i { 1 }, sum {};
  const int max { 10 };

loop:
   sum += i;             // Add current value of i to sum
   if(++i <= max)
      goto loop;         // Go back to loop until i = 11

   cout << endl
        << "sum = " << sum << endl
        << "i = "   << i   << endl;
   return 0;
}
