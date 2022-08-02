#include <functional>
#include <iostream>
#include <typeinfo>
#include <math.h>
using std::tr1::function;
using std::cout; using std::type_info;

struct S
  { // simple callable type
  float operator()(float) { return 1.0f; }
  typedef float result_type;
  };

void show_type(const char *title, const type_info& info)
  { // show name of target type
  cout << title << ": " << info.name() << '\n';
  }

int main()
  { // demonstrate function::target_type
  function<float(float)> fn;
  show_type("empty", fn.target_type());
  fn = cosf;
  show_type("cosf", fn.target_type());
  fn = S();
  show_type("S", fn.target_type());
  return 0;
  }