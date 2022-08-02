#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;

int main()
  { // demonstrate member function swap
  shared_ptr<resource> sp0(new resource(0));
  weak_ptr<resource> wp0(sp0);
  shared_ptr<resource> sp1(new resource(1));
  weak_ptr<resource> wp1(sp1);
  show("wp0 before swap", wp0);
  show("wp1 before swap", wp1);
  wp0.swap(wp1);
  show("wp0 after swap", wp0);
  show("wp1 after swap", wp1);
  swap(wp0, wp1);
  show("wp0 after second swap", wp0);
  show("wp1 after second swap", wp1);
  return 0;
  }