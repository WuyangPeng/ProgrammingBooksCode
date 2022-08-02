// File:  Driver.cpp

#include "Doctor.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Constructors, Destructors "
		<< " and Inheritance\n";

	cout << "\nKaren is our baby doctor."
		<<	"\nMake an object using default "
		<< "constructor, \nthen set the data.";

	Doctor BabyDoc;
	BabyDoc.SetData("Karen", 45, "Deliveries");

	cout << "\n\nSean is our orthopedic surgeon."
		<<	"\nMake an object using the overloaded"
		<< " constructor" ;
	Doctor BoneGuy("Sean", 38, "Orthopedics");

	cout << "\nAll finished. End of program.\n";
	return 0;
}
