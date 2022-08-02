#include <functional>
using std::tr1::reference_wrapper;

class ref
  { // simple class containing reference
public:
  ref(int& i) : member(i) {}
private:
  int& member;
  };

class refwrap
  { // simple class containing reference_wrapper
public:
  refwrap(int& i) : member(i) {}
private:
  reference_wrapper<int> member;
  };

void f()
  { // demonstrate copying
  int i, j;
  ref r0(i);
  ref r1(j);
  r1 = r0;      // error: ref can't be copied

  refwrap rw0(i);
  refwrap rw1(j);
  rw1 = rw0;    // okay: refwrap can be copied
  }