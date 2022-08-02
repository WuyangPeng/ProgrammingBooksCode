#include <memory>
#include <iostream>
using std::tr1::shared_ptr;
using std::cout;

int main()
  { // demonstrate use of get
  int *ip = new int(3);             // allocate int resource
  cout << (void*)ip << '\n';        // show address
  shared_ptr<int> sp(ip);           // create shared_ptr object
  cout << (void*)sp.get() << '\n';  // show stored address
  return 0;
  }
