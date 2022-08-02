#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <random>
using std::tr1::is_integral;
using std::tr1::true_type; using std::tr1::false_type;
using std::cout;

template <class Ty>
void seed_impl(Ty val, const true_type&)
  { // seed with an integral type
  cout << "Called integral version of seed,"
  cout << " with argument type "
       << typeid(Ty).name() << '\n';
  }

template <class Ty>
void seed_impl(Ty val, const false_type&)
  { // seed with a non-integral type
  cout << "Called non-integral version of seed,"
  cout << " with argument type "
       << typeid(Ty).name() << '\n';
  }

template <class Ty>
void seed(Ty val)
  { // dispatch to appropriate version of seed_impl
  seed_impl(val, is_integral<Ty>());
  }

int main()
  { // call seed with several argument types
  seed(1);
  seed('a');
  seed(std::tr1::mt19937());
  return 0;
  }