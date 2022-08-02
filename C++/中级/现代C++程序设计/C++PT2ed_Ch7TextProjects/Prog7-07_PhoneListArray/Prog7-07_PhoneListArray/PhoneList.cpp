//File: PhoneList.cpp

#include "PhoneList.h"
#include <string>
#include <iostream>
#include <iomanip>	

using namespace std;

PhoneList::PhoneList()   
{
	// constructor sets strings to ""
	// and zero's integers
	name = "";
	address = "";
	phNumber = "";
	cout << "In the PhoneList constructor.\n";
}

void PhoneList::ShowListing()
{
	cout << endl << setw(20) << name << setw(25) 
		<< address << setw(15) << phNumber;

}
