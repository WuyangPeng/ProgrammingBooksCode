//A program with functions to help us
//uses an infinite series to 
//calculate an estimated value of PI.

//Here is PI to 20 places
//3.14159265358979323846 

#include <iostream>
#include <string>
#include <iomanip>		//for setprecision
#include <sstream>		//for a stringstream object
using namespace std;

//function prototypes
int AskNumTerms();
double CalculatePI(int nTerms);
string PrepResultsString(double PI, double calcPI, int nTerms);

int main()
{
	int nTerms;

	//doubles can only store 15 places
	double PI = 3.141592653589793;

	double calcPI;

	string result, answer;

	cout << "PI Calculation Program\n";

	do
	{
		nTerms = AskNumTerms();
		calcPI = CalculatePI(nTerms);
		result = PrepResultsString(PI,calcPI,nTerms);

		cout << result;

		cout << "Do more PI calculations? yes/no ";
		getline(cin,answer);

	}while(answer == "yes");

	return 0;
}

//Ask the user for number of terms.
int AskNumTerms()
{
	int n;

	cout << "\nEnter number of terms for PI calculation:  ";
	cin >> n;
	cin.ignore();

	return n;
}

//Calculate value of PI using infinite series equation.
double CalculatePI(int nTerms)
{
	//Declare and initialize here
	double calcPI = 0.0;
	double numerator = 4.0, denom = 1.0;
	
	for(int i = 0; i < nTerms; ++i)
	{
		calcPI = calcPI + numerator/denom;
		denom += 2.0;
		numerator = -1.0 * numerator;   //flip sign
	}

	return calcPI;
}

string PrepResultsString(double PI, double calcPI, int nTerms)
{
	stringstream piString;

	piString.setf(ios::fixed);

	piString << "Results\nNumber of Terms: " << nTerms
		<< setprecision(10) <<  " PI = " << PI 
		<< " Calc PI  = " << calcPI << endl;

	return piString.str();
}



	

