#include <functional>
#include <iostream>
using std::tr1::reference_wrapper;
using std::tr1::ref; using std::tr1::cref;
using std::cout;

void show(int& i)
  { // show value referred to by reference to int
  cout << "int&: " << i << '\n';
  }

void show(const int& i)
  { // show value referred to by reference to const int
  cout << "const int&: " << i << '\n';
  }

int main()
  { // demonstrate use of ref and cref
  int Miller = 3;
  show(ref(Miller));    // calls show(int\&);
  reference_wrapper<int> rw0(Miller);
  show(ref(rw0));       // calls show(int\&);
  show(cref(Miller));   // calls show(const int\&);
  reference_wrapper<const int> rw1(Miller);
  show(cref(rw1));      // calls show(const int\&);
  return 0;
  }