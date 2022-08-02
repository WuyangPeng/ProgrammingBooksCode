// arrays2.cpp - Script 6.5

#include <iostream>

int main() {

	// Number of array elements:
	const unsigned short ITEMS = 3;

	// Create three different arrays.
	int intArray[ITEMS] = {98, -486, 301589};
	char charArray[ITEMS] = {'A', 'B', 'C'};
	double doubleArray[ITEMS] = {3.14315614, 2.74546944, 7.349e14};

	// Create the pointers.
	int *intPtr = intArray;
	char *charPtr = charArray;
	double *doublePtr = doubleArray;

	// Print a heading.
	std::cout << "Array of integers:\n";
	
	// Print each array element's
	// values and address.
	for (int i = 0; i < ITEMS; ++i) {
		std::cout << *intPtr << " at "
		<< reinterpret_cast<unsigned long>(intPtr) << "\n";
		intPtr++;
	}
	
	// Repeat for charArray.
	std::cout << "\nArray of chars:\n";
	for (int i = 0; i < ITEMS; ++i) {
		std::cout << *charPtr << " at "
		<< reinterpret_cast<unsigned long>(charPtr) << "\n";
		charPtr++;
	}
	
	// Repeat for doubleArray.
	std::cout << "\nArray of doubles:\n";
	for (int i = 0; i < ITEMS; ++i) {
		std::cout << *doublePtr << " at "
		<< reinterpret_cast<unsigned long>(doublePtr) << "\n";
		doublePtr++;
	}
	
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;
	
} // End of the main() function.
