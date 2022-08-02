#include <iostream>
#include <memory>
using std::tr1::shared_ptr;
using std::cout;

struct instrumented
  { // class to report allocation and de-allocation
  static void *operator new(size_t sz)
    { // report allocation
    void *res = ::operator new(sz);
    cout << " Created object at: " << res << '\n';
    return res;
    }
  static void operator delete(void *ptr)
    {  // report de-allocation
    cout << " Destroyed object at: " << ptr << '\n';
    ::operator delete(ptr);
    }
  };

typedef shared_ptr<instrumented> spi;

static void h(spi& sp)
  {
  spi sp0(sp);
  cout << "   In h, ref count is "
    << sp.use_count() << '\n';
  }

static void g(spi& sp)
  {
  spi sp0(sp);
  cout << "  In g, ref count is "
    << sp.use_count() << '\n';
  h(sp);
  cout << "  Back in g, ref count is "
    << sp.use_count() << '\n';
  }

static void f()
  {
  spi sp(new instrumented);
  cout << " In f, ref count is "
    << sp.use_count() << '\n';
  g(sp);
  cout << " Back in f, ref count is "
    << sp.use_count() << '\n';
  }

int main()
  {
  cout << "In main\n";
  f();
  cout << "Back in main\n";
  return 0;
  }