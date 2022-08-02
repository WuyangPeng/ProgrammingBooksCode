// substring.cpp - Script 14.1

#include <iostream>

#include <string>

// Start the main function.
int main() {

	// Declare the necessary variables.
	std::string filename; 
	
	// Prompt the user for the filename.
	// Alternatively read the filename in
	// from a directory.
	std::cout << "Enter the file's name: [filename.ext] ";
	std::getline(std::cin, filename);
	
	// Find the length of the filename.
	unsigned short length = filename.size();
	
	// The extension is the last three letters.
	std::string ext = filename.substr( (length - 3), 3);

	// Print a message.
	std::cout << "The file '" 
	<< filename.substr(0, (length - 4)) 
	<< "' can probably be opened using ";
	
	// Print the associated application
	// based upon the extension.
	if (ext == "doc") {
		std::cout << "Microsoft Word";
	} else if (ext == "xls") {
		std::cout << "Microsoft Excel";
	} else if (ext == "pdf") {
		std::cout << "Adobe Acrobat Reader";
	} else if (ext == "jpg") {
		std::cout << "an image application";
	} else { // No idea.
		std::cout << "some unknown application";
	}

	// Finish the sentence.
	std::cout << ".\n";

	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;

} // End of the main() function.
