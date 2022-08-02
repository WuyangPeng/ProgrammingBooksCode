#include <iostream>
#include <functional>
using std::tr1::bind;
using namespace std::tr1::placeholders;
using std::cout;

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
  // argument values
  int a = 10;
  int b = 11;
  int c = 12;

  // one additional argument
  one_arg a1;
  cout << bind(a1, _1)(a, b, c) << '\n';
  cout << a1(a) << '\n';          // equivalent call
  cout << bind(a1, _2)(a, b, c) << '\n';
  cout << a1(b) << '\n';          // equivalent call
  cout << bind(a1, _3)(a, b, c) << '\n';
  cout << a1(c) << '\n';          // equivalent call
  cout << bind(a1, 10)(a, b, c) << '\n';
  cout << a1(10) << '\n';         // equivalent call

  // three additional arguments
  three_args a3(1);
  cout << bind(&three_args::f, a3, _1, _2)(a, b, c)
    << '\n';
  cout << a3.f(a, b) << '\n';     // equivalent call
  cout << bind(&three_args::f, a3, _2, _3)(a, b, c)
    << '\n';
  cout << a3.f(b, c) << '\n';     // equivalent call
  cout << bind(&three_args::f, a3, _3, _2)(a, b, c)
    << '\n';
  cout << a3.f(c, b) << '\n';     // equivalent call
  cout << bind(&three_args::f, a3, 1, _2)(a, b, c)
    << '\n';
  cout << a3.f(1, b) << '\n';     // equivalent call
  return 0;
  }
