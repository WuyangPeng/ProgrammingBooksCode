//
// staticptr.cpp
// Detecting bad pointer assignment
// Chris H. Pappas and William H. Murray, 2000
//

#include <iostream>

using namespace std;

typedef struct tagIntegerNode {
  int             iValue;
  tagIntegerNode *pNextIntegerNode;
}INTEGERNODE;

class A {
  public: 
    // Made public to simplify tracing
    // Would normally be protected:
    static INTEGERNODE *pFirstIntegerNode;
};

// Static data members must be initialized at file scope, even
// if private.
INTEGERNODE *A::pFirstIntegerNode;

class B:public A {
  public:
    B( void );
};

class C:public A {
  public:
    C( void );
};

void main( void )
{
  B instanceB;
  C instanceC;

  cout << instanceB.pFirstIntegerNode->iValue << endl;
  cout << instanceC.pFirstIntegerNode->pNextIntegerNode->iValue << endl;
};

B::B( void )
{
  pFirstIntegerNode                   = new INTEGERNODE;
  pFirstIntegerNode->iValue           = 1;
  pFirstIntegerNode->pNextIntegerNode = NULL;
};

C::C( void )
{
  pFirstIntegerNode->pNextIntegerNode                   = new INTEGERNODE;
  pFirstIntegerNode->pNextIntegerNode->iValue           = 2;
  pFirstIntegerNode->pNextIntegerNode->pNextIntegerNode = NULL;
};