//: C06:ComposeTry.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// A first attempt at implementing function composition.
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
using namespace std;

template<typename R, typename E, typename F1, typename F2>
class unary_composer {
  F1 f1;
  F2 f2;
public:
  unary_composer(F1 fone, F2 ftwo) : f1(fone), f2(ftwo) {}
  R operator()(E x) { return f1(f2(x)); }
};

template<typename R, typename E, typename F1, typename F2>
unary_composer<R, E, F1, F2> compose(F1 f1, F2 f2) {
  return unary_composer<R, E, F1, F2>(f1, f2);
}

int main() {
  double x = compose<double, const string&>(
    atof, mem_fun_ref(&string::c_str))("12.34");
  assert(x == 12.34);
} ///:~
