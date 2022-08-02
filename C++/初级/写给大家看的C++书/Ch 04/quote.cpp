// quote.cpp - Script 4.6

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// Start the main function.
int main() {

	// Declare the necessary variables.
	std::string quote, speaker; 
	
	// Prompt the user for the quotation.
	std::cout << "Enter a quotation (without quotation marks):\n";
	std::getline(std::cin, quote);

	// No extraneous input to be discarded
	// because all input is assigned to the string!
	
	// Prompt the user for the quotation's author.
	std::cout << "Enter the person to whom this quote is attributed:\n";
	std::getline(std::cin, speaker);

	// Create a blank line in the output.
	std::cout << "\n";
	
	// Repeat the input back to the user.
	std::cout << "The following quote has been received...\n\n"	
	<<  quote << "\n-" << speaker << "\n\n";
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
