#include <algorithm>
#include <memory>
#include <iostream>
#include <set>
using std::tr1::shared_ptr;
using std::lower_bound; using std::set;
using std::cout;

typedef shared_ptr<int> spi;
typedef set<spi> iset;
typedef iset::const_iterator citer;

static void lookup(const iset& data, spi sp)
  { // look for stored object that matches sp
  citer res = lower_bound(data.begin(), data.end(), sp);
  cout << *sp;
  if (res == data.end() || *res != sp)
    cout << " not found\n";
  else
    cout << " found\n";
  }

int main()
  { // demonstrate less-than comparison
  iset data;
  spi sp0(new int(0));
  spi sp1(new int(1));
  spi sp2(new int(2));
  spi sp3(sp1);         // shares ownership with sp1
  spi sp4(new int(1));  // same value as sp1, but different resource
  data.insert(sp0);
  data.insert(sp1);
  data.insert(sp2);
  lookup(data, sp1);    // search for sp1
  lookup(data, sp3);    // search for sp3
  lookup(data, sp4);    // search for sp4
  return 0;
  }