#include <array>
#include <algorithm>
#include <iostream>
#include <iterator>
using std::tr1::array;
using std::sort;
using std::cout; using std::copy;
using std::ostream_iterator;

const int ELEMS = 6;

int main()
  { // demonstrate use of begin and end to designate range
  array<int, ELEMS> values = { 3, 1, 4, 2, 9, 8 };
  copy(values.begin(), values.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  sort(values.begin(), values.end());
  copy(values.begin(), values.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  return 0;
  }
