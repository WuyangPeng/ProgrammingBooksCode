#include <stdlib.h>
#include <typeinfo>
#include <iostream>
using std::cout;

int main()
  { // show use of _Longlong and _ULonglong
  _Longlong val = 3;
  _ULonglong uval = 4;
  cout << typeid(val).name() << '\n';
  cout << typeid(uval).name() << '\n';
  return 0;
  }