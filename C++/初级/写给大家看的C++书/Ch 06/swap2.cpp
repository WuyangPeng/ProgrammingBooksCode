// swap2.cpp - Script 6.9

#include <iostream>

// Function prototype.
// Function takes two arguments.
// Both arguments are integer references.
// Function returns no values.
void swap(int &first, int &second);

int main() {

	// Create the variables.
	int myNum1 = 23900;
	int myNum2 = -149;
	
	// Print their current values.
	std::cout << "At first, myNum1 is "
	<< myNum1 << " and myNum2 is "
	<< myNum2 << "\n\n";

	// Call the function.
	swap(myNum1, myNum2);

	// Print their values again.
	std::cout << "After calling the function, myNum1 is "
	<< myNum1 << " and myNum2 is "
	<< myNum2 << "\n\n";

	std::cout << "Press Enter or Return to continue.\n";
	std::cin.get();
	return 0;
		
} // End of the main().

// Function definition.
void swap(int &first, int &second) {

	// Need a temporary integer.
	int temp;
	
	// Assign the value of first to temp.
	temp = first;
	
	// Assign the value of second to first.
	first = second;

	// Assign the original value of first to second.
	second = temp;
	
} // End of swap().
