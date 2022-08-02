// brkcndts.cpp
// Using Breakpoints Condition option.
// Chris H. Pappas and William H. Murray, 2000
//

#include <iostream>

using namespace std;

class A {
  public:
    void method( int iValue );
};

void main( void )
{
  A instance_A,
	instance_B,
	instance_n;

    instance_A.method( 55 );
	instance_B.method( 10 );
  //....
	instance_n.method( 22 );
}

void A::method(int iValue)
{
  cout << iValue << endl;
}