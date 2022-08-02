#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;

int main()
  { // demonstrate construction from shared_ptr
  shared_ptr<resource> sp(new resource(4));
                                  // sp owns resource
  weak_ptr<resource> wp0(sp);     // wp0 points to resource 
  weak_ptr<resource> wp1(wp0);    // wp1 points to resource 
  show("first weak_ptr", wp0);
  show("second weak_ptr", wp1);
  return 0;
  }