// quote.cpp - Script 7.5

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

// We need the fstream file in order
// to work with files.
#include <fstream>


// Class declaration.
class StoreQuote {

public:
	// Declare the attributes.
	std::string quote, speaker;
	
	// Define a file object.
	std::ofstream fileOutput;
	
	// Constructor:
	StoreQuote();
	
	// Destructor:
	~StoreQuote();
	
	// Declare the methods.
	void inputQuote();
	void inputSpeaker();
	bool write(); 

}; // Don't forget the semicolon!

// Define the constructor.
// Constructor opens the file.
StoreQuote::StoreQuote() {
	fileOutput.open("quotes.txt", std::ios::app);
}

// Define the destructor.
// Destructor closes the file.
StoreQuote::~StoreQuote() {
	fileOutput.close();
}

// Define the methods for the StoreQuote class.

/* The method inputQuote() assigns the
 * quote to the quote attribute.
 * It takes no arguments.
 * It returns nothing. 
 */
void StoreQuote::inputQuote() {
	std::getline(std::cin, quote);
}

/* The method inputSpeaker() assigns the
 * speaker to the speaker attribute.
 * It takes no arguments.
 * It returns nothing. 
 */
void StoreQuote::inputSpeaker() {
	std::getline(std::cin, speaker);
}

/* The method write() returns a
 * boolean value indicating whether
 * or not the data is written to the file.
 * It takes no arguments.
 * It returns a boolean. 
 */
bool StoreQuote::write() {

	if (fileOutput.is_open()) {
	
		// Write the data to the file.
		fileOutput << quote << "|" 
		<< speaker << "\n";
		
		return true;
		
	} else { // Couldn't open the file.
		return false; // Indicates a problem occurred.
	}
}


// Start the main function.
int main() {

	// Create a new object.
	StoreQuote quote;

	// Prompt the user for the quotation and take it.
	std::cout << "Enter a quotation (without quotation marks):\n";
	quote.inputQuote();
	
	// Prompt the user for the quotation's author and take it.
	std::cout << "Enter the person to whom this quote is attributed:\n";
	quote.inputSpeaker();
	
	// Record the data.
	if (quote.write()) {
	
		// Print a message.
		std::cout << "The data has been written to the file!\n";
	
	} else { // Couldn't open the file.
		std::cout << "The data could not be written!\n";
		return 1; // Indicates a problem occurred.
	}
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;

} // End of the main() function.
