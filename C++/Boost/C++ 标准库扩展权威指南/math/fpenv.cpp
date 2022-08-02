#include <fenv.h>
#include <iostream>
#include "mathutil.h"
using std::cout;

class save_fp_env
  { // class to save and restore floating-point environment
public:
  save_fp_env() { fegetenv(&env); }
  ~save_fp_env() { fesetenv(&env); }
private:
  fenv_t env;
  };

double divide(double x, double y)
  { // simple floating-point computation
  save_fp_env env;
  double res = x / y;
  show_exceptions("in function 'divide'");
  return res;
  }

int main()
  { // demonstrate saving and restoring floating-point environment
  show_exceptions(
    "in function 'main' before call to 'divide'");
  divide(2.0, 3.0);
  show_exceptions(
    "in function 'main' after call to 'divide'");
  return 0;
  }
