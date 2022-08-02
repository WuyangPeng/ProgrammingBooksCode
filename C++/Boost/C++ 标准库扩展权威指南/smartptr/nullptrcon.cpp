#include <ostream>
#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;

int main()
  {
  shared_ptr<resource> sp((resource*)0);
  show("construct from null pointer", sp);
  return 0;
  }
