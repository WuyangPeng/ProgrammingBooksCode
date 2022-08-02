#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::auto_ptr;

int main()
  {
  auto_ptr<resource> ap(new resource(5));
  show("construct auto_ptr from pointer", ap);
  shared_ptr<resource> sp(ap);
  show("auto_ptr", ap);
  show("shared_ptr", sp);
  return 0;
  }