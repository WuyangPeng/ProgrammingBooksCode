//A program that uses the 
//PICalculator object 
//to calculate an estimated value of PI.

#include "PICalculator.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	//Steve is our PICalculator object.
	//He'll help us calculate values of PI.
	PICalculator Steve;

	string result;

	cout << "Revisit the PI Calculation Program";

	//First we'll tell Steve that we want to
	//calculate PI to 5000 terms.
	
	int terms = 5000;
	Steve.SetNumTerms(terms);
		
	//Ask Steve to give us the results!
	result = Steve.GetResultsString();
	
	cout << "\nWe told Steve to use 5000 terms: " << endl;
	cout << result;

	//Now we let Steve ask the user for the 
	//number of terms. 
	Steve.AskNumTerms();
	result = Steve.GetResultsString();

	cout << "The user told Steve how many terms: "<< endl;
	cout << result << endl;

	return 0;
}

