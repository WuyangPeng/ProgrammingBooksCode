#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using std::copy; using std::ostream_iterator;
using std::vector; using std::cout;

int main()
  { // show order of elements in sequence container
  vector<int> cont;
  cont.push_back(0);
  cont.push_back(2);
  cont.push_back(4);
  cont.push_back(1);
  cont.push_back(3);
  cont.push_back(5);
  copy(cont.begin(), cont.end(),
    ostream_iterator<int>(cout, " "));
  cout << '\n';
  return 0;
  }