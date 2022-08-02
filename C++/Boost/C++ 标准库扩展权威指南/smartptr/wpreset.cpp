#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;

int main()
  { // demonstrate member function reset()
  weak_ptr<resource> wp0;
  show("empty object before reset", wp0);
  wp0.reset();
  show("empty object after reset", wp0);
  shared_ptr<resource> sp1(new resource(1));
  weak_ptr<resource> wp1(sp1);
  show("non-empty object before reset", wp1);
  wp1.reset();
  show("non-empty object after reset", wp1);
  return 0;
  }