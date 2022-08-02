#include <functional>
#include <iostream>
using std::tr1::mem_fn;
using std::cout;

template <class Ty>
void show_result_type(Ty)
  { // show nested type named result_type
  cout << typeid(Ty::result_type).name() << '\n';
  }

struct S
  { // struct with member functions
  int f0() { return 0; }
  long f1(int) { return 1; }
  void f2(int, int) {}
  double f3(int, int, int) { return 2.0; }
  };

int main()
  { // show nested result_type
  show_result_type(mem_fn(&S::f0)); // S::f0 returns int
  show_result_type(mem_fn(&S::f1)); // S::f1 returns long
  show_result_type(mem_fn(&S::f2)); // S::f2 returns void
  show_result_type(mem_fn(&S::f3)); // S::f3 returns double
  return 0;
  }