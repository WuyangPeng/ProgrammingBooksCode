#include <memory>
#include <iostream>
#include <ostream>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::cout;

resource *get_resource(int i)
  { // allocate resource object
  resource *res = new resource(i);
  cout << "created resource with value "
    << *res << '\n';
  return res;
  }

void destroy_resource(resource *res)
  { // destroy resource object
  cout << "destroying resource with value "
    << *res << '\n';
  delete res;
  }

int main()
  { // demonstrate function pointer as deleter object
  shared_ptr<resource> sp(get_resource(3),
    destroy_resource);
  cout << "In main, resource has value "
    << *sp << '\n';
  return 0;
  }