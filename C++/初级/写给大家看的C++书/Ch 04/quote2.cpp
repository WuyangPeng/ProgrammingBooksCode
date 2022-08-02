// quote2.cpp - Script 4.8

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// We need the fstream file in order
// to work with files.
#include <fstream>

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
	
	// Write the data to the file.
	
	// Define a file object.
	std::ofstream fileOutput("quotes.txt", std::ios::app);
	
	// If the file is open, record the data.
	if (fileOutput.is_open()) {
	
		// Write the data to the file.
		fileOutput << quote << "|" 
		<< speaker << "\n";
		
		// Close the stream.
		fileOutput.close();
		
		// Print a message.
		std::cout << "The data has been written to the file!\n";
	
	} else { // Couldn't open the file.
		std::cout << "The file could not be opened!\n";
		return 1; // Indicates a problem occurred.
	}
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;

} // End of the main() function.
