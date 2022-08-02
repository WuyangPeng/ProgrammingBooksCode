// arrays1.cpp - Script 6.1

#include <iostream>

int main() {

	// Create a constant representing the 
	// number of array elements.
	const unsigned short ITEMS = 10;
	
	// Create an array.
	int numbers[ITEMS];

	std::cout << "You will be prompted to enter " << ITEMS << " numbers. They can be positive or negative but cannot contain decimals or commas.\n\n";
	
	// Create the loop that takes the input.
	// The loop should run once for each array element.
	for (int i = 0; i < ITEMS; ++i) {
	
		// Prompt the user.
		std::cout << "Enter a number: ";
		
		// Take the input, validate, and reprompt if necessary.
		while (!(std::cin >> numbers[i])) {
		
			// Problem! Clear cin and reprompt.
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Please enter a valid integer: ";
			
		} // End of WHILE.
		
	} // End of FOR.
	
	// Print another message.
	std::cout << "The following numbers have been recorded:\n";
	
	// Need a total variable.
	int total = 0;
	
	// Loop through the array again.
	for (int i = 0; i < ITEMS; ++i) {
	
		// Print the number.
		std::cout << numbers[i] << "\n";
		
		// Add to the total.
		total += numbers[i];
		
	} // End of FOR.
	
	// Print the total and average.
	std::cout << "The sum of the numbers is "
	<< total << "\nThe average of the numbers is "
	<< (float(total)/ITEMS) << "\n\n";
		
	std::cin.ignore(100, '\n');
	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;
	
} // End of the main() function.
