//File:  PICalculator.cpp

#include "PICalculator.h"
#include <string>
#include <iostream>
#include <iomanip>		//for setprecision
#include <sstream>		//for a stringstream object
using namespace std;

//constructor initializes class members
PICalculator::PICalculator()
{
	nTerms = 0;
	
	//Initialize real value of PI to 16 places
	realPI = 3.1415926535897932; 
}

//use number of terms to determine est PI
void PICalculator::Calculate()
{
	calcPI = 0.0;
	double numerator = 4.0, denom = 1.0;
	
	for(int i = 0; i < nTerms; ++i)
	{
		calcPI = calcPI + numerator/denom;
		denom += 2.0;
		numerator = -1.0 * numerator;   //flip sign
	}
}

		
//Ask the user for number of terms.
void PICalculator::AskNumTerms()
{
	cout << "Enter number of terms for PI calculation:  ";
	cin >> nTerms;
	cin.ignore();     //strip off Enter key

	//now calculate PI
	Calculate();
}


//Set the number of terms and then calculate.
void PICalculator::SetNumTerms(int tms)
{
	nTerms = tms;

	//Once you set the number of terms, 
	//calculate the value for PI.
	Calculate();
}

//Return a formatted string with results.
string PICalculator::GetResultsString()
{
	stringstream piString;

	piString.setf(ios::fixed);
	piString << "\nResults\nNumber of Terms: " << nTerms
		<< setprecision(10) <<  " PI = " << realPI 
		<< " Calc PI = " << calcPI << endl;

	return piString.str();
}

