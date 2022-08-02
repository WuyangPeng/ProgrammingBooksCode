#include <tuple>
#include <iostream>
using std::tr1::tuple; using std::tr1::get;
using std::cout;

void show(int i, int j, const tuple<int,int&,int> t)
  {
  cout << i << ' ' << j << ": "
       << get<0>(t) << ' '
       << get<1>(t) << ' '
       << get<2>(t) << '\n';
  }

int main()
  {
  int i = 1, j = 2;
  tuple<int,int&,int> t0(i, j, 3);
  show(i, j, t0);               // 1 2: 1 2 3
  get<0>(t0) = 4;               // set first element to 4
  get<1>(t0) = 5.1;             // set object referred to by
                                // second element to 5
  get<2>(t0) = '\6';            // set third element to 6
  show(i, j, t0);               // 1 5: 4 5 6
  return 0;
  }