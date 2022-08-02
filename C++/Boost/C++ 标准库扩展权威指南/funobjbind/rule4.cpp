#include <iostream>
#include <functional>
using std::tr1::bind;
using std::cout;

int no_args()
  { // function taking no arguments
  return 0;
  };

struct one_arg
  { // class type with member operator() taking one argument
  int operator()(int i) const
    { // function call operator that takes one argument
    return i;
    }
  typedef int result_type;
  };

struct three_args
  { // class type with member function taking two arguments
  three_args(int v) : val(v) {}
  int f(int i, int j) const
    {   // member function taking two arguments
    return val + 2 * i + 3 * j;
    }
private:
  int val;
  };

int main()
  { // examples of calls to bind
  // no additional arguments
  cout << bind(no_args)() << '\n';
  cout << no_args() << '\n';    // equivalent call

  // one additional argument
  one_arg a1;
  cout << bind(a1, 1)() << '\n';
  cout << a1(1) << '\n';        // equivalent call

  // three additional arguments
  three_args a3(1);
  cout << bind(&three_args::f, a3, 2, 3)() << '\n';
  cout << a3.f(2, 3) << '\n';   // equivalent call
  return 0;
  }