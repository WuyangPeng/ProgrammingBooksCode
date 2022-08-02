#include <memory>
#include <stdlib.h>
#include <iostream>
#include <new>
#include "sputil.h"
using std::tr1::shared_ptr;
using std::bad_alloc; using std::cout;

static bool no_memory = false;

void *operator new(size_t sz)
  { // allocate memory, with one-shot failure
  void *res;
  bool no_mem = no_memory;
  no_memory = false;
  if (no_mem || (res = malloc(sz)) == 0)
    throw bad_alloc();
  return res;
  }

void operator delete(void *ptr)
  { // free allocated memory
  free(ptr);
  }

int main()
  { // demonstrate resource destruction on exception
  try {  // construct with no memory
    cout << "construct with no memory:\n";
    instrumented *ip = new instrumented;
    no_memory = true;
    shared_ptr<instrumented> sp0(ip);
    }
  catch(...)
    {  // handle the exception
    cout << " caught the exception\n";
    }
  try {  // reset with no memory
    cout << "reset with no memory:\n";
    shared_ptr<instrumented> sp1;
    instrumented *ip = new instrumented;
    no_memory = true;
    sp1.reset(ip);
    }
  catch(...)
    {  // handle the exception
    cout << " caught the exception\n";
    }
  return 0;
  }