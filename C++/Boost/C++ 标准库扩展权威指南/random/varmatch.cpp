#include <random>
#include <iostream>
using std::tr1::variate_generator;
using std::tr1::mt19937;
using std::cout;

struct identity
  { // trivial floating-point distribution
  typedef double input_type;
  typedef double result_type;
  template <class Engine>
    double operator()(Engine& eng)
      { // return value from eng()
      return eng();
      }
  };

typedef mt19937 eng_t;
typedef identity dist_t;
typedef variate_generator<eng_t, dist_t> gen_t;

const int nvals = 10;

int main()
  { // demonstrate type matching and range adjustment
  eng_t eng;
  dist_t dist;
  gen_t gen(eng, dist);
  for (int i = 0; i < nvals; ++i)
    cout << gen() << '\n';
  return 0;
  }