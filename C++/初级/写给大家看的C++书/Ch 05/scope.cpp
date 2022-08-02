// scope.cpp - Script 5.6

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the string file
// for the string functionality.
#include <string>

/* First function prototype.
 * Function takes no arguments.
 * Function returns no value.
 */
void promptAndWait();

/* Second function prototype.
 * Function takes no arguments.
 * Function returns no value.
 */
void nameChange();

// Declare a global variable.
std::string gName;

// Start the main function.
int main() {

	// Declare a local variable.
	std::string name = "Andi";
	
	// Assign a value to the global variable.
	gName = name;

	// Print the current values.
	std::cout << "At first, name is " << name << " and gName is " << gName << ".\n";
	
	// Call the function.
	nameChange();
	
	// Print the values again.
	std::cout << "After the function, name is " << name << " and gName is " << gName << ".\n";
		
	// Call the promptAndWait() function.
	promptAndWait();
		
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.


// Define the promptAndWait() function.
void promptAndWait() {
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
} // End of the promptAndWait() function.


// Define the noNameChange() function.
void nameChange() {

	// Declare a local variable.
	std::string name = "Larry";
	
	// Print the values.
	std::cout << "In the function, name is " << name << " and gName is initially " << gName << ".\n";
	
	// Assign a value to the global variable.
	gName = name;
	
	// Print the values again.
	std::cout << "In the function, name is " << name << " and gName is now " << gName << ".\n";
	
} // End of the noNameChange() function.
