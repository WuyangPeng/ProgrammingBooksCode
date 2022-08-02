// quote.cpp - Script 10.2

#include <iostream>

#include <string>

#include <fstream>

// Class declaration.
class StoreQuote {

public:
	// Constructor:
	StoreQuote(std::string filename);
	
	// Destructor:
	~StoreQuote();
	
	// Declare the methods.
	void inputQuote();
	void inputSpeaker();
	bool write(); 

private:
	// Declare the attributes.
	std::string quote, speaker;
	
	// Define a file object.
	std::ofstream fileOutput;
	

}; // Don't forget the semicolon!


// Define the constructor.
// Constructor opens the file.
StoreQuote::StoreQuote(std::string filename) {

	std::cout << "In the constructor, opening the file.\n";

	fileOutput.open(filename.c_str(), std::ios::app);

	// Assert that the file is open.
	assert(fileOutput.is_open());
	
	std::cout << "If this prints, the file must be open.\n";

}

// Define the destructor.
// Destructor closes the file.
StoreQuote::~StoreQuote() {

	std::cout << "In the destructor, closing the file.\n";

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

	std::cout << "In inputQuote(), quote is '" 
	<< quote << "'\n";

}

/* The method inputSpeaker() assigns the
 * speaker to the speaker attribute.
 * It takes no arguments.
 * It returns nothing. 
 */
void StoreQuote::inputSpeaker() {
	std::getline(std::cin, speaker);

	std::cout << "In inputSpeaker(), speaker is '" 
	<< speaker << "'\n";

}

/* The method write() returns a
 * boolean value indicating whether
 * or not the data is written to the file.
 * It takes no arguments.
 * It returns a boolean. 
 */
bool StoreQuote::write() {

	std::cout << "Inside the write() method.\n";

	if (fileOutput.is_open()) {
		
		std::cout << "Inside the write() method, the file is open.\n";

		// Write the data to the file.
		fileOutput << quote << "|" 
		<< speaker << "\n";
		return true;
	} else { // Couldn't open the file.

		std::cout << "Inside the write() method; the file isn't open.\n";

		return false; // Indicates a problem occurred.
	}
}


int main() {

	// Create a new object.
	StoreQuote quote("quotes.txt");

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
	
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

}
