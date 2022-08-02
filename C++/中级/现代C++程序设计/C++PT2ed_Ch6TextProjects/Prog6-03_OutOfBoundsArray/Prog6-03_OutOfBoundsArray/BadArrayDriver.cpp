//This program is bad.
//We go out of bounds on our arrays.

#include <iostream>
using namespace std;

int main()
{

	//Make 3 arrays, all sized to 4
	int High[4], Mid[4], Low[4];
	int i;

	//now fill using rand()
	//make high between 90 - 100
	//make low between 45-55
	//make rain between 0 - 10
	
	//YIKES, look at for loop index range  :-(
	for(i = 0; i <= 4; ++ i)
	{
		Low[i] = rand()%11;	
		Mid[i] = rand()%11 + 45;
		High[i] = rand()%11 + 90;
	}

	cout << "Write the low values.";
	for(i = 0; i < 4; ++ i)
		cout << "\nLow[" << i << "] = " << Low[i];

	cout << "\nWrite the middle values.";
	for(i = 0; i < 4; ++ i)
		cout << "\nMid[" << i << "] = " << Mid[i];

	cout << "\nWrite the highs values.";
	for(i = 0; i < 4; ++ i)
		cout << "\nHigh[" << i << "] = " << High[i];

	return 0;
}

