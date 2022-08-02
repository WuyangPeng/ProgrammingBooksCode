//File: FlowFunctions.h

#define FILE "StreamGaugeInflow.csv"

#include <string>
using namespace std;

//Read flow data from FILE file. 
//Returns the total lines read from file. 
//If error, returns -99
int ReadFlowFile(string Dates[], int flowData[]);

//Search data for the high and low flows.
//Return the indexes.
void FindHighLow(int flowData[], int total, 
				 int &rHigh, int &rLow);

