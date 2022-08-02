#include <memory>
#include <iomanip>
#include <iostream>
using std::tr1::shared_ptr;
using std::cout; using std::boolalpha;

typedef shared_ptr<int> spi;

int main()
  { // demonstrate member function unique
  cout << boolalpha;
  spi sp0;                          // empty object
  cout << "empty object: " << sp0.unique() << '\n';
  spi sp1((int*)0);                 // no resource
  cout << "null pointer: " << sp1.unique() << '\n';
  spi sp2(new int);                 // controls resource
  cout << "one object: " << sp2.unique() << '\n';
  { // create short-lived object
  spi sp3(sp2);                     // copy
  cout << "two objects: " << sp2.unique() << '\n';
  } // sp3 destroyed
  cout << "one object: " << sp2.unique() << '\n';
  return 0;
  }