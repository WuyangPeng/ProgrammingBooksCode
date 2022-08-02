#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;

int main()
  { // demonstrate object conversions
  shared_ptr<d_res> spa(new d_res(1));
  weak_ptr<d_res> wpa(spa);

  shared_ptr<resource> sp0(spa);
  show("shared_ptr constructed from shared_ptr<d_res>",
    sp0);
  weak_ptr<resource> wp0(spa);
  show("weak_ptr constructed from shared_ptr<d_res>",
    wp0);
  shared_ptr<resource> sp1(wpa);
  show("shared_ptr constructed from weak_ptr<d_res>",
    sp1);
  weak_ptr<resource> wp1(wpa);
  show("weak_ptr constructed from weak_ptr<d_res>",
    wp1);

  shared_ptr<d_res> spb(new d_res(2));
  weak_ptr<d_res> wpb(spb);

  sp0 = spb;
  show("shared_ptr assigned from shared_ptr<d_res>",
    sp0);
  wp0 = spb;
  show("weak_ptr assigned from shared_ptr<d_res>",
    wp0);
  wp1 = wpb;
  show("weak_ptr assigned from weak_ptr<d_res>",
    wp1);
  return 0;
  }
