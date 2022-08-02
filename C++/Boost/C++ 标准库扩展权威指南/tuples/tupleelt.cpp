#include <tuple>
#include <iostream>
#include <typeinfo>
using std::tr1::tuple; using std::tr1::tuple_element;
using std::cout;

typedef tuple<int> tuple1;
typedef tuple<int&,double&> tuple2;

template <class Ty>
void show_type()
  {
  cout << typeid(Ty).name() << '\n';  
  }

int main()
  {
  show_type<tuple_element<0, tuple1>::type>();  // int
  show_type<tuple_element<0, tuple2>::type>();  // int
  show_type<tuple_element<1, tuple2>::type>();  // double
  return 0;  
  }
