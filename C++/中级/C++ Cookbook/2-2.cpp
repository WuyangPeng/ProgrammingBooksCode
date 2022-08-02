#include "myclass.h"
namespace mylib {
  MyClass::refCount_ = 0; // Static definition, Recipe 8.4
  MyClass::foo( ) {       // Method implementations
    // ...
  }
}
