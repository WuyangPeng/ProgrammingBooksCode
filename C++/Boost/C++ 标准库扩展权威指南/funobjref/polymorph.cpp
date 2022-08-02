#include <functional>
#include <iostream>
using std::tr1::reference_wrapper;
using std::cout;

struct base
  { // base class
  virtual void show() const
    { // show name of base class
    cout << "base\n";
    }
  };

struct derived0 : base
  { // one derived class
  void show() const
    { // show name of derived class
    cout << "derived0\n";
    }
  };

struct derived1 : base
  { // another derived class
  void show() const
    { // show name of derived class
    cout << "derived1\n";
    }
  };

int main()
  { // demonstrate reference_wrapper's support for polymorphism
  derived0 Crowley;
  derived1 Layden;
  reference_wrapper<base> rw0(Crowley);
  rw0.get().show();         // calls derived0::show
  reference_wrapper<base> rw1(Layden);
  rw1.get().show();         // calls derived1::show
  return 0;
  }