#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
using std::copy; using std::ostream_iterator;
using std::set; using std::cout;

int main()
  { // show order of elements in associative container
  set<int> cont;
  cont.insert(0);
  cont.insert(2);
  cont.insert(4);
  cont.insert(1);
  cont.insert(3);
  cont.insert(5);
  copy(cont.begin(), cont.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  return 0;
  }
