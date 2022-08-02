//File: DeluxeDriver.cpp

#include "DeluxeCounter.h"

#include <iostream>
#include <string>
using namespace std;

int main()
{
	
	cout << "The Deluxe Counter Program.\n";
	//create two of these high-class counters

	DeluxeCounter superDooper;

	superDooper.SetCount(75);
	superDooper.SetName("Donna");
	superDooper.SetWhat("chickens");

	DeluxeCounter topNotch("Don","Tractors",15);
	
	//see what we've got
	superDooper.PrintCount();
	topNotch.PrintCount();

	cout << "\n\nTime to fix dinner. ";
	--superDooper;

	cout << "\nTime to go to the farm auction.\n ";
	++topNotch;
	++topNotch;	

	superDooper.PrintCount();
	topNotch.PrintCount();

	cout << "\nDon't run over your chickens with"
			<< " your new tractors! :-) \n";

	return 0;
}