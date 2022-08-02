#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;

int main()
  { // demonstrate pointer conversions
  shared_ptr<resource> sp(new d_res(1));
  show("constructed from pointer to derived", sp);
  sp.reset(new d_res(2));
  show("reset with pointer to derived", sp);
  return 0;
  }