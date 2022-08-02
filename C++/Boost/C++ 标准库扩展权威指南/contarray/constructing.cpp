#include <array>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <iostream>
using std::tr1::array;
using std::basic_ostream; using std::cout;
using std::copy; using std::ostream_iterator;

class Elt
  { // class with non-trivial default constructor
public:
  Elt() : i(1) {}
  Elt(int ii) : i(ii) {}
private:
  template<class Elem, class Traits> friend
    basic_ostream<Elem, Traits>& operator<<(
      basic_ostream<Elem, Traits>&, const Elt&);
  int i;
  };

template<class Elem, class Traits>
  basic_ostream<Elem, Traits>& operator<<(
    basic_ostream<Elem, Traits>& out, const Elt& elt)
  { // show object contents
  return out << elt.i;
  }

int main()
  { // demonstrate default constructor and aggregate initialization
  array<Elt, 6> arr0;
  copy(arr0.begin(), arr0.end(),
    ostream_iterator<Elt>(cout, " "));
  cout << '\n';
  array<Elt, 6> arr1 = { 1, 2, 3, 4 };
  copy(arr1.begin(), arr1.end(),
    ostream_iterator<Elt>(cout, " "));
  cout << '\n';
  array<int, 6> arr2 = { 1, 2, 3, 4 };
  copy(arr2.begin(), arr2.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  array<int, 6> arr3;
  copy(arr3.begin(), arr3.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  array<int, 6> arr4 = {};
  copy(arr4.begin(), arr4.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  return 0;
  }