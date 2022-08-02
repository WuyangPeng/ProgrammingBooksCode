// rectange1.cpp - Script 7.1

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Class declaration.
class Rectangle {

public:

	// Declare the attributes.
	unsigned width, height;

}; // Don't forget the semicolon!

// Start the main function.
int main() {

	// Create the necessary variables.
	unsigned width = 25;
	unsigned height = 14;

	// Print a little introduction.
	std::cout << "With a width of " << width
	<< " and a height of " << height << "...\n\n";
		
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
		
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
