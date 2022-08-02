#include <functional>
#include <iostream>
using std::tr1::reference_wrapper; using std::tr1::cref;
using std::cout;

void hello()
  { // simple function
  cout << "Hello, world\n";
  }

void goodbye()
  { // another simple function
  cout << "Goodbye, cruel world\n";
  }

int main()
  { // demonstrate invocation of reference_wrapper object
  typedef void (*const fun)();
  reference_wrapper<fun> rw(&hello);
  rw();         // calls hello
  rw = cref(&goodbye);
  rw();         // calls goodbye
  return 0;
  }