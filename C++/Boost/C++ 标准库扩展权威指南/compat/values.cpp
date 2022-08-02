#include <stdlib.h>
#include <iostream>
using std::cout;

int main()
  { // show range limits
  cout << "_Longlong can hold values in the range\n\t["
    << LLONG_MIN << ',' << LLONG_MAX << "]\n";
  cout << "_ULonglong can hold values in the range\n\t["
    << 0 << ',' << ULLONG_MAX << "]\n";
  return 0;
  }
