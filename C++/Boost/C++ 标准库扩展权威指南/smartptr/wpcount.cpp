#include <memory>
#include <iostream>
using std::tr1::shared_ptr; using std::tr1::weak_ptr;
using std::cout;

typedef shared_ptr<int> spi;
typedef weak_ptr<int> wpi;

int main()
  { // demonstrate member function use_count
  wpi wp0;                          // empty object
  cout << "empty object: " << wp0.use_count() << '\n';
  spi sp1((int*)0);                 // no resource
  wpi wp1(sp1);
  cout << "null pointer: " << wp1.use_count() << '\n';
  spi sp2(new int);                 // controls resource
  wpi wp2(sp2);
  cout << "one object: " << wp2.use_count() << '\n';
  { // create short-lived object
  spi sp3(sp2);                     // copy
  cout << "two objects: " << wp2.use_count() << '\n';
  } // sp3 destroyed
  cout << "one object: " << wp2.use_count() << '\n';
  sp2.reset();
  cout << "expired: " << wp2.use_count() << '\n';
  return 0;
  }