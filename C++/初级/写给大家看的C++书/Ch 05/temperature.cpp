// temperature.cpp - Script 5.2

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

/* First function prototype.
 * Function takes no arguments.
 * Function returns no value.
 */
void promptAndWait();

/* Second function prototype.
 * Function takes two arguments:
 * one float and one char.
 * Function returns no value.
 */
void convertTemperature(float tempIn, char typeIn);

// Start the main function.
int main() {

	// Declare the variables for the user input.
	float temperatureIn;
	char tempTypeIn;
	
	// Prompt the user and take the input.
	std::cout << "Enter a temperature and indicate whether it is in degrees Fahrenheit or Celsius: [##.# C/F] ";
	std::cin >> temperatureIn >> tempTypeIn;
	
	// Check the tempTypeIn value.
	if  (
		(tempTypeIn == 'C') ||
	 	(tempTypeIn == 'c') ||
	  	(tempTypeIn == 'F') ||
	   	(tempTypeIn == 'f')
	   	) {
	   	
	   	// Call the conversion function.
	   	convertTemperature(temperatureIn, tempTypeIn);
	   	
	} else { // Invalid type, print an error message.
		std::cout << "The calculation could not be made due to invalid input.\n\n";
	}

	// Call the promptAndWait() function.
	promptAndWait();
		
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.


// Define the promptAndWait() function.
void promptAndWait() {
	std::cin.ignore(100, '\n');
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
} // End of the promptAndWait() function.


// Define the convertTemperature() function.
void convertTemperature(float tempIn, char typeIn) {

	// Create constants to represent the 
	// numbers used in the calculation.
	const unsigned short ADD_SUBTRACT = 32;
	const float RATIO = 5.0/9.0;
	
	// Declare the required variables.
	float tempOut;
	char typeOut;
	
	// Make the conversion based upon the value of typeIn.
	switch (typeIn) {
	
		case 'C':
		case 'c':
			// Calculation:
			tempOut = (tempIn / RATIO) + ADD_SUBTRACT;
			// For output purposes:
			typeOut = 'F';
			break;
			
		case 'F':
		case 'f':
			// Calculation:
			tempOut = (tempIn  - ADD_SUBTRACT) * RATIO;
			// For output purposes:
			typeOut = 'C';
			break;
			
	} // End of switch.
	
	// Print the results.
	std::cout << tempIn << " degrees " 
	<< typeIn << " is equal to "
	<< tempOut << " degrees " 
	<< typeOut << ".\n\n";
	
} // End of the convertTemperature() function.
