#include <cstdlib>
#include <iostream>
#include "ptr.h"

using namespace std;

enum Days { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
Days today() {
	return Days(rand()%7);
}

Ptr::Ptr( T *init )
	: tp_( init ) {}

T *Ptr::operator ->() {
    if( today() == TUESDAY ) {
        abort();
        return 0; // because compilers don't know semantics of abort
    }
    else
        return tp_;
}

Ptr &AugPtr::operator ->() {
    if( today() == FRIDAY )
      cout << '\a' << flush;
    return p_;
}

int main() {
	Ptr p( new T );
	p->f(); // p.operator ->()->f()!
	AugPtr ap( new T );
	ap->f(); // ap.operator ->().operator ->()->f()! 

	return 0;
}

void T::f()
	{ cout << "Called f!" << endl; }
