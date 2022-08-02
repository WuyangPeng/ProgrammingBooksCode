#include <random>
#include <iostream>
#include <sstream>
using std::tr1::normal_distribution;
using std::tr1::ranlux64_base_01;
using std::stringstream; using std::cout;

int main()
  { // show properties of a distribution
  ranlux64_base_01 eng;
  normal_distribution<> dist;
  stringstream str;
  std::cout << "First value: " << dist(eng) << '\n';
  str<< eng << ' ' << dist;
  std::cout << "Second value: " << dist(eng) << '\n';
  str >> eng >> dist;
  std::cout << "Second value, after read: "
    << dist(eng) << '\n';
  str.clear();
  str.seekg(0);
  str >> eng >> dist;
  dist.reset();
  std::cout << "Second value, after reset: "
    << dist(eng) << '\n';
  return 0;
  }