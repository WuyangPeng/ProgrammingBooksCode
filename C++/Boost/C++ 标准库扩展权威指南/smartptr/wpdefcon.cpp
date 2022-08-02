#include <memory>
#include "sputil.h"
using std::tr1::weak_ptr;

int main()
  {
  weak_ptr<int> sp;           // default constructor
  show("default constructor", sp);
  return 0;
  }

