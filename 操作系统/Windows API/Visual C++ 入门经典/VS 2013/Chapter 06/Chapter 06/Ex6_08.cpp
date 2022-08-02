// Ex6_08.cpp
// Using function templates

#include <iostream>
using std::cout;
using std::endl;

// Template for function to compute the maximum element of an array
template<typename T> T max(const T x[], const size_t len)
{
  T maximum{ x[0] };
  for (size_t i{ 1 }; i < len; i++)
  if (maximum < x[i])
    maximum = x[i];
  return maximum;
}

int main()
{
  int small[] { 1, 24, 34, 22};
  long medium[] { 23, 245, 123, 1, 234, 2345};
  double large[] { 23.0, 1.4, 2.456, 345.5, 12.0, 21.0};

  const size_t lensmall{ _countof(small) };
  const size_t lenmedium{ _countof(medium) };
  const size_t lenlarge{ _countof(large) };

  cout << endl << max(small, lensmall);
  cout << endl << max(medium, lenmedium);
  cout << endl << max(large, lenlarge);

  cout << endl;
  return 0;
}
