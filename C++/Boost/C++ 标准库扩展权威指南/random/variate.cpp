#include <random>
#include <iomanip>
#include <iostream>
#include <array>
using std::tr1::variate_generator;
using std::tr1::ranlux3_01;
using std::tr1::gamma_distribution;
using std::tr1::array;
using std::cout; using std::setw; using std::left;

typedef ranlux3_01 eng_t;
typedef gamma_distribution<> dist_t;
typedef variate_generator<eng_t, dist_t> gen_t;

const int nvals = 10;

int main()
  { // demonstrate variate_generator
  eng_t eng;
  dist_t dist;
  gen_t gen(eng, dist);
  array<gen_t::result_type,nvals> res0, res1;
  for (int i = 0; i < nvals; ++i)
    res0[i] = dist(eng);

  for (int i = 0; i < nvals; ++i)
    res1[i] = gen();

  cout << "Part 1\n" << left;
  for (int i = 0; i < nvals; ++i)
    cout << setw(12) << res0[i] << ' '
      << setw(12) << res1[i] << '\n';

  // restart
  eng.seed();
  dist.reset();
  for (int i = 0; i < nvals; ++i)
    res0[i] = dist(eng);

  gen.engine().seed();
  gen.distribution().reset();
  for (int i = 0; i < nvals; ++i)
    res1[i] = gen();

  cout << "\nPart2\n";
  for (int i = 0; i < nvals; ++i)
    cout << setw(12) << res0[i] << ' '
      << setw(12) << res1[i] << '\n';
  return 0;
  }
