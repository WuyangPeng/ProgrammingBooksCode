#include <fenv.h>
#include <iostream>
#include "mathutil.h"
using std::cout;

class hold_exceptions
  { // class to defer raising of exceptions
public:
  hold_exceptions() { feholdexcept(&env); }
  ~hold_exceptions()
    { // ignore inexact, raise all others
    feclearexcept(FE_INEXACT);
    feupdateenv(&env);
    }
private:
  fenv_t env;
  };

double divide(double x, double y)
  { // simple floating-point computation
  hold_exceptions holder;
  double res = x / y;
  show_exceptions("in call to 'divide'");
  return res;
  }

int main()
  { // demonstrate feholdexcept and feupdateenv
  show_exceptions("at start of 'main'");
  divide(2.0, 3.0);
  show_exceptions("after call to 'divide'");
  divide(2.0, 0.0);
  show_exceptions("after second call to 'divide'");
  return 0;
  }
