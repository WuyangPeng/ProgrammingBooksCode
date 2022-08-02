#include <array>
#include <algorithm>
#include <iostream>
using std::cout; using std::sort;
using std::tr1::array;

template <class Container>
void do_sort(Container& values)
  { // sort contents of array
  sort(values.begin(), values.end());
  }

int main()
  { // demonstrate use C-style array as STL sequence
  const int ELEMS = 6;
  array<int, ELEMS> values = { 3, 1, 4, 2, 9, 8 };
  for (int i = 0; i < ELEMS; ++i)
    cout << values[i] << ' ';
  cout << '\n';
  do_sort(values);
  for (int i = 0; i < ELEMS; ++i)
    cout << values[i] << ' ';
  cout << '\n';
  return 0;
  }
