#include <functional>
#include <memory>
#include <iostream>
using std::tr1::mem_fn; using std::tr1::shared_ptr;
using std::cout;

class C
  { // simple class with member function
public:
  C(int i0 = 0) : i(i0) {}
  void show() const
    { // show contents
    cout << i << '\n';
    }
private:
  int i;
  };

template <class Fty, class Ty>
void apply(Fty fn, Ty obj)
  { // call a function object with one argument
  fn(obj);
  }

int main()
  { // demonstrate simple use of mem_fn
  C c0(0);
  C *cp = new C(1);
  shared_ptr<C> sp(new C(2));
  void (C::*mptr)() const = &C::show;

  apply(mem_fn(mptr), c0);  // equivalent to (c0.*mptr)()
  apply(mem_fn(mptr), cp);  // equivalent to (cp->*mptr)()
  apply(mem_fn(mptr), sp);  // equivalent to ((*sp).*mptr)()

  delete cp;
  return 0;
  }