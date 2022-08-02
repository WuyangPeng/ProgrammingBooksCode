#include <memory>
#include "sputil.h"
using std::tr1::enable_shared_from_this;

class derived : public enable_shared_from_this<derived>
  {
  typedef enable_shared_from_this<derived> base;
public:
  derived() {}      // calls default constructor for base
  derived(const derived& der)
    : base(der) {}  // explicit call to copy constructor for base
  derived& operator=(const derived& der)
    {
    base::operator=(der); // explicit call to assignment operator
    }
  ~derived() {}     // calls destructor for base
  };
