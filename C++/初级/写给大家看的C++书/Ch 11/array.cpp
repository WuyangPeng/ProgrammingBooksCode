// array.cpp - Script 11.3

#include <iostream>

#include <string>

int main() {

	// Get the number of elements to allocate
	// from the user.
	unsigned int count = 0;
	std::cout << "Number of elements to allocate? ";
	std::cin >> count;
	
	// Allocate the memory.
	int *x = new int[count];
	
	// Initialize the array.
	for (int i = 0; i < count; i++) {
		x[i] = count - i;
	}

	// Print the array.
	for (int i = 0; i < count; i++) {
		std::cout << "The value of x[" 
		<< i << "] is " << x[i] << "\n";
	}

	// Free the memory. 
	// Must use delete[] not delete.
	delete[] x;
	x = NULL;
	
	std::cin.ignore(100,'\n'); // Ignore any garbage.
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
}
