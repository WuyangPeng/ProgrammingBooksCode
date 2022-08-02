//: C07:ListSpecialFunctions.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
//{L} Noisy
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include "Noisy.h"
#include "PrintContainer.h"
using namespace std;

int main() {
  typedef list<Noisy> LN;
  LN l1, l2, l3, l4;
  generate_n(back_inserter(l1), 6, NoisyGen());
  generate_n(back_inserter(l2), 6, NoisyGen());
  generate_n(back_inserter(l3), 6, NoisyGen());
  generate_n(back_inserter(l4), 6, NoisyGen());
  print(l1, "l1", " "); print(l2, "l2", " ");
  print(l3, "l3", " "); print(l4, "l4", " ");
  LN::iterator it1 = l1.begin();
  ++it1; ++it1; ++it1;
  l1.splice(it1, l2);
  print(l1, "l1 after splice(it1, l2)", " ");
  print(l2, "l2 after splice(it1, l2)", " ");
  LN::iterator it2 = l3.begin();
  ++it2; ++it2; ++it2;
  l1.splice(it1, l3, it2);
  print(l1, "l1 after splice(it1, l3, it2)", " ");
  LN::iterator it3 = l4.begin(), it4 = l4.end();
  ++it3; --it4;
  l1.splice(it1, l4, it3, it4);
  print(l1, "l1 after splice(it1,l4,it3,it4)", " ");
  Noisy n;
  LN l5(3, n);
  generate_n(back_inserter(l5), 4, NoisyGen());
  l5.push_back(n);
  print(l5, "l5 before remove()", " ");
  l5.remove(l5.front());
  print(l5, "l5 after remove()", " ");
  l1.sort(); l5.sort();
  l5.merge(l1);
  print(l5, "l5 after l5.merge(l1)", " ");
  cout << "\n Cleanup" << endl;
} ///:~
