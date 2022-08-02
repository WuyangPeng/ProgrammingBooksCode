// Ex3_09.cpp
// Using multiple counters to show powers of 2
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

int main()
{
  const long max { 10L };

  for (long i {}, power { 1L }; i <= max; i++, power += power)
      cout << endl
           << setw(10) << i << setw(10) << power;     // Loop statement

   cout << endl;
   return 0;
}
