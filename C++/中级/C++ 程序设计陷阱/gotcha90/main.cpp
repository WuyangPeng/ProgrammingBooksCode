#include <memory>
#include <string>
#include <iostream>
#include "container.h"
#include "list.h"

template <typename T>
void print( Container<T> &c ) {
    std::auto_ptr< Iter<T> > i( c.genIter() );
    for( i->reset(); !i->done(); i->next() )
        std::cout << i->get() << std::endl;
}

int main() {
	std::auto_ptr< List<int> > c1( new List<int> );
	for( int i = 0; i < 10; ++i )
		c1->insert( i );
	print( *c1 );
	
	std::auto_ptr< Container<std::string> > c2( new List<std::string> );
	c2->insert( "Andrei" );
	c2->insert( "Dan" );
	c2->insert( "Herb" );
	c2->insert( "Scott" );
	print( *c2 );
	
	std::auto_ptr< Container<std::string> > c3( c2->clone() );
	print( *c3 );
	
	extern void victimize();
	victimize();
	
	return 0;
}
