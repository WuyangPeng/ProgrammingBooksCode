// cast.cpp - Script 2.5

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Declare the variables to be used.
	unsigned int miles = 192;
	float multiplier = 1.609344;
	float kilometers;
	
	// Calculate the kilometers.
	kilometers = miles * multiplier;

	// Print the results.
	std::cout << miles << " miles is approximately " 
	<< int(kilometers + 0.5) << " kilometers(s).\n";
	
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.