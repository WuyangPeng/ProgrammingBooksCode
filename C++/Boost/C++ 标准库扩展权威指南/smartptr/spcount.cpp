#include <memory>
#include <iostream>
using std::tr1::shared_ptr;
using std::cout;

typedef shared_ptr<int> spi;

int main()
  { // demonstrate member function use_count
  spi sp0;                          // empty object
  cout << "empty object: " << sp0.use_count() << '\n';
  spi sp1((int*)0);                 // no resource
  cout << "null pointer: " << sp1.use_count() << '\n';
  spi sp2(new int);                 // controls resource
  cout << "one object: " << sp2.use_count() << '\n';
  { // create short-lived object
  spi sp3(sp2);                     // copy
  cout << "two objects: " << sp2.use_count() << '\n';
  } // sp3 destroyed
  cout << "one object: " << sp2.use_count() << '\n';
  return 0;
  }