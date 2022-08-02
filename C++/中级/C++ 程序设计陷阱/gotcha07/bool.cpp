#include <iostream>

typedef unsigned short Bits;

inline Bits repeated( Bits b, Bits m )
	{ return b & m & (b & m)-1; }


void dowop1( Bits options ) {
	int ctr = 0;
	for( int i = 0; i < 8; ++i )
	    if( options & 1<<(8+i) )
	        if( ctr++ ) {
	            std::cerr << "Too many options selected" << std::endl;
	            break;
	        }
}

void dowop2( Bits options ) {
	if( repeated( options, 0XFF00 ) )
	    std::cerr << "Too many options selected" << std::endl;
}

void boolTest() {
	std::cout << "===  bool test  ===" << std::endl;
	Bits opts[] = { 0x0000, 0x1000, 0x1011, 0x2100, 0xf000 };
	for( int i = 0; i < sizeof(opts)/sizeof(opts[0]); ++i ) {
		std::cerr << "Options: " << std::hex << opts[i] << std::endl;
		dowop1( opts[i] );
		dowop2( opts[i] );
	}
}
