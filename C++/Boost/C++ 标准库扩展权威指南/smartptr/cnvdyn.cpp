#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::tr1::dynamic_pointer_cast;

struct base0
  { // simple base class
  base0(int i0) : i(i0) {}
  virtual ~base0() {}
  int i;
  };

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr>& operator<<(
  std::basic_ostream<Elem, Tr>& str,
  const base0& b0)
  { // insert base0 contents into stream
  return str << b0.i;
  }

struct base1
  { // simple base class
  base1(int j0) : j(j0) {}
  virtual ~base1() {}
  int j;
  };

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr>& operator<<(
  std::basic_ostream<Elem, Tr>& str,
  const base1& b1)
  { // insert base1 contents into stream
  return str << b1.j;
  }

struct derived : virtual base0, base1
  { // derived class
  derived(int i0, int j0, int k0)
    : base0(i0), base1(j0), k(k0) {}
  int k;
  };

template <class Elem, class Tr>
std::basic_ostream<Elem, Tr>& operator<<(
  std::basic_ostream<Elem, Tr>& str,
  const derived& d)
  { // insert derived contents into stream
  return str << d.k;
  }

int main()
  {
  shared_ptr<base0> sp(new derived(1, 2, 3));
  show("base0 shared_ptr", sp);
  shared_ptr<derived> sp0 =
    dynamic_pointer_cast<derived>(sp);
  show("upcast from virtual base", sp0);
  shared_ptr<base1> sp1 =
    dynamic_pointer_cast<base1>(sp);
  show("cross-cast", sp1);
  shared_ptr<resource> sp2 =
    dynamic_pointer_cast<resource>(sp);
  show("failed cast", sp2);
  return 0;
  }