#include <tuple>
using std::tr1::tuple;

tuple<> none;                   // holds no elements
tuple<int> one;                 // holds one element, of type int

int i; double d;
tuple<int&, const double&>
    two(i, d);                  // holds two elements, one of
                                // type reference to int and one
                                // of type reference to const double
tuple<int, int, int, int, int,
  int, int, int, int, int> ten; // holds ten elements, all of type int
