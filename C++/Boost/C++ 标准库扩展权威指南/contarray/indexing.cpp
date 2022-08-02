#include <array>
#include <iostream>
using std::tr1::array;
using std::cin; using std::cout;

const int ELEMS = 10;
array<int, ELEMS> squares = { 0, 1, 4, 9, 16,
  25, 36, 49, 64, 81 };

int main()
  { // demonstrate array indexing
  int idx = -1;
  while (idx < 0 || ELEMS <= idx)
    { // check index value before using
    cout << "Value to square: ";
    cin >> idx;
    }
  cout << idx << " squared is "
    << squares[idx] << "\n\n";

  // no check needed:
  for (idx = 0; idx < ELEMS; ++idx)
    cout << idx << " squared is "
      << squares[idx] << '\n';
  return 0;
  }