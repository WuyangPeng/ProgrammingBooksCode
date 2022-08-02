#include <functional>
#include <iostream>
using std::tr1::function;
using std::cout;

int func()
  { // simple function
  cout << "called func\n";
  return 0;
  }

struct S
  { // simple function object
  int operator()() const
    {
    cout << "called S::operator()\n";
    return 1;
    }
  typedef int result_type;
  } obj;

int main()
  { // demonstrate construction of function<> types
  function<int()> f0(func);
  f0();
  f0 = obj;
  f0();
  return 0;
  }