//This program uses an infinite series to 
//calculate an estimated value of PI.

//Here is PI to 20 places
//3.14159265358979323846 

#include <iostream>
#include <string>
#include <iomanip>	//for setprecision
using namespace std;

int main()
{
	int nTerms;

	//doubles can only store 15 places
	double PI = 3.141592653589793;


	double numerator, denom;
	double piCalc;
	string answer;

	cout << "PI Calculation Program\n";

	do
	{
		cout << "\nEnter number of terms for PI calculation:  ";
		cin >> nTerms;
		cin.ignore();	//strip out Enter key left over from cin

		//Since we are summing up PI, zero this variable!
		piCalc = 0.0;

		//Set the values for these variables that change.
		numerator = 4.0;	//start at +4.0
		denom = 1.0;		//start at 1.0
		for(int i = 0; i < nTerms; ++i)
		{
			piCalc = piCalc + numerator/denom;
	
			denom += 2.0;
			numerator = -1.0 * numerator;   //flip sign
		}

		cout << "Results\nNumber of Terms: " << nTerms
			<< setprecision(10) <<  " PI = " << PI 
			<< " Calc PI = " << piCalc << endl;

		cout << "Do more PI calculations? yes/no ";
		getline(cin,answer);

	}while(answer == "yes");

	return 0;
}