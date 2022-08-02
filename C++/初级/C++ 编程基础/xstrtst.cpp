// xstrtst.cpp

#include <iostream>
#include "xstring.h"
using namespace std;

main()
{
  xstring a;
  xstring b = "Test";
  a = xstring(5); // legal

  a = 5;         // illegal

  cout << a << endl;
}
