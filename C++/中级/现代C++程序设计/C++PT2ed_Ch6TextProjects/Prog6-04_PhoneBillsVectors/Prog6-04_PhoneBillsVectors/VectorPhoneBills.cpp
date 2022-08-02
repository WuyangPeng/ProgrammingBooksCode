//The Phone Bill Program using vectors to 
//hold bill and month names. 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	// Declare vector of floats for phone bills
	vector <float> vPhoneBills;       

	//Declare vector of strings for the months:
	vector <string> vMonth;
	
	//Must fill vector one at a time
	vMonth.push_back("Jan");
	vMonth.push_back("Feb");
	vMonth.push_back("Mar");
	vMonth.push_back("Apr");
	vMonth.push_back("May");
	vMonth.push_back("June");
	vMonth.push_back("July");
	vMonth.push_back("Aug");
	vMonth.push_back("Sept");
	vMonth.push_back("Oct");
	vMonth.push_back("Nov");
	vMonth.push_back("Dec");

	float yearSum, ave;
	int i;		     //i is our loop index 

	cout << "\n A program that determines yearly total"
		<< "\n and average monthly phone bill.\n\n";

	// Obtain monthly billing information 
	float bill;
	for(i = 0; i < vMonth.size(); ++i) 
	{
		cout << " Enter bill for month " << vMonth.at(i) << " $";
		cin >> bill;
		vPhoneBills.push_back(bill);
	}

	// Now calculate the average value.
	yearSum = 0.0;
	for(i = 0; i < vMonth.size(); ++i)  
	{
		yearSum = yearSum + vPhoneBills.at(i);
	}

	ave = yearSum/12;
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "\n Total yearly phone cost is $" << yearSum
		<< "\n Average monthly phone bill is $"
		 << ave << endl;



	return 0;
}
