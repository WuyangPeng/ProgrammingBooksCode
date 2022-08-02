// memory.cpp - Script 11.1

#include <iostream>

int main() {

	// Declare a variable i that
	// is a pointer to int.
	int *i;
	
	// Allocate memory for an int. 
	// Assign the addres to i.
	i = new int;
	
	// Print the address.
	std::cout << "Address of allocated memory is " << i << "\n";
	
	// Return the memory to the pool.
	delete i;
	i = NULL;
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;

}
