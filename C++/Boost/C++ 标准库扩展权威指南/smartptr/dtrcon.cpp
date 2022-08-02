#include <iostream>
#include <ostream>
#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::cout;

struct deleter
  {
  void operator()(resource *res)
    {
    cout << "destroying resource at "
         << (void*)res << '\n';
    delete res;
    }
  };

int main()
  {
  shared_ptr<resource> sp(new resource(3), deleter());
  show("construct from pointer", sp);
  return 0;
  }