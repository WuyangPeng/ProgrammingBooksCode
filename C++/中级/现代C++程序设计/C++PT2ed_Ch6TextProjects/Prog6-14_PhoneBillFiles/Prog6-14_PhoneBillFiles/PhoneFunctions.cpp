//File: PhoneFunctions.cpp

#include <iostream>		//needed for cout
#include <string>		//needed for string
#include <fstream>		//for ifstream and ofstream
using namespace std;


//For convenience, we'll use #define for file names
#define FILE_IN "PhoneBills.txt"
#define FILE_OUT "PhoneBillSummary.txt"

//Function that reads monthly bill data.
bool ReadBillData(float bills[], string &rCust, 
				  string &rCompany, string &rYear)
{

	ifstream billInput;		//input object 

	billInput.open(FILE_IN);

	//check that we've got the file open
	if(!billInput)
	{
		cout << "\n Whoops! Can't find " << FILE_IN;
		return false;
	}

	//Read monthly bill info using ifstream object
	//getline and cin works just like it did
	//for keyboard input--except use ifstream object

	//First line is the Company
	getline(billInput,rCompany);

	//Second line is the Customer
	getline(billInput,rCust);

	//Third line is the timeframe
	getline(billInput,rYear);


	//Used this way, billInput works just like cin >> 
	for(int i = 0; i < 12; ++i) 
	{
		billInput >> bills[i];
	}

	//all done reading, close the file
	billInput.close();

	return true;
}

//Function that determines bill average,
//given the yearly sum.
float CalcBillTotalandAve(float bills[], float &rSum)
{
	rSum = 0.0;
	for(int i = 0; i < 12; ++i)  
	{
		rSum = rSum + bills[i];
	}

	return rSum/12.0;
}

float FindMax(float bills[])
{
	//First set max to first element, then compare 
	//to all values. If we find a higher value, 
	//set it to max;

	float max = bills[0];

	for(int i = 1; i < 12; ++i)
	{
		if(max < bills[i])
			max = bills[i];

	}
	return max;
}

bool WriteSummaryFile(string cust, string year, string co,
					  float sum, float ave,float max)
{
	ofstream billOutput;		//output object 

	billOutput.open(FILE_OUT);

	//check that we've got the file open
	if(!billOutput)
	{
		cout << "\n Whoops! Can't open " << FILE_OUT;
		return false;
	}

	//Now it is just like cout << to write to the file!
	billOutput << "\n " << cust << "\n " << year;
	billOutput << "\n Phone Bill Summary for " << co;

	//Set precision for the file stream object.
	billOutput.precision(2);
	billOutput.setf(ios::fixed);
	billOutput << "\n Total yearly phone cost is $" << sum
		<< "\n Average monthly phone bill is $"
		<< ave << "\n Max Month is $" << max << endl;

	//close the file
	billOutput.close();

	return true;
}

