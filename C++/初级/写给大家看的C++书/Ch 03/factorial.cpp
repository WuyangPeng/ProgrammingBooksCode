// factorial.cpp - Script 3.8

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Numbers for calculations:
	unsigned short num = 8;
	unsigned long int sum = 1;
	unsigned short multiplier = 1;
	
	// Loop through each multiplier,
	// from 1 to num,
	// adding the result to the sum.
	while (multiplier <= num) {
	
		// Multiply current sum times the multiplier.
		sum *= multiplier;
		
		// Increment the multiplier.
		++multiplier;
		
	} // End of the while loop.
	
    // Print the results.
    std::cout << "The factorial of " << num
	<< " is " << sum << ".\n\n";
		
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.