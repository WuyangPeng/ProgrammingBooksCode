#include <iostream>

struct B {
	B() { a = 1; b = 2; }
	int a, b;
};

void apply( B array[], int length, void (*f)( B & ) ) {
    for( int i = 0; i < length; ++i )
        f( array[i] );
}

void somefunc( B &b ) {
	std::cout << "B::a = " << b.a << " , B::b = " << b.b << std::endl;
}

struct D : public B {
	D() { c = 3; d = 4; }
	int c, d;
};

int main() {
	D *dp = new D[3];
	apply( dp, 3, somefunc ); // disaster!

	return 0;
}
