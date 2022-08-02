#include <array>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <iostream>
using std::tr1::array;
using std::basic_ostream; using std::cout;
using std::copy; using std::ostream_iterator;

int main()
  { // demonstrate copying
  cout << "Original array: ";
  array<int, 6> arr0 = { 1, 1, 2, 3, 5, 8 };
  copy(arr0.begin(), arr0.end(),
    ostream_iterator<int>(cout, " "));
  cout << "\n  Copied array: ";
  array<int, 6> arr1 = arr0;
  copy(arr1.begin(), arr1.end(),
    ostream_iterator<int>(cout, " "));
  cout << "\n     New array: ";
  array<int, 6> arr2 = {};
  copy(arr2.begin(), arr2.end(),
    ostream_iterator<int>(cout, " "));
  cout << "\n    After copy: ";
  arr2 = arr0;
  copy(arr2.begin(), arr2.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  return 0;
  }