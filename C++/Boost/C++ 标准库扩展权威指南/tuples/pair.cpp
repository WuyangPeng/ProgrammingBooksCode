#include <iostream>
#include <typeinfo>
#include <utility>
using std::pair; using std::make_pair;
using std::tr1::get; using std::tr1::tuple_element;
using std::tr1::tuple_size;
using std::cout;

template <class Ty>
void show(const Ty& pr)
  {
  cout << "size:   " << tuple_size<Ty>::value << '\n';
  cout << "first type:  "
    << typeid(tuple_element<0, Ty>::type).name() << '\n';
  cout << "second type: "
    << typeid(tuple_element<1, Ty>::type).name() << '\n';
  cout << "first:  " << get<0>(pr) << '\n';
  cout << "second: " << get<1>(pr) << '\n' << '\n';
  }

int main()
  {
  show(make_pair(1, 2));
  show(make_pair(3.0, 1.1f));
  return 0;
  }