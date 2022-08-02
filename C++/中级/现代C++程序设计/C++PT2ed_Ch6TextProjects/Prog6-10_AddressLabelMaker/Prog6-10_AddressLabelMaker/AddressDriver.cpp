//This program creates an label maker 
//using C-strings and several functions from  
//C's <string.h> These functions are now available
//in C++'s standard namespace

#include <iostream>
using namespace std;

int main()
{
	char first[20], middle[20], last[20];
	char Name[50], Address[50], City[30];
	char State[5],Zip[15];

	//first ask for information, read using getline
	cout << "Enter first name: ";
	cin.getline(first,20);
	cout << "Enter middle name: ";
	cin.getline(middle,20);
	cout << "Enter last name: ";
	cin.getline(last,20);

	cout << "Enter street address: ";
	cin.getline(Address,50);
	cout << "Enter city: ";
	cin.getline(City,30);
	cout << "Enter 2 letter state abbrev: ";
	cin.getline(State,20);
	cout << "Enter zip code: ";
	cin.getline(Zip,15);

	//build Name   Last, First Middle Initial
	//first copy the last name into Name
	strcpy(Name,last);

	//next concatenate a comma
	//use ", " since that is considered a char[]
	strcat(Name,", ");

	//add first name
	strcat(Name,first);

	//add space
	strcat(Name," ");

	//pull first initial, use strncpy
	strncat(Name,middle,1);

	//add period
	strcat(Name,".");

	cout << "\nHere is the mailing label.\n" 
		<< Name << endl << Address << endl
		<< City << ", " << State << " " << Zip << endl;

	return 0;
}



