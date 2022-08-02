#include <memory>
#include "sputil.h"
using std::tr1::shared_ptr;

int main()
  {
  shared_ptr<int> sp;           // default constructor
  show("default constructor", sp);
  return 0;
  }