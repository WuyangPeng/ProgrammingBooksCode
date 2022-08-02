#include <memory>
#include <iomanip>
#include <iostream>
using std::tr1::shared_ptr;
using std::cout; using std::boolalpha;

int main()
  {
  cout << boolalpha;
  shared_ptr<int> sp0(new int(0));
  shared_ptr<int> sp1(sp0);
  shared_ptr<int> sp2(new int(2));
  cout << "sp0 == sp1: " << (sp0 == sp1) << '\n';
  cout << "sp0 == sp2: " << (sp0 == sp2) << '\n';
  cout << "sp0 != sp1: " << (sp0 != sp1) << '\n';
  cout << "sp0 != sp2: " << (sp0 != sp2) << '\n';
  return 0;
  }