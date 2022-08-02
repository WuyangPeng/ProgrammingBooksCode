#include <functional>
#include <iostream>
using std::tr1::mem_fn;
using std::cout;

class C
  { // simple class with member functions
public:
  C(int i0 = 0) : i(i0) {}
  void show() const
    { // show contents
    cout << "in show: " << i << '\n';
    }
  void one_arg(int j) const
    { // member function taking one argument
    cout << "in one_arg: " << i
         << ", " << j << '\n';
    }
  void two_args(int j, int k) const
    { // member function taking two arguments
    cout << "in two_args: " << i
         << ", " << j << ", " << k << '\n';
    }
private:
  int i;
  };

int main()
  {
  C c(1);
  int two = 2;
  int three = 3;
  mem_fn(&C::show)(c);                // c.show();
  mem_fn(&C::one_arg)(c, two);        // c.one_arg(two);
  mem_fn(&C::two_args)(c, two, three);// c.two_args(two, three);
  return 0;
  }