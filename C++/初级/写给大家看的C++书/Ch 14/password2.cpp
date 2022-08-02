// password2.cpp - Script 14.7

#include <iostream>
#include <string>

// For the C toupper() function.
#include <cctype>

// Start the main function.
int main(int argc, char *argv[]) {

	// This program expect three command line arguments
	// plus the program's name (so four total).
	if (argc == 4) { // OK to proceed
	
		// Assign the arguments to variables.
		std::string word1 = argv[1];
		std::string word2 = argv[2];
		char punc = argv[3][0]; // Assign just 1 character.
		
		// Need a couple more strings.
		std::string password, insert;
	
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
		
	} else { // Wrong arguments.
		std::cout << "\nThis program, "
		<< argv[0] << ", expects to receive 3 arguments: two words and a single character, each separated by a space.\n\n";
	}
	
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

} // End of the main() function.
