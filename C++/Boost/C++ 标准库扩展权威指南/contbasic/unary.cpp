#include <algorithm>
#include <functional>
#include <iostream>
using std::for_each; using std::unary_function;
using std::cout;

template <class Ty>
struct writer : unary_function<Ty, void>
  { // write values
  void operator()(const Ty& val)
    { // write the passed value
    cout << val << ' ';
    }
  };

int main()
  { // demonstrate use of unary function object
  const int NVALS = 6;
  int values[NVALS] = { 3, 1, 9, 4, 5, 7 };
  for_each(values, values + NVALS, writer<int>());
  return 0;
  }