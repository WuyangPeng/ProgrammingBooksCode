#include <fenv.h>
#include <iostream>
#include "mathutil.h"
using std::cout;

double divide(double x, double y)
  { // simple floating-point computation
  double res = x / y;
  show_exceptions("in call to 'divide'");
  return res;
  }

int main()
  { // demonstrate fegetexceptflag and fesetexceptflag
  fexcept_t except;
  fegetexceptflag(&except, FE_INEXACT | FE_DIVBYZERO);
  show_exceptions("at start of 'main'");
  divide(2.0, 3.0);
  show_exceptions("after call to 'divide'");
  divide(2.0, 0.0);
  show_exceptions("after second call to 'divide'");
  fesetexceptflag(&except, FE_INEXACT);
  show_exceptions("after call to 'fesetexceptflag'");
  return 0;
  }