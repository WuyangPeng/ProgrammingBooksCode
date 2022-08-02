// xstrtst.cc

#include <iostream>
#include "xstring.h"
using namespace std;

main()
{
  string* s = new xstring();
  delete s;

  xstring a;
  xstring b = "Test";

  a = xstring(5); // legal

  a = 5;         // illegal

  cout << a << endl;
}
