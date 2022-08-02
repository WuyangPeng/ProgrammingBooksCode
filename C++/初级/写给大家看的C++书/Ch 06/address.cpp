// address.cpp - Script 6.2

#include <iostream>

int main() {

	// Create some variables.
	int a = -12;
	float b = 78.53;
	char c = 'D';
	unsigned long d = 1904856026;
	int e = 9002356;
	
	// Print the addresses.
	std::cout << "The address of a is "
	<< (unsigned long) &a << "\n";
	std::cout << "The address of b is "
	<< (unsigned long) &b << "\n";
	std::cout << "The address of c is "
	<< (unsigned long) &c << "\n";
	std::cout << "The address of d is "
	<< (unsigned long) &d << "\n";
	std::cout << "The address of e is "
	<< (unsigned long) &e << "\n";

	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();

	return 0;
	
} // End of the main() function.
