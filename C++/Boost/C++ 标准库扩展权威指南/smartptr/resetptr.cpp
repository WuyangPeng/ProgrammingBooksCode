#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;

int main()
  { // demonstrate member function reset
  shared_ptr<resource> sp0;
  show("empty object before reset", sp0);
  sp0.reset(new resource(1));
  show("empty object after reset", sp0);
  sp0.reset(new resource(2));
  show("non-empty object after reset", sp0);
  return 0;
  }