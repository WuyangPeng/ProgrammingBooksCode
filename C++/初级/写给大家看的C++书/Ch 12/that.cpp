// that.cpp - Script 12.9

// Need the header file.
#include "header.h"


// Create a variable.
unsigned short thatNum = 8;

// Create a normal variable with
// the same name as the static
// variable in this.cpp
bool printMe = true;

// Implement the returnFactorial() function.
unsigned long returnFactorial(unsigned short num) {

	unsigned long sum = 1;

	// Loop from 1 to num,
	// adding the result to the sum.
	for (int i = 1; i <= num; ++i) {
	
		// Multiply current sum times i.
		sum *= i;
		
	} // End of the for loop.
	
	if (printMe) {
		return sum;
	} else {
		return 0;
	}
	
} // End of the returnFactorial() function.
