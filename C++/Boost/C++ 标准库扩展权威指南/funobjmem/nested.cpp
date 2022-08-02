#include <functional>
#include <iostream>
#include <typeinfo>
#include <utility>
using std::tr1::mem_fn;
using std::unary_function; using std::binary_function;
using std::cout;

void show_types(...)
  { // general function
  cout << "not unary_function or binary_function\n";
  }

template <class Ty, class Ret>
void show_types(
  const unary_function<Ty, Ret>& obj)
  { // overload for types derived from unary_function
  typedef unary_function<Ty, Ret> base;
  cout << "unary_function: "
       << typeid(base::result_type).name() << '('
       << typeid(base::argument_type).name() << ")\n";
  }

template <class Ty1, class Ty2, class Ret>
void show_types(
  const binary_function<Ty1, Ty2, Ret>& obj)
  { // overload for types derived from binary_function
  typedef binary_function<Ty1, Ty2, Ret> base;
  cout << "binary_function: "
       << typeid(base::result_type).name() << '('
       << typeid(base::first_argument_type).name()
       << ", "
       << typeid(base::second_argument_type).name()
       << ")\n";
  }

class C
  { // simple class with member functions
public:
  C(int i0 = 0) : i(i0) {}
  void show() const
    { // show contents
    cout << i << '\n';
    }
  void set(int i0)
    { // replace contents
    i = i0;
    }
private:
  int i;
  };

int main()
  { // show nested types
  show_types(mem_fn(&C::show));
  show_types(mem_fn(&C::set));
  return 0;
  }