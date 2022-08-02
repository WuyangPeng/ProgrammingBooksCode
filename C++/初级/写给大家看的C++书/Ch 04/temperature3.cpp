// temperature3.cpp - Script 4.7

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Create constant to represent the 
	// numbers used in the calculation.
	const unsigned short ADD_SUBTRACT = 32;
	const float RATIO = 5.0/9.0;
	
	// Declare the variables for the user input
	// and for the determined output.
	float temperatureIn, temperatureOut;
	char tempTypeIn, tempTypeOut;
	
	// Prompt the user and take the input
	// for the temperature.
	std::cout << "Enter a temperature: [##.#] ";
	while (!(std::cin >> temperatureIn)) {
	
		// Problem! Clear cin and reprompt.
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Please enter a valid temperature: [##.#] ";
		
	} // End of WHILE.

	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
		
	// Prompt the user and take the input
	// for the temperature type.
	do {
		std::cout << "Is this in degrees Fahrenheit or Celsius? [F/C] ";
		std::cin >> tempTypeIn;
	
		// Discard any extraneous input.
		std::cin.ignore(100, '\n');
		
	} while ( // tempTypeIn doesn't have a valid value.
		(tempTypeIn != 'C') &&
	 	(tempTypeIn != 'c') &&
	  	(tempTypeIn != 'F') &&
	   	(tempTypeIn != 'f')
	);
	
	// Create a blank line in the output.
	std::cout << "\n";
	
	// Make the conversion based upon the value of tempTypeIn.
	switch (tempTypeIn) {
	
		case 'C':
		case 'c':

			// Calculation:
			temperatureOut = (temperatureIn / RATIO) + ADD_SUBTRACT;

			// For output purposes:
			tempTypeOut = 'F';
			tempTypeIn = 'C';
			
			break;
			
		case 'F':
		case 'f':
			
			// Calculation:
			temperatureOut = (temperatureIn  - ADD_SUBTRACT) * RATIO;

			// For output purposes:
			tempTypeOut = 'C';
			tempTypeIn = 'F';

			break;
			
		default:
			tempTypeOut = 'E'; // Error.
			break;
	} // End of switch.
	
	// If the temperature type inputted is valid,
	// then print the results of the calculation.
	if (tempTypeOut != 'E') {
		std::cout << temperatureIn << " degrees " 
		<< tempTypeIn << " is equal to "
		<<  temperatureOut << " degrees " 
		<< tempTypeOut << ".\n\n";
	} else { // Invalid input.
		std::cout << "The calculation could not be made due to invalid input.\n\n";
	}
	
	// Wait for the user to press Enter or Return.
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
