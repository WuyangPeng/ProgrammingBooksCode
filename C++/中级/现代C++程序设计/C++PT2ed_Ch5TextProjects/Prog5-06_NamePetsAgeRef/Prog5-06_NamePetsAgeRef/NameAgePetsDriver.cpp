//A program with a function that uses 
//reference variables to return 
//three data items to main.

//include statements
#include <iostream>
#include <string>
using namespace std;

//function declarations
void AskForInfo(string &rName, int &rAge, int &rNumPets);
void WriteInfo(string name, int age, int numPets);

int main()
{
	string name;
	int age, numPets;

	//Use the variable names in the call to Ask.
	//The addresses are passed since it is a 
	//call by reference.
	AskForInfo(name, age, numPets);

	//The Write function is a call by value.
	//Copies of the values are passed to it.
	WriteInfo(name, age, numPets);

	return 0;
}


void AskForInfo(string &rName, int &rAge, int &rNumPets)
{
	cout << "Please enter your name:  ";
	getline(cin, rName);
	cout << "Please enter your age:  ";
	cin >> rAge;
	cout << "Please enter the number of pets that you own:  ";
	cin >> rNumPets;
	cin.ignore();
}

void WriteInfo(string name, int age, int numPets)
{
	cout << "Hi " << name << "!\nI see that you are "
		<< age << " years old and have " << numPets << " pets." << endl;
}


