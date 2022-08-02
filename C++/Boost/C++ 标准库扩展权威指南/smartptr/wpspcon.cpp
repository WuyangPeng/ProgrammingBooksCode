#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;

int main()
  { // demonstrate construction from shared_ptr
  shared_ptr<resource> sp(new resource(4));
                                  // sp owns resource
  show("shared_ptr", sp);
  weak_ptr<resource> wp(sp);      // wp points to resource 
  show("weak_ptr", wp);
  return 0;
  }