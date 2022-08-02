#include "rawstorage.h"
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <memory>

typedef std::string T;

struct X {
	X() : t_( new T("C++") ) {}
	~X() { delete t_; }
	X( const X &that ) : t_( new T(*that.t_) ) {}
    X &operator =( const X &rhs ) {
        if( this != &rhs )
            { delete t_; t_ = new T(*rhs.t_); }
        return *this;
    }
    const T &get_t() const { return *t_; }
    T *t_;
    //...
};

std::ostream &operator <<( std::ostream &o, const X &x )
	{ return o << *x.t_; }

int main() {
	X x;
	X *buf = (X *)std::malloc( sizeof(X) ); // raw storage...
	X &rx = *buf; // foul trickery...
	//rx = x; // probable error!
	
	const int N = 12;
	X a[N];
	X *ary = (X *)std::malloc( N*sizeof(X) );
	//std::copy( a, a+N, ary ); // assign to raw storage!
	
	raw_storage_iterator<X *, X> ri( ary );
	std::copy( a, a+N, ri ); // works!
	
	std::copy( ary, ary+N, std::ostream_iterator<X>(std::cout,"\n") );

	return 0;
}
