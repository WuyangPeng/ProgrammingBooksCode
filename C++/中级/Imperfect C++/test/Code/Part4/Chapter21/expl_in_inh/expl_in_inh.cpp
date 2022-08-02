
///////////////////////////////////////////////////////
#if 0
///////////////////////////////////////////////////////

#include <ctime>

struct Interface
{
  virtual void DoSomething() = 0;
};

class Concrete
  : public Interface
{

private:
  void DoSomething()
  {}
};

void func();
void func()
{
    Concrete    c;

    c.DoSomething(); //  Error

    Interface    *i_ptr = &c;

    i_ptr->DoSomething(); // OK
}

///////////////////////////////////////////////////////
#else
///////////////////////////////////////////////////////


#include <stlsoft_explicit_inheritance_veneer.h>

class Time
  : public stlsoft::explicit_inheritance_veneer<std::tm>
{
public:
  Time()
  {
    std::time_t t;

    std::time(&t);
    base_type_value() = *std::localtime(&t);
  }
  
  Time(std::time_t const t)
  {
    base_type_value() = *std::localtime(&t);
  }
};

int main()
{
  Time          t;
  char const    *s = std::asctime(&t);
    
  return 0;
}

///////////////////////////////////////////////////////
#endif 
///////////////////////////////////////////////////////
