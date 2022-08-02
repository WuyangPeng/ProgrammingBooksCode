// erase.cpp - Script 4.1

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Declare a variable for the user input.
	// Single character to store Yes (Y) or No (N).
	char answer; 
	
	// Prompt the user and take the input.
	std::cout << "Would you like to erase your hard drive? [Y/N] ";
	std::cin >> answer;
	
	// Create a blank line in the output.
	std::cout << "\n";
	
	// Print a message based upon the value.
	switch (answer) {
		case 'Y':
		case 'y':
			std::cout << "I'm thinking that's not such a good idea.\n\n";
			break;
		case 'N':
		case 'n':
			std::cout << "That's probably for the best.\n\n";
			break;
		default:
			std::cout << "Can't answer a simple Yes or No question, eh?\n\n";
			break;
	}
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
