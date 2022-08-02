#include <memory>
#include <iostream>
using std::tr1::shared_ptr; using std::tr1::get_deleter;
using std::cout;

struct del
  { // trivial deleter object
  void operator()(void *ptr)
    { // simply delete
    delete ptr;
    }
  };

int main()
  { // demonstrate function function get_deleter
  shared_ptr<int> sp0(new int);         // no deleter
  shared_ptr<int> sp1(new int, del());  // has deleter
  cout << get_deleter<del>(sp0) << '\n';
  cout << get_deleter<del>(sp1) << '\n';
  return 0;
  }