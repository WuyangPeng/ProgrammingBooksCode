#include "c12.h"

int main() {
	C1 c1;
	c1.f1(0);
	c1.f1();


	C2 c2;
	c2.f2(0);
	c2.f2();

	//void (C1::*pmf1)() = &C1::f1; //error!
	void (C2::*pmf2)() = &C2::f2;
	
	return 0;
}
