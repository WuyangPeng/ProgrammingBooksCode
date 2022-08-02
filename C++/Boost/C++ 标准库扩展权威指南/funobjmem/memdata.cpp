#include <functional>
#include <iostream>
#include <typeinfo>
using std::tr1::mem_fn;
using std::cout;

template <class Ty>
void show_type(Ty)
  { // show the name of a type
  cout << typeid(Ty).name() << '\n';
  }

struct S
  {
  S() : i(0), j(1) {}
  int i;
  const int j;
  };

int main()
  {
  S s;
  const S cs;
  show_type(mem_fn(&S::i)(s));  // type of s.i
  show_type(mem_fn(&S::i)(cs)); // type of cs.i
  show_type(mem_fn(&S::j)(s));  // type of s.j
  show_type(mem_fn(&S::j)(cs)); // type of cs.j
  }