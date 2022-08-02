#include <iostream>
#include <memory>
using std::tr1::shared_ptr;
using std::cout;

struct instrumented
  { // class to report allocation and de-allocation
  static void *operator new(size_t sz)
    { // report allocation
    void *res = ::operator new(sz);
    cout << "created object at: " << res << '\n';
    return res;
    }
  static void operator delete(void *ptr)
    {  // report de-allocation
    cout << "destroyed object at: " << ptr << '\n';
    ::operator delete(ptr);
    }
  };

typedef shared_ptr<instrumented> spi;

int main()
  { // demonstrate reference counting
  spi sp0(new instrumented);            // allocate resource
  cout << sp0.use_count() << '\n';      // 1 shared_ptr
  spi sp1(sp0);                         // copy sp0
  cout << sp0.use_count() << '\n';      // 2 shared_ptrs
    {
    spi sp2(sp1);                       // copy sp1
    cout << sp0.use_count() << '\n';    // 3 shared_ptrs
    }
  cout << sp0.use_count() << '\n';      // 2 shared_ptrs
  return 0;
  }                                     // resource destroyed
