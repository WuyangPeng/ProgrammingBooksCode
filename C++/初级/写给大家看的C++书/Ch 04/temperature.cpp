// temperature.cpp - Script 4.3

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Create constant to represent the 
	// numbers used in the calculation.
	const unsigned short SUBTRACT_NUM = 32;
	const float RATIO = 5.0/9.0;
	
	// Declare a variable for the user input.
	float fahrenheit; 
	
	// Prompt the user and take the input.
	std::cout << "Enter a temperature in degrees Fahrenheit: ";
	std::cin >> fahrenheit;
	
	// Create a blank line in the output.
	std::cout << "\n";
	
	// Print the conversion.
	std::cout << fahrenheit 
	<< " degrees Fahrenheit is equal to "
	<<  (fahrenheit - SUBTRACT_NUM) * RATIO
	<< " degrees Celsius.\n\n";
	
	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.