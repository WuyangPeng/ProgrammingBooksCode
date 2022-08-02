//File: PICalculator.h

//Given a number of terms, this PICalculator
//class uses an infinite series to determine
//an estimate for PI.

#include <string>
using namespace std;

#ifndef _PICALC_H
#define _PICALC_H

class PICalculator
{
	private:
			int nTerms;
			double calcPI, realPI;

			//This performs the PI calculation. 
			void Calculate();
	public:
			PICalculator();

			//Ask user for number of terms.
			void AskNumTerms();

			//Set function passes data into object
			void SetNumTerms(int tms);

			//Get functions return values.
			double GetActualPI(){ return realPI;}
			double GetCalcdPI(){ return calcPI;}
			string GetResultsString();
};

#endif
