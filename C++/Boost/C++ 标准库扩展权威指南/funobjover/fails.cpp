#include <functional>
using std::not1; using std::bind1st;
using std::tr1::bind;
using namespace std::tr1::placeholders;
using std::binary_function;

struct do_something :
  binary_function<double, double, double>
  { // useless example of callable type with binary function call operator
  double operator()(double, double) const;
  };

void okay()
  { // C++03 call wrapper provides nested types
  not1(bind1st(do_something(), 1.0));
  }

void fails()
  { // TR1 call wrapper does not provide nested types
  not1(bind(do_something(), 1.0, _1));
  }
