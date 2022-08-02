// factorial.cpp - Script 10.1

#include <iostream>

// Need the climits file
// in order to know the maximum
// size of an unsigned long int.
#include <climits>

// Declare the class.
class Factorial {
public:
	Factorial(unsigned short num = 1);
	bool inRange();
	unsigned long getFactorial();
	
private:
	unsigned short num;
	
}; // End of class.

// Implement the methods:
Factorial::Factorial (unsigned short num) {
	this->num = num;
}

bool Factorial::inRange() {

	// Maximum possible value for validation.
	unsigned long max = ULONG_MAX;

	// Loop from 1 to num,
	// dividing the number from max.
	for (int i = num; i >= 1; --i) {
	
		max /= i;
		
	} // End of the for loop.
	
	// Return a true/false value.
	if (max < 1) {
		return false;
	} else {
		return true;
	}
	
} // End of the factorialInRange() function.

unsigned long Factorial::getFactorial() {

	// For the factorial.
	unsigned long sum = 1;
	
	// Loop from 1 to num,
	// adding the result to the sum.
	for (int i = 1; i <= num; ++i) {
	
		// Multiply current sum times i.
		sum *= i;
		
	} // End of the for loop.
	
	return sum;
	
} // End of the returnFactorial() function.

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
	
	// Create the object.
	Factorial f(numberIn);
	
	// Print the results.
	if (f.inRange()) {
	
		std::cout << "The factorial of " << numberIn
		<< " is " << f.getFactorial() << ".\n\n";
		
	} else { // Out of range.
	
		std::cout << "The factorial of " << numberIn
		<< " cannot be calculated on this computer.\n" 
		<< "Please use a smaller integer and try again.\n\n";
		
	}
		
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;
	
} // End of the main() function.
