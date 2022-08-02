// char.cpp - Script 2.6

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Declare the variables to be used.
	char letter = 'N';
	char tab = '\t';
	char quote = '\'';
	
	// Print the characters with numeric equivalents.
	std::cout << "It's a question of character:\n";
	std::cout << letter << " is equivalent to " << int(letter) << ".\n";
	std::cout << tab << " is equivalent to " << int(tab) << ".\n";
	std::cout << quote << " is equivalent to " << int(quote) << ".\n";
	
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.