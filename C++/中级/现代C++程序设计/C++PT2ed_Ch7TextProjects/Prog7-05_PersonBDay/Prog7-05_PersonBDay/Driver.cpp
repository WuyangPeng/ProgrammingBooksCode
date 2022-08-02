//File: Driver.cpp

#include "Person.h"
#include <iostream>
using namespace std;

int main()
{
	string goAgain;
	Person user;

	cout<<"This is the "
		<< "\"Have You Had Your Birthday?\" Program!";

	//For convenience, let's write out today's date.
	Date d;
	cout << "\n" << d.GetFormattedDate()<< endl << endl;

	do
	{
		user.AskForBDayInfo();
		user.WriteBDayInfo();

		cout<<"Would you like to go again?   yes/no ";
		getline(cin, goAgain);

	}while(goAgain == "yes");

	cout<<"GoodBye";

	return 0;
}