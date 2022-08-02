// main.cpp - Script 12.7

#include <iostream>

// Include the Rational.h
// header file.
#include "Rational.h"

int main() {

	// Create two Rationals: 3/5 and 3/4.
	myMath::Rational f1(2,6);
	myMath::Rational f2(8,12);

	// Test addition.
	std::cout << f1 << " + " << f2 << " == " << (f1+f2) << "\n";

	// Test subtraction.
	std::cout << f1 << " - " << f2 << " == " << (f1-f2) << "\n";

	// Test multiplication.
	std::cout << f1 << " * " << f2 << " == " << (f1*f2) << "\n";

	// Test division.
	std::cout << f1 << " / " << f2 << " == " << (f1/f2) << "\n";
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
	
} // End of main().

