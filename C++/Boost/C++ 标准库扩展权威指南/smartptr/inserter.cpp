#include <memory>
#include <iostream>
using std::tr1::shared_ptr;
using std::cout;

int main()
  { // demonstrate stream inserter
  shared_ptr<int> sp(new int);
  cout << "   get: " << sp.get() << '\n';
  cout << "object: " << sp << '\n';
  return 0;
  }