#include <iostream>
#include <sstream>
#include <iomanip>
using std::boolalpha;
using std::stringstream;
using std::cout; using std::hexfloat;

int main()
  { // demonstrate use of hexfloat stream manipulator
  cout << boolalpha;
  stringstream str;
  double d = 0.1/0.3;
  str << d;
  double res = 0.0;
  str >> res;
  cout << hexfloat << d << ' ' << res
    << (d == res ? " " : " not ") << "equal " << '\n';
  str.clear();
  str << hexfloat << d;
  res = 0.0;
  str >> res;
  cout << hexfloat << d << ' ' << res
    << (d == res ? " " : " not ") << "equal " << '\n';
  return 0;
  }