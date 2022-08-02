#include <functional>
#include <iostream>
using std::tr1::reference_wrapper;
using std::cout;

int main()
  { // demonstrate basic use of reference_wrapper
  int Stuhldreher = 3;
  reference_wrapper<int> rw(Stuhldreher);
  cout << rw << '\n';           // displays value of Stuhldreher
  Stuhldreher = 4;
  cout << rw << '\n';           // displays new value of Stuhldreher
  rw.get() = 5;                 // changes value of Stuhldreher
  cout << Stuhldreher << '\n';  // displays new value
  return 0;
  }