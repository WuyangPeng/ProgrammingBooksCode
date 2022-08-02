#include <functional>
using std::tr1::bind;

int no_args()
  { // function taking no arguments
  return 1;
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
  int f(int i, int j) const
    {   // member function taking two arguments
    return i + j;
    }
  };

void call_bind()
  { // examples of calls to bind
  // no additional arguments
  bind(no_args);

  // one additional argument
  one_arg a1;
  bind(a1, 1);

  // three additional arguments
  three_args a3;
  bind(&three_args::f, a3, 1, 2);
  }