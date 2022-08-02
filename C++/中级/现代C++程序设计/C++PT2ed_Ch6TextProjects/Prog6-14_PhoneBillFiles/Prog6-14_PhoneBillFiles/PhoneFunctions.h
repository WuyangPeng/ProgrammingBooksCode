//File: PhoneFunctions.h

#include <string>	//needed here for string
using namespace std;


//Function prototypes
bool ReadBillData(float bills[], string &rCust, 
				  string &rCompany, string &rYear);

float CalcBillTotalandAve(float bills[], float &rSum);

float FindMax(float bills[]);

bool WriteSummaryFile(string cust, string year, string co,
					  float sum, float ave, float max);
