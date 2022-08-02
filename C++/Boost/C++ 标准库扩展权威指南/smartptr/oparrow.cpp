#include <memory>
#include <iostream>
using std::tr1::shared_ptr;
using std::cout;

struct S
  {
  int member;
  };

int main()
  { // demonstrate use of operator->
  S *s = new S;                     // create object
  s->member = 4;                    // assign to member
  shared_ptr<S> sp(s);              // create shared_ptr object
  cout << sp->member << '\n';       // show value of member
  return 0;
  }