// Soln5_1.cpp
#include <iostream>

// Recursive factorial function
long fact(long n)
{
  // If n is 1 return it, otherwise return n*fact(n-1)
  return n == 1L ? 1L : n*fact(n - 1L);
}

int main()
{
  for (long value{ 2L }; value < 10L; ++value)
    std::cout << value << "! = " << fact(value) << std::endl;
}
