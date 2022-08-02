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
  { // demonstrate assignment of function<> types
  function<int()> f0(func), f1;
  report("constructed from func", f0);
  f0 = f1;
  report("assigned empty function object", f0);
  f0 = func;
  report("assigned func", f0);
  f0 = 0;
  report("assigned 0", f0);
  f0 = obj;
  report("assigned obj", f0);
  return 0;
  }