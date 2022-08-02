//File: FlowFunctions.cpp

#include <iostream>
#include <string>
#include <fstream>		//for ifstream, ofstream
using namespace std;

#include "FlowFunctions.h"

//Search data for the high and low flows.
//Return the indexes for later use.
void FindHighLow(int flowData[], int total, 
				 int &rHigh, int &rLow)
{
	//set high and low indexes to first value
	rHigh = rLow = 0;

	//local vars to keep track high/low values
	int highFlow, lowFlow;

	//set to first value
	highFlow = lowFlow = flowData[0];

	//now traverse array looking for high/low
	for(int i = 1; i < total; ++i)
	{
		if(flowData[i] < lowFlow)
		{
			lowFlow = flowData[i];
			rLow = i;
		}

		if(flowData[i] > highFlow)
		{
			highFlow = flowData[i];
			rHigh = i;
		}
	}
}

int ReadFlowFile(string Dates[], int flowData[])
{
	ifstream inFlow;
	inFlow.open(FILE);

	//check that we've got the file open
	if(! inFlow)
	{
		cout << "\nERROR Can't find " << FILE;
		return -99;
	}

	cout << "\nReading " << FILE << endl;

	//use i to count entries in file
	int i = 0;

	//Here is a sample line:
	//1/71,71642
	//The comma separates date and flow
	while(!inFlow.eof() )
	{
		//read date using ',' for delimiter(stop) 
		getline(inFlow, Dates[i], ',');

		//getline has removed the comma,
		//now just read the flow number
		//use cin-like form to read numbers
		inFlow >> flowData[i]; 

		//get rid of \n at end of line
		inFlow.ignore();

		//increment the count
		++i;
	}

	cout << "Read " << i << " flow values. " << endl;
	
	//all done reading, close the file
	inFlow.close();

	//return total number of values
	return i;
}

