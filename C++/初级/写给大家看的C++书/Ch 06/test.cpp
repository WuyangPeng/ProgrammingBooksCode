// test.cpp - Script 6.7

#include <iostream>

// Function prototype.
// Function takes two arguments.
// Function returns no values.
void changeVar(int myVar, int newValue);

int main() {

	// Create a new variable.
	int myNum = 20;
	
	// Print its current value.
	std::cout << "myNum is "
	<< myNum << "\n";

	// Call the function.
	changeVar(myNum, 90);

	// Print its value again.
	std::cout << "After calling the function, myNum is now "
	<< myNum << "\n";
		
	return 0;

} // End of the main().

// Function definition.
void changeVar(int myVar, int newValue) {

	// Assign the new value to the variable.
	myVar = newValue;
	
} // End of changeVar().
