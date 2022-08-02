#include <functional>
#include <iostream>
using std::tr1::function;
using std::cout;

int func()
  { // simple function
  return 0;
  }

struct S
  { // simple function object
  int operator()() const
    {
    return 1;
    }
  typedef int result_type;
  } obj;

void report(const char *title, bool val)
  { // report state of function object
  cout << title << ": object is ";
  if (val)
    cout << "not ";
  cout << "empty\n";
  }

int main()
  { // demonstrate construction of function<> types
  function<int()> f0;
  report("after default construction", f0);
  function<int()> f1(0);
  report("after construction from 0", f1);
  function<int()> f2(f1);
  report("after construction from f1", f2);
  function<int()> f3(func);
  report("after construction from func", f3);
  function<int()> f4(obj);
  report("after construction from obj", f4);
  return 0;
  }
