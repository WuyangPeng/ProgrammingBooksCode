// currency.cpp - Script 5.3

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
 * one float and one unsigned int.
 * The unsigned int has a default value of 1.
 * Function returns no value.
 */
void dollarsToEuros(float rate, unsigned dollars = 1);

// Start the main function.
int main() {

	// Declare the variables for the user input.
	float conversionRate = 0.832339; // $1 = 0.832339 Euros
	unsigned dollarsIn;
	
	// Show the exchange rate by calling the function.
	dollarsToEuros(conversionRate);
	
	// Prompt the user and take US dollars input.
	std::cout << "Enter a US dollar amount (without the dollar sign, commas or a decimal): [####] ";
	std::cin >> dollarsIn;
	
	// Show the conversion by calling the function.
	dollarsToEuros(conversionRate, dollarsIn);
	
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


// Define the dollarsToEuros() function.
void dollarsToEuros(float rate, unsigned dollars) {

	// Adjust the formatting.
	std::cout.setf(std::ios_base::fixed);
	std::cout.setf(std::ios_base::showpoint);
	std::cout.precision(2);
	
	// Print the results.
	std::cout << "\n$" << dollars 
	<< " US = " << (rate * dollars)
	<< " Euros.\n\n";
	
} // End of the dollarsToEuros() function.
