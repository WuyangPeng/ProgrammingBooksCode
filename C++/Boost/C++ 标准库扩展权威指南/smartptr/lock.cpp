#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;

static void do_lock(const char *title,
  weak_ptr<resource> wp)
  {
  shared_ptr<resource> sp = wp.lock();
  show(title, sp);
  }

int main()
  { // demonstrate member function lock
  shared_ptr<resource> sp0(new resource);
  weak_ptr<resource> wp0(sp0);
  do_lock("weak_ptr with resource", wp0);
  sp0.reset();
  do_lock("expired weak_ptr", wp0);
  return 0;
  }