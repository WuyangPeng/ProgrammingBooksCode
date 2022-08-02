//How old are you? in main function

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int age;
	string name;

	//Write a greeting
	cout << "Hello from a C++ program! \n";

	//Ask for the user's name
	cout << "What is your name?  ";
	getline(cin,name);

	//Ask for age
	cout << "How old are you?  ";
	cin >> age;

	//Write information
	cout << "Hi " << name << "! You are " 
		<< age << " years old.  \n";

	return 0;
}


