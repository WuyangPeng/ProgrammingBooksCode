#include <iomanip>
#include <iostream>
#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr; using std::tr1::weak_ptr;
using std::cout; using std::boolalpha;

int main()
  { // demonstrate member function expired
  cout << boolalpha;
  shared_ptr<resource> sp(new resource);
  weak_ptr<resource> wp(sp);
  cout << "points to resource: " << wp.expired() << '\n';
  sp.reset();
  cout << "expired: " << wp.expired() << '\n';
  return 0;
  }