//A program that reads the monthly bills
//from a data file. It calculates phone bill 
//average and total for the year. 

#include <iostream>
#include <string>
using namespace std;

#include "PhoneFunctions.h"

int main()
{
	string customer, company, year;

	float phone_bills[12];       

	cout << "A program that determines yearly total"
		<< "\nand average monthly phone bill."
		<< "\n\nData contained in \"PhoneBills.txt\""
		<< "\nResults written to \"PhoneBillSummary.txt\"\n";


	//Call function to read data into phone_bills
	//Function returns a false if it can't find file.
	bool result = ReadBillData(phone_bills, customer,
					company, year);
	if(result == false)
	{
		cout << "\nCan't continue working, no data!";

		//Use exit to terminate the program.
		exit(1);
	}

	//Calc values
	float ave, sum, max;
	ave = CalcBillTotalandAve(phone_bills, sum);

	//Find the max bill
	max = FindMax(phone_bills);
	
	result = WriteSummaryFile(customer, year, company,
								sum, ave, max);
	if(result == false)
	{
		cout << "\nProblem writing the file. Exiting program.";
		exit(1);
	}

	cout << "\nAll done! "
		<< "\nCheck \"PhoneBillSummary.txt\" for results!" << endl;
	return 0;
}

