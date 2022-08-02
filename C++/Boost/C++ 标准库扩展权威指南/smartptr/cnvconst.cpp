#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::tr1::const_pointer_cast;

int main()
  { // demonstrate pointer conversions
  shared_ptr<const resource> sp(new resource(1));
  show("shared_ptr to const object", sp);
  shared_ptr<resource> sp0 =
    const_pointer_cast<resource>(sp);
  show("shared_ptr to non-const object", sp0);
  return 0;
  }
