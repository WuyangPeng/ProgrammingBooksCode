// increment.cpp - Script 3.7

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Two basic integers:
	int n1 = 1;
	int n2 = 1;

    // Print the current values.
    std::cout << "At first, n1 is " << n1
	<< " and n2 is " << n2
	<< ".\n";
	
	// Postfix arithmetic.
	n2 = n1++;
    std::cout << "After n2 = n1++, n1 is " << n1
	<< " and n2 is " << n2
	<< ".\n";
	n2 = n1--;
    std::cout << "After n2 = n1--, n1 is " << n1
	<< " and n2 is " << n2
	<< ".\n\n";
	
	// Reset the values.
	n1 = n2 = 1;
    std::cout << "Now, n1 is " << n1
	<< " and n2 is " << n2
	<< ".\n";
	
	// Prefix arithmetic.
	n2 = ++n1;
    std::cout << "After n2 = ++n1, n1 is " << n1
	<< " and n2 is " << n2
	<< ".\n";
	n2 = --n1;
    std::cout << "After n2 = --n1, n1 is " << n1
	<< " and n2 is " << n2
	<< ".\n\n";
	
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
