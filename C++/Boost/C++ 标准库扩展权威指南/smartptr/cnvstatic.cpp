#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::tr1::static_pointer_cast;

int main()
  { // demonstrate static_pointer_cast
  shared_ptr<resource> sp(new d_res(1));
  shared_ptr<d_res> sp0 = static_pointer_cast<d_res>(sp);
  show("base resource", sp);
  show("derived resource", sp0);

  sp.reset();
  sp0 = static_pointer_cast<d_res>(sp);
  show("null pointer to base resource", sp);
  show("null pointer to derived resource", sp0);
  return 0;
  }