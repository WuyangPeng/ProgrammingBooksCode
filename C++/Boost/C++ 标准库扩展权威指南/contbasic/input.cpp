#include <iostream>
using std::cout;

template <class Iter>
Iter maximum(Iter first, Iter last)
  { // algorithm to find maximum value in nonempty sequence
  Iter res = first++;
  while (first != last)
    { // check current element
    if (*res < *first)
      res = first;
    ++first;
    }
  return res;
  }

int main()
  { // demonstrate use of input sequence
  const int NVALS = 6;
  int values[NVALS] = { 3, 1, 9, 4, 5, 7 };
  cout << "maximum: " <<
    *maximum(values, values + NVALS) << '\n';
  return 0;
  }