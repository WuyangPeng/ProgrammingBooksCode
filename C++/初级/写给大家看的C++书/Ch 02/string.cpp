// string.cpp - Script 2.7

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file in order
// to work with the string type.
#include <string>

// Start the main function.
int main() {

	// Declare the variables to be used.
	std::string firstName, lastName, fullName;
	
	// Assign values.
	firstName = "Larry";
	lastName = "Ullman";
	
	// Define the full name.
	fullName = firstName + " " + lastName;
	
	// Say "hello".
	std::cout << "Hello, " << fullName << "!\n";
	
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.