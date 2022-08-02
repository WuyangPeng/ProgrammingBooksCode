#include <array>
#include <iostream>
#include <stdexcept>
using std::tr1::array;
using std::cin; using std::cout; using std::out_of_range;

const int ELEMS = 10;
array<int, ELEMS> squares = { 0, 1, 4, 9, 16,
  25, 36, 49, 64, 81 };

int main()
  { // demonstrate index checking with array::at
  int idx = -1;
  for (;;)
    { // don't do this:
    try { // show the value
        cout << idx << " squared is "
          << squares.at(idx) << '\n';
        break;
        }
    catch(const out_of_range&)
      { // prompt for new index value
      cout << "Value to square: ";
      cin >> idx;
      }
    }
  return 0;
  }
