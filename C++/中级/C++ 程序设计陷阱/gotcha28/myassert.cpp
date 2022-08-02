#include "myassert.h"
#include <vector>
#include <deque>

template <typename T>
bool process( const T & )
	{ return false; }

template <class Cont>
void doit( Cont &c, int index ) {
    assert( index >= 0 && index < c.size() ); // #1
    assert( process( c[index] ) ); // #2
    //...
}

int main() {

	int x = 23;
	assert( x-12<2 );
	
	std::vector<int> aVector(10);
	doit( aVector, 9 );
	
	std::deque<double> aList;
	//doit( aList, 1 ); // uncomment to have runtime error
						// not caught by assertion
	
	return 0;
}
