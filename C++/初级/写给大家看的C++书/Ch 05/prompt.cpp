// prompt.cpp - Script 5.1

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

/* Function prototype.
 * Function takes no arguments.
 * Function returns no value.
 */
void promptAndWait();

// Start the main function.
int main() {

	// Do something.
	std::cout << "The main() function is doing something...\n\n";
		
	// Call the promptAndWait() function.
	promptAndWait();
	
	// Return the value 0 to indicate no problems.
	return 0;

} // End of the main() function.


// Define the promptAndWait() function.
void promptAndWait() {

	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
} // End of the promptAndWait() function.
