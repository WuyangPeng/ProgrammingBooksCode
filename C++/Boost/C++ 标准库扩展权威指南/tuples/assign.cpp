#include <utility>
#include <iostream>
#include <tuple>
using std::tr1::tuple; using std::tr1::get;
using std::cout; using std::make_pair;

void show(int i, int j, const tuple<int,int&,int>& t)
  {
  cout << i << ' ' << j << ": "
       << get<0>(t) << ' '
       << get<1>(t) << ' '
       << get<2>(t) << '\n';
  }

void show(const tuple<int,int>& t)
  {
  cout << get<0>(t) << ' '
       << get<1>(t) << '\n';
  }

int main()
  {
  int i = 1, j = 2;
  tuple<int,int&,int> t0(i, j, 3);
  tuple<int,double,char> t1(4, 5.1, '\6');
  show(i, j, t0);               // 1 2: 1 2 3
  t0 = t1;
  show(i, j, t0);               // 1 5: 4 5 6
  tuple<int,int> t2(1, 2);
  show(t2);                     // 1 2
  t2 = make_pair(3, 4);
  show(t2);                     // 3 4
  return 0;
  }
