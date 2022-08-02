#include <functional>
#include <math.h>
#include <iostream>
#include <typeinfo>
using std::tr1::result_of;
using std::ostream; using std::cout;

class C
  { // sample class
public:
  C(int i0) : i(i0) {}
  long get() const { return i; }
  int i;
  void operator()(int ii) { i = ii; }
  typedef void result_type;
  };

template <class Fty, class Arg>
void show_return(Fty fun, Arg arg)
  { // show return type of fun(arg)
  typedef typename result_of<Fty(Arg)>::type ret;
  cout << "Return type of " << typeid(Fty).name()
    << " when called with " << typeid(Arg).name()
    << " is " << typeid(ret).name() << '\n';
  }

int main()
  { // demonstrate class template result_of
  C c(1);
  C *cp = &c;
  const C *ccp = &c;
  show_return(cosf, 1.0);       // cosf(float) returns float
  show_return(&C::get, cp);     // C::get() returns long
  show_return(&C::i, ccp);      // C::i has type const int
  show_return(c, 3);            // C() returns void
  return 0;
  }