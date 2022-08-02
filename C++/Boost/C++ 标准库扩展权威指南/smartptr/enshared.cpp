#include <memory>
#include <ostream>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::tr1::enable_shared_from_this;
using std::basic_ostream;

struct C : enable_shared_from_this<C>, resource
  {
  C(int i0 = 0) : resource(i0) {}
  };

static void show_sp(C *cp)
  {
  shared_ptr<C> spc(cp->shared_from_this());
  show("from this", spc);
  }

int main()
  {
  shared_ptr<C> sp(new C(1));
  show("original object", sp);
  C *cp = sp.get();
  show_sp(cp);
  show("after return", sp);
  return 0;
  }