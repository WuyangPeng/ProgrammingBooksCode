//NameFunctions.cpp
//Contains the function definitions for the 
//prototypes contained in NameFunctions.h


#include <iostream>		//cout, cin, getline
#include <string>		//string object
#include <vector>		//vector objects
using namespace std;

bool SearchForName(vector<string> &names, vector<string> &origins, 
				   string &userName, string &nameOrigin )
{
	//Search our name vector until we either find it, or
	//run out of names. Stop looking when we find it.

	int index = 0;   
	while(index < names.size() )
	{
		if(userName == names.at(index))
		{
			//once we find it, set nameOrigin and return to main
			nameOrigin = origins.at(index);
			return true;  //found it.
		}
		else
		{
			++ index;
		}
	}

	//if we make it to this part of the function,
	//we didn't find the name
	return false;
}


void FillVectors(vector<string> &names, vector<string> &origins)
{
	//Load our names and origins into the vectors
	//These are main's vectors.
	//We have reference variables for them.
	names.push_back("Barbara");
	origins.push_back("greek, meaning stranger");

	names.push_back("Kelly");
	origins.push_back("celtic, meaning warrior or defender");

	names.push_back("Claire");
	origins.push_back("french, meaning bright and clear");

	names.push_back("Janis");
	origins.push_back("english, God is gracious");

	names.push_back("Ciara");
	origins.push_back("celtic, meaning black and mysterious");
		
	names.push_back("Lucy");
	origins.push_back("latin, meaning bringer of light");
}


string AskUserForName()
{
	string uName;
	cout << "\nPlease enter a woman's name, such as Kelly: ";
	getline(cin,uName);
	return uName;
}