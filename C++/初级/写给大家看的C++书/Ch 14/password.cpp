// password.cpp - Script 14.2

#include <iostream>
#include <string>

// For the C toupper() function.
#include <cctype>

// Start the main function.
int main() {

	// Declare the necessary variables.
	std::string word1, word2, password, insert;
	char punc;
	
	// Prompt the user for the data.
	std::cout << "Enter two words and another character (like punctuation or a single number), with spaces between each: [word word !]\n";
	std::cin >> word1 >> word2 >> punc;
	
	// Validate and reprompt, if you want.
	
	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
	
	// Determine the larger word.
	// Larger word will be the base of the password.
	if (word1.size() > word2.size()) {
		password = word1;
		insert = word2;
	} else {
		password = word2;
		insert = word1;
	}
	
	// Loop through the smaller word,
	// inserting its letters into password.
	for (int i = 0; i < insert.size(); ++i) {
		
		// Capitalize the inserted letter.
		password.insert( (i*2), 1, toupper(insert[i]));
		
	}
	
	// Add two copies of the character somewhere.
	password.replace ((password.size()/2) , 1, 2, punc);

	// Print the password.
	std::cout << "\nYour password is '" 
	<< password << "'.\n\n";

	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

} // End of the main() function.
