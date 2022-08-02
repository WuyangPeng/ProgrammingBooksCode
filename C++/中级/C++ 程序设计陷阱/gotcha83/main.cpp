#include "cptr.h"
#include <string>
#include <vector>
#include <list>
#include "ptrlist.h"
#include <iostream>

template <class Container>
void releaseElems( Container &c ) {
    typedef typename Container::iterator I;
    for( I i = c.begin(); i != c.end(); ++i )
        delete *i;
}

int main() {
	using namespace std;
	
	const char *names[] = { "Ann", "Bob", "David", "Zoe" };
	const int n = sizeof(names)/sizeof(names[0]);
	
	vector< Cptr<string> > vs;
	for( int i = 0; i < n; ++i )
		vs.push_back( new string(names[i]) );
	
	list< Cptr<string> > ls;
	ls.push_back( new string( "Aarhus" ) );
	ls.push_back( vs[2] );
	ls.push_back( vs[3] );
	ls.push_back( new string( "Zygote" ) );
	
	
	PtrList<int> pli;
	pli.append( new int(1) );
	pli.append( new int(2) );
	pli.append( new int(3) );
	
	list<int *> lip;
	lip.push_back( new int(1) );
	lip.push_back( new int(2) );
	lip.push_back( new int(3) );
	lip.push_back( new int(4) );
	cout << lip.size() << endl;
	
	releaseElems( lip );
	cout << lip.size() << endl;
	
	return 0;
}
