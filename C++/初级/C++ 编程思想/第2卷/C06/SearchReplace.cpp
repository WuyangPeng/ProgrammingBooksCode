//: C06:SearchReplace.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// The STL search and replace algorithms.
#include <algorithm>
#include <functional>
#include <vector>
#include "PrintSequence.h"
using namespace std;

struct PlusOne {
  bool operator()(int i, int j) { return j == i + 1; }
};

class MulMoreThan {
  int value;
public:
  MulMoreThan(int val) : value(val) {}
  bool operator()(int v, int m) { return v * m > value; }
};

int main() {
  int a[] = { 1, 2, 3, 4, 5, 6, 6, 7, 7, 7,
    8, 8, 8, 8, 11, 11, 11, 11, 11 };
  const int ASZ = sizeof a / sizeof *a;
  vector<int> v(a, a + ASZ);
  print(v.begin(), v.end(), "v", " ");
  vector<int>::iterator it = find(v.begin(), v.end(), 4);
  cout << "find: " << *it << endl;
  it = find_if(v.begin(), v.end(),
    bind2nd(greater<int>(), 8));
  cout << "find_if: " << *it << endl;
  it = adjacent_find(v.begin(), v.end());
  while(it != v.end()) {
    cout << "adjacent_find: " << *it
         << ", " << *(it + 1) << endl;
    it = adjacent_find(it + 1, v.end());
  }
  it = adjacent_find(v.begin(), v.end(), PlusOne());
  while(it != v.end()) {
    cout << "adjacent_find PlusOne: " << *it
         << ", " << *(it + 1) << endl;
    it = adjacent_find(it + 1, v.end(), PlusOne());
  }
  int b[] = { 8, 11 };
  const int BSZ = sizeof b / sizeof *b;
  print(b, b + BSZ, "b", " ");
  it = find_first_of(v.begin(), v.end(), b, b + BSZ);
  print(it, it + BSZ, "find_first_of", " ");
  it = find_first_of(v.begin(), v.end(),
    b, b + BSZ, PlusOne());
  print(it,it + BSZ,"find_first_of PlusOne"," ");
  it = search(v.begin(), v.end(), b, b + BSZ);
  print(it, it + BSZ, "search", " ");
  int c[] = { 5, 6, 7 };
  const int CSZ = sizeof c / sizeof *c;
  print(c, c + CSZ, "c", " ");
  it = search(v.begin(), v.end(), c, c + CSZ, PlusOne());
  print(it, it + CSZ,"search PlusOne", " ");
  int d[] = { 11, 11, 11 };
  const int DSZ = sizeof d / sizeof *d;
  print(d, d + DSZ, "d", " ");
  it = find_end(v.begin(), v.end(), d, d + DSZ);
  print(it, v.end(),"find_end", " ");
  int e[] = { 9, 9 };
  print(e, e + 2, "e", " ");
  it = find_end(v.begin(), v.end(), e, e + 2, PlusOne());
  print(it, v.end(),"find_end PlusOne"," ");
  it = search_n(v.begin(), v.end(), 3, 7);
  print(it, it + 3, "search_n 3, 7", " ");
  it = search_n(v.begin(), v.end(),
    6, 15, MulMoreThan(100));
  print(it, it + 6,
    "search_n 6, 15, MulMoreThan(100)", " ");
  cout << "min_element: "
       << *min_element(v.begin(), v.end()) << endl;
  cout << "max_element: "
       << *max_element(v.begin(), v.end()) << endl;
  vector<int> v2;
  replace_copy(v.begin(), v.end(),
    back_inserter(v2), 8, 47);
  print(v2.begin(), v2.end(), "replace_copy 8 -> 47", " ");
  replace_if(v.begin(), v.end(),
    bind2nd(greater_equal<int>(), 7), -1);
  print(v.begin(), v.end(), "replace_if >= 7 -> -1", " ");
} ///:~
