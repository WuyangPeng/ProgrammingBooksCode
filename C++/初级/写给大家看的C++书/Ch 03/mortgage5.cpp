// mortgage5.cpp - Script 3.5

// We need the iostream file in order
// to use cout and cin.
#include <iostream>

// We need the cmath file in order
// to use the pow() function.
#include <cmath>

// Start the main function.
int main() {

	// Set basic values.
	unsigned long loanAmount = 150000; // financed amount
	float annualInterestRate = 6.0; // 6% interest
	unsigned short loanLength = 15; // 30 years
	const unsigned short MONTHS_IN_YEAR = 12; 
	bool approved = false; // Not approved for a loan
	
	// Establish comparison values as constants.
	const unsigned short LOW_MAX = 500;
	const unsigned short MODERATE_MAX = 1500;
	const unsigned short PRICEY_MAX = 3000;
	const unsigned short EXPENSIVE_MAX = 10000;
	
	// Perform basic calculations.
	float monthlyInterestRate = annualInterestRate / MONTHS_IN_YEAR; // Monthly rate
	monthlyInterestRate = monthlyInterestRate/100; // Monthly rate as a decimal
	unsigned short numberPayments = loanLength * MONTHS_IN_YEAR; 

	// Mortgage payment calculation, broken down into subparts.
	float monthlyPayment = 1 - pow((1 + monthlyInterestRate), -numberPayments);
	monthlyPayment = monthlyInterestRate/monthlyPayment;
	monthlyPayment = loanAmount * monthlyPayment;

    // Print the basic information.
    std::cout << "Assuming a loan in the amount of $" << loanAmount
	<< ", at " << annualInterestRate 
	<< "% interest, over " << loanLength
	<< " years, the monthly payment would be $";
		
	// Adjust the formatting.
	std::cout.setf(std::ios_base::fixed);
	std::cout.setf(std::ios_base::showpoint);
	std::cout.precision(2);
	
	// Print the monthly payment.
	std::cout << monthlyPayment << ".\n\n";
	
	// How expensive is the monthly payment?
	if (monthlyPayment < LOW_MAX) {
		std::cout << "Your mortgage payment is a steal!\n\n";
	} else if (monthlyPayment < MODERATE_MAX) {
		std::cout << "Your mortgage payment seems resonable.\n\n";
	} else if (monthlyPayment < PRICEY_MAX) {
		std::cout << "The budget is getting a little tight.\n\n";
	} else if (monthlyPayment < EXPENSIVE_MAX) {
		std::cout << "Ouch!\n\n";
	} else {
		std::cout << "I hope your name is 'Trump'!\n\n";
	}
	
	// Are they approved?
	std::cout << "According to our information, you ";
	std::cout << ((approved) ? "are" : "are NOT");
	std::cout << " already approved for this loan.\n";
	
	// Let the reader know what to do next.
	std::cout << "Press Enter or Return to continue.\n";
	
	// Wait for the user to press Enter or Return.
	std::cin.get();
	
	// Return the value 0 to indicate no problems.
	return 0;
	
} // End of the main() function.
