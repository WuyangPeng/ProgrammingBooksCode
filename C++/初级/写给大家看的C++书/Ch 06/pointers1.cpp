// pointers1.cpp - Script 6.3

#include <iostream>

int main() {

	// Create some variables.
	int a = -12;
	float b = 78.53;
	char c = 'D';
	unsigned long d = 1904856026;
	int e = 9002356;
	
	// Create matching pointers.
	int *aPointer = &a;
	float *bPointer = &b;
	char *cPointer = &c;
	unsigned long *dPointer = &d;
	int *ePointer = &e;
	
	// Print the addresses.
	std::cout << "The address of a is "
	<< reinterpret_cast<unsigned long>(aPointer) << "\n";
	std::cout << "The address of b is "
	<< reinterpret_cast<unsigned long>(bPointer) << "\n";
	std::cout << "The address of c is "
	<< reinterpret_cast<unsigned long>(cPointer) << "\n";
	std::cout << "The address of d is "
	<< reinterpret_cast<unsigned long>(dPointer) << "\n";
	std::cout << "The address of e is "
	<< reinterpret_cast<unsigned long>(ePointer) << "\n";

	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();

	return 0;
	
} // End of the main() function.
