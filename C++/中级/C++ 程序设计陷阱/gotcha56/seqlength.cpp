#include <iostream>

template <typename N, typename In>
void seqLength( N &len, In b, In e ) {
    N n( 0 ); // this way, NOT "N n = 0;"
    while( b != e ) {
        ++n;
        ++b;
    }
    len = n;
}

class StrangeInt {
  public:
	StrangeInt( int a = 0 )
		: v_( a ) {}
	StrangeInt &operator =( const StrangeInt &rhs )
		{ v_ = rhs.v_; return *this; }
	StrangeInt &operator ++()
		{ ++v_; return *this; }
	const StrangeInt operator ++(int)
		{ StrangeInt temp( *this ); ++*this; return temp; }
	operator int() const
		{ return v_; }
  private:
	int v_;
	StrangeInt( const StrangeInt &that )
		: v_( that.v_ ) {}
	
};

int main() {
	int a[] = { 1,2,3,4,5,6};

	int len;
	seqLength( len, a, a+6 );
	std::cout << len << std::endl;

	StrangeInt len2;
	seqLength( len2, a, a+6 );
	std::cout << len2 << std::endl;

	return 0;
}
