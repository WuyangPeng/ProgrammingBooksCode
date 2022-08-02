//
// clasview.cpp
// Understanding ClassView symbols.
// Chris H. Pappas and William H. Murray, 2000
//

// external static definition
// required for static class data members
static int static_publicParentData;

class parent {
  public:
    int        publicParentData;
    static int static_publicParentData;
               parent() {};

  private:
    float      privateParentData;
    void       privateParentMethod() {};

  protected:
    double     protectedParentData;
    void       protectedParentMethod() {};
};

class child:public parent {
  public:
    int        publicChildData;
    void       publicChildMethod() {};
               child() {};
  private:
    float      privateChildData;
    void       privateChildMethod() {};

  protected:
    double     protectedChildData;
    void       protectedChildMethod() {};
};

inline void doNothingFunction( void ) {};

void main( void )
{
  parent instanceParent;
  child  instanceChild;
}