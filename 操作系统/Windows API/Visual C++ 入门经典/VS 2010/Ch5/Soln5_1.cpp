// Soln5_1.cpp
#include <iostream>
using std::cout;
using std::endl;

// Recursive factorial function
long fact(long n)
{
  // If n is 1 return it, otherwise return n*fact(n-1)
  return n == 1L ? 1L : n*fact(n-1);
}

int main()
{
  for(long value = 2 ; value<10L ; value++)
    cout << value << "! = " << fact(value) << endl;

  return 0;
}
