// format.cpp - Script 2.4

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// Start the main function.
int main() {

	// Declare the variables to be used.
	unsigned short quantity;
	float price;
	float taxRate;
	
	// Assign values.
	quantity = 3;
	price = 19.95;
	taxRate = 0.05;

	// Print some introductory text.
	std::cout << "- Widget Cost Calculator-\n";
	
	// Print the variables.
	std::cout << "The cost of purchasing " 
	<< quantity	<< " widget(s) at a price of $" 
	<< price << ", with tax, comes to $";
	
	// Adjust the formatting.
	std::cout.setf(std::ios_base::fixed);
	std::cout.setf(std::ios_base::showpoint);
	std::cout.precision(2);

	// Print the calculation.
	std::cout << ( (quantity * price) + ((quantity * price) * taxRate) ) << ".\n";

	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.