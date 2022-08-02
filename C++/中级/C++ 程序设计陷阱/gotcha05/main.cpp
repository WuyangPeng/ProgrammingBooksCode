#include <iostream>
#include <string>
#include "array.h"

template <typename A>
void print( const A &a, int n ) {
	using namespace std;
	cout << "[ ";
	for( int i = 0; i < n; ++i )
		cout << a[i] << " ";
	cout << ']' << endl;
}

int main() {
	Array<int,12> ia;
	ia = 7;
	print( ia, 12 );
	ia[8] = ia[0] = 2;
	ia[3] = ia[0];
	print( ia, 12 );
	ia = 0;
	print( ia,12 );
	ia.setAll( -1 );
	print( ia, 12 );
	
	Array<std::string,5> sa;
	sa = "Dorian";
	print( sa, 5 );
	sa[4] = sa[0] = "Edgar";
	sa[3] = sa[0];
	print( sa, 5 );
	sa = "Annabel";
	print( sa,5 );
	
	return 0;
}
