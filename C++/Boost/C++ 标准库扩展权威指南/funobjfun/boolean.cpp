#include <functional>
#include <iostream>
#include <math.h>
using std::tr1::function;
using std::cout;

void report(const char *title, bool val)
  { // report state of function object
  cout << title << ": object is ";
  if (val)
    cout << "not ";
  cout << "empty\n";
  }

int main()
  { // demonstrate conversion to boolean type
  function<float(float)> fn;        // construct empty object
  report("after construction", fn);
  fn = cosf;                        // assign target object
  report("after assigning target object", fn);
  fn = 0;                           // assign null pointer
  report("after assigning null pointer", fn);
  return 0;
  }