#include <iostream>
#include "cbridge.h"

int main() {
	C a( 12 );
	std::cout << a.get_a() << " " << a.get_b() << std::endl;
	
	return 0;
}
