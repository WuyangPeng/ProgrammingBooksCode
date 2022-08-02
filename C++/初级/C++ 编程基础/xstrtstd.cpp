#include <iostream>
#include <string>
#include "xstringd.h"
using namespace std;

int main()
{
  xstring x = "Steve ";
  xstring y = "Heller";
  xstring z = x + y;
  cout << z << endl;
}
