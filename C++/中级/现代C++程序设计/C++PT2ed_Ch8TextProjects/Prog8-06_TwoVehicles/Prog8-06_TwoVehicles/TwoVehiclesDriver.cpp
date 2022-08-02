//File: TwoVehiclesDriver.cpp

#include <iostream>
#include "Vehicles.h"

using namespace std;

int main()
{
	cout << "The Two Vehicles Program " << endl;

	Vehicle *base[2];	//2 pointers to the base class
	RV HaveFun;
	Semi GoToWork;

	base[0] = &HaveFun;	//assign into base class ptrs
	base[1] = &GoToWork;

	//obtain the info using the virtual functions
	for(int i = 0; i < 2; ++i)
	{
		base[i]->AskInfo();
	}

	//now write the information
	for(int i = 0; i < 2; ++i)
	{
		base[i]->WriteInfo();
	}

	cout << "\nWork? No. Let's go camping!  \n\n";
	return 0;
}