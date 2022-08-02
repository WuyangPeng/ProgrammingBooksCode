listing 1
// Demonstrate an auto_ptr.
#include <iostream>
#include <memory>
using namespace std;

class X {
public:
  X() { cout << "constructing\n"; }
  ~X() { cout << "destructing\n"; }
  void f() { cout << "Inside f()\n"; }
};

int main()
{
  auto_ptr<X> p1(new X), p2;

  p2 = p1; // transfer ownership
  p2->f();

  // can assign to a normal pointer
  X *ptr = p2.get();
  ptr->f();

  return 0;
}

