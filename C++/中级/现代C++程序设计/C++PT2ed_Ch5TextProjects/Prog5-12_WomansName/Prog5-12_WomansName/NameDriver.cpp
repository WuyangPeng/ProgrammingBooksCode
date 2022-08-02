//Program asks the user to enter a woman's name.
//Search our vector to see if the name is in it.
//If it is, write out the origin/meaning of the name.

#include <iostream>		//cout, cin, getline
#include <string>		//string object
#include <vector>		//vector objects
using namespace std;

#include "NameFunctions.h"

int main()
{
	cout << "Welcome to the C++ Name Search Program";

	//Create 2 string vectors, names and origins.
	vector<string> names;
	vector<string> origins;

	//Now use a function to fill the vectors with data
	FillVectors(names, origins);

	//Variables for name and results
	string  userName, nameOrigin, answer;
	bool bFoundIt;   

	do
	{
		userName = AskUserForName();

		//the bFoundIt flag indicates if the name was found
		bFoundIt = SearchForName(names,origins,userName,nameOrigin);
		if(bFoundIt)
		{
			cout << "Here is your name: " << userName;
			cout << "\nOrigin: " << nameOrigin;
		}
		else
		{
			cout << "Sorry. " << userName << " isn't in our vector. ";
		}

		cout << "\nDo another name?  yes/no ";
		getline(cin,answer);

	}while (answer == "yes");

	return 0;
}


