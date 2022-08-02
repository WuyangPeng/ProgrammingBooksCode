#ifndef MYCLASS_H__ // #include guards, Recipe 2.1
#define MYCLASS_H__
#include <string>

namespace mylib { // Namespaces, Recipe 2.4
class AnotherClass; // forward class declarations, Recipe 2.3
class Logger;
extern Logger* gpLogger; // External storage declaration, Recipe 2.2

class MyClass {
public:
  std::string getVal( ) const;
  // ...
private:
  static int refCount_;
  std::string val_;
}

// Inline definitions, Recipe 2.5
inline std::string MyClass::getVal( ) const {
  return(val_);
}

#include "myclass.inl"
} // namespace

#endif // MYCLASS_H_ _
