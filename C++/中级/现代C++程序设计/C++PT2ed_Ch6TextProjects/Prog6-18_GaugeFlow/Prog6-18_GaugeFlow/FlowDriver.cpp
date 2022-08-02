//File:  FlowDriver.cpp
//This program reads the flow data for a 
//river gauge for the Colorado River.
//We find the high and low flows.
//We obtain indexex for high and low and 
//use them to reference data arrays. 

#include <iostream>
#include <string>
using namespace std;

#include "FlowFunctions.h"

int main()
{
	cout << "This program finds the highest and"
		<< " lowest flow values \nfor"
		<< " Inflow Gauge 09082500 in the "
		<< "\nColorado River near Glenwood Springs, Colorado"
		<< "\nfrom 1/1971 to 12/2003 " << endl;

	int flowData[400];	//33 years * 12 = ~400 months
	string Dates[400];

	int highIndex, lowIndex;

	int total = ReadFlowFile(Dates, flowData );
	if(total == -99)
	{
		cout << "\nTrouble reading input file.";
		cout << "\nExiting program. " << endl;
		exit(1);
	}

	FindHighLow(flowData, total, highIndex, lowIndex);
	
	cout << "\nThe highest flow was " << flowData[highIndex] 
		<< " acre feet per month in " << Dates[highIndex] << endl;

	cout << "The lowest flow was " << flowData[lowIndex] 
		<< " acre feet per month in " << Dates[lowIndex] << endl;

	return 0;
}


