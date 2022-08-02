#include <fenv.h>
#include <iostream>
#include "mathutil.h"
using std::cout;

int main()
  { // demonstrate feraiseexcept, feclearexcept, and fetestexcept
  show_exceptions("at start of 'main'");
  feraiseexcept(FE_INEXACT);
  show_exceptions("after call to 'feraiseexcept'");
  feclearexcept(FE_INEXACT);
  show_exceptions("after call to 'feclearexcept'");
  return 0;
  }