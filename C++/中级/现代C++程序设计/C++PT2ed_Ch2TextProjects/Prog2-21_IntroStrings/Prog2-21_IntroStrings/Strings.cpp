//C++ string objects


#include <iostream>		//for cout, cin, getline
#include <string>		//for string

using namespace std;

int main()
{
	//declare 3 string objects, initialize one of them
	string name;
	string school;
	string favLang = "C++, of course";

	cout << "C++ Programming Student Demographics ";
	
	//ask the user to enter her name and school
	//use getline function to read from input into string
	cout << "\nPlease enter your name: ";
	getline(cin,name);

	cout << "Please enter your school: ";
	getline(cin,school);

	cout << "Programming Student Data:"
			<< "\nName: " << name
			<< "\nSchool: " << school
			<< "\nFavorite language: " << favLang << endl;

	return 0;
}


