#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;

int main()
  { // demonstrate member function reset()
  shared_ptr<resource> sp0;
  show("empty object before reset", sp0);
  sp0.reset();
  show("empty object after reset", sp0);
  shared_ptr<resource> sp1(new resource(1));
  show("non-empty object before reset", sp1);
  sp1.reset();
  show("non-empty object after reset", sp1);
  return 0;
  }