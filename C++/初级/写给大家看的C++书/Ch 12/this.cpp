// this.cpp - Script 12.10

#include <iostream>

// Need the header file.
#include "header.h"


// Get the external variable.
extern unsigned short thatNum;

// Create a static variable.
static bool printMe = false;

int main() {

	// Create a local variable.
	unsigned short thisNum = 10;
	
	// Print the factorial of thisNum.
	std::cout  << thisNum << "! is equal to " << returnFactorial(thisNum) << "\n\n";
	
	// Print the factorial of thatNum.
	std::cout  << thatNum << "! is equal to " << returnFactorial(thatNum) << "\n\n";

	// Print the factorial of headerNum
	// (defined in header.h).
	std::cout  << headerNum << "! is equal to " << returnFactorial(headerNum) << "\n\n";

	// Should we say "hello"?
	if (printMe) {
		std::cout << "Hello!\n";
	}

	// Call the promptAndWait() function.
	promptAndWait();
	
	return 0;
	
} // End of main().

// Define the promptAndWait() function.
void promptAndWait() {

	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
} // End of the promptAndWait() function.

