// pointers2.cpp - Script 6.4

#include <iostream>

int main() {

	// Create some variables.
	int a = -12;
	float b = 78.53;
	char c = 'D';
	unsigned long d = 1904856026;
	std::string e = "arglebargle";
	
	// Print the values of the variables.
	std::cout << "The value of a is initially "
	<< a << "\n";
	std::cout << "The value of b is initially "
	<< b << "\n";
	std::cout << "The value of c is initially "
	<< c << "\n";
	std::cout << "The value of d is initially "
	<< d << "\n";
	std::cout << "The value of e is initially "
	<< e << "\n";
	
	// Create matching pointers.
	int *aPointer = &a;
	float *bPointer = &b;
	char *cPointer = &c;
	unsigned long *dPointer = &d;
	std::string *ePointer = &e;
	
	// Change the values using the pointers.
	*aPointer = 5462;
	*bPointer = -3.143022489;
	*cPointer = 'Z';
	*dPointer = 1604326026;
	*ePointer = "foofarah";

	// Print the values of the variables again.
	std::cout << "The value of a is now "
	<< a << "\n";
	std::cout << "The value of b is now "
	<< b << "\n";
	std::cout << "The value of c is now "
	<< c << "\n";
	std::cout << "The value of d is now "
	<< d << "\n";
	std::cout << "The value of e is now "
	<< e << "\n";
	
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();

	return 0;
	
} // End of the main() function.
