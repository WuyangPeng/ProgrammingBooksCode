#include <tuple>
#include <iostream>
using std::tr1::tuple; using std::tr1::get;
using std::cout;

int main()
  {
  tuple<int,int> t0(1, 2);
  cout << get<0>(t0) << ' ' << get<1>(t0) << '\n';   // 1 2
  return 0;
  }