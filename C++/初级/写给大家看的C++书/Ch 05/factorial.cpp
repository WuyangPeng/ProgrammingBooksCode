// factorial.cpp - Script 5.4

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

/* First function prototype.
 * Function takes no arguments.
 * Function returns no value.
 */
void promptAndWait();

/* Second function prototype.
 * Function takes one argument, an unsigned short integer.
 * Function returns an unsigned long integer.
 */
unsigned long returnFactorial(unsigned short num);

// Start the main function.
int main() {

	// Declare the variable for the user input.
	unsigned short numberIn;
	
	// Prompt the user and take the input.
	std::cout << "Enter a small, positive integer: [##] ";
	std::cin >> numberIn;
	
	// Validate the input? 
	// Check that the input is between 1 and, say, 13?
		
    // Print the results.
    std::cout << "The factorial of " << numberIn
	<< " is " << returnFactorial(numberIn) << ".\n\n";
		
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


// Define the returnFactorial() function.
unsigned long returnFactorial(unsigned short num) {

	unsigned long sum = 1;

	// Loop from 1 to num,
	// adding the result to the sum.
	for (int i = 1; i <= num; ++i) {
	
		// Multiply current sum times i.
		sum *= i;
		
	} // End of the for loop.
	
	return sum;
	
} // End of the returnFactorial() function.
