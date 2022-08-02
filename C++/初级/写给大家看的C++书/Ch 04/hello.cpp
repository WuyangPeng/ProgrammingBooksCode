// hello.cpp - Script 4.4

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Start the main function.
int main() {

	// Declare the necessary variables.
	std::string firstName, lastName; 
	
	// Prompt the user for their first name.
	std::cout << "Enter your first name: ";
	std::cin >> firstName;

	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
	
	// Prompt the user for their last name.
	std::cout << "Enter your last name: ";
	std::cin >> lastName;

	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
	
	// Create a blank line in the output.
	std::cout << "\n";
	
	// Say hello and print a letter count.
	std::cout << "Hello, "	
	<<  firstName << " " << lastName 
	<< ". Did you know that there are "
	<< (firstName.size() + lastName.size()) 
	<< " letters in your name?\n\n";
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
