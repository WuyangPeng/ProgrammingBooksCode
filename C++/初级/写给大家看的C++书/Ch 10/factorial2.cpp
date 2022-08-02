// factorial2.cpp - Script 10.3

#include <iostream>

// Need the climits file
// in order to know the maximum
// size of an unsigned long int.
#include <climits>

// Function prototype.
// Function takes one argument, an unsigned short int.
// Function returns an unsigned long int.
// Function can throw an exception.
unsigned long returnFactorial(unsigned short num) throw (const char *);

// Start the main() function.
int main() {

	// Declare the variable for the user input.
	unsigned short numberIn = 0;
	
	// Prompt the user, take, and validate the input.
	std::cout << "Enter a small, positive integer: [##] ";
	while (!(std::cin >> numberIn) || (numberIn < 1)) {
	
		// Problem! Clear cin and reprompt.
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Please enter a small, positive integer: [##] ";
		
	} // End of WHILE.

	// Discard any extraneous input.
	std::cin.ignore(100, '\n');
	
	// Try to calculate the factorial.
	try {
	
		unsigned long factorial = returnFactorial(numberIn);
		std::cout << "The factorial of " << numberIn
		<< " is " << factorial << ".\n\n";
	
	}
	
	// Catch any exception.
	catch (const char *e) {
		std::cout << e;
	}
			
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;
	
} // End of the main() function.

// Define the function.
unsigned long returnFactorial(unsigned short num) throw (const char *) {

	// For the factorial.
	unsigned long sum = 1;
	
	// Maximum possible value for validation.
	unsigned long max = ULONG_MAX;

	// Loop from 1 to num,
	// adding the result to the sum.
	// Divide the result from max.
	for (int i = 1; i <= num; ++i) {
	
		sum *= i;
		max /= i;
		
	} // End of the for loop.

	if (max < 1) { // Throw an exception.
	
		throw "The factorial cannot be calculated on this computer.\nPlease use a smaller integer and try again.\n\n";
		
	} else { // Return the factorial.
	
		return sum;
		
	}
	
} // End of the returnFactorial() function.

