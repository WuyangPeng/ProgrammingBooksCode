#include <ostream>
#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;

int main()
  {
  shared_ptr<resource> sp(new resource(3));
  show("construct from pointer", sp);
  return 0;
  }