#include <math.h>

void test()
  {
  int i_val = 2;
  float f_val = 2.0F;
  double d_val = 2.0;
  long double ld_val = 2.0L;
  atan2(i_val, d_val);      // calls atan2(double, double)
  atan2(i_val, f_val);      // calls atan2(double, double)
  atan2(f_val, f_val);      // calls atan2(float, float)
  atan2(f_val, ld_val);     // calls atan2(long double, long double)
  }
