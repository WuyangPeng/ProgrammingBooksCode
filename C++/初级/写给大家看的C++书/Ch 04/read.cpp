// read.cpp - Script 4.9

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
	std::string line;
	
	// Define a file object.
	std::ifstream fileInput("quotes.txt");
	
	// If the file is open, read the data.
	if (fileInput.is_open()) {
	
		std::cout << "The following quotes have been recorded...\n\n";
		
		// Read in all data.
		while (std::getline(fileInput, line, '|')) { // Reads in a quote.
			
			// Print the quote.
			std::cout << line << "\n - ";
			
			// Get and print the speaker.
			std::getline(fileInput, line);
			std::cout << line << "\n\n";
			
		} // End of WHILE.
		
		// Close the stream.
		fileInput.close();
	
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
