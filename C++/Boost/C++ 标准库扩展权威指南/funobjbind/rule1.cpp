#include <functional>
#include <iostream>
using std::tr1::bind; using std::tr1::ref;
using std::cout;

void modify(int& arg)
  { // add 1 to argument
  ++arg;
  }

int main()
  { // demonstrate use of reference_wrapper with bind
  int i = 0;
  cout << i << '\n';

  // i passed by value; not modified
  bind(modify, i)();
  cout << i << '\n';

  // i passed by reference; modified
  bind(modify, ref(i))();
  cout << i << '\n';
  return 0;
  }