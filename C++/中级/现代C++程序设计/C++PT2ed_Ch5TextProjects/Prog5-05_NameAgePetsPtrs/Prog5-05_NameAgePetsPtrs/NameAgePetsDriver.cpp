//A program with a function that uses 
//pointers with indirection operators to 
//return three pieces of information to main.

//include statements
#include <iostream>
#include <string>
using namespace std;

//function declarations
void AskForInfo(string *pName, int *pAge, int *pNumPets);
void WriteInfo(string name, int age, int numPets);

int main()
{
	string name;
	int age, numPets;

	//Use the address operator to pass the variable
	//addresses to the function.
	AskForInfo(&name, &age, &numPets);

	//No need to use pointers here. We can pass
	//the values to the Write function.
	WriteInfo(name, age, numPets);

	return 0;
}


void AskForInfo(string *pName, int *pAge, int *pNumPets)
{
	cout << "Please enter your name:  ";
	getline(cin, *pName);
	cout << "Please enter your age:  ";
	cin >> *pAge;
	cout << "Please enter the number of pets that you own:  ";
	cin >> *pNumPets;
	cin.ignore();
}

void WriteInfo(string name, int age, int numPets)
{
	cout << "\nHi " << name << "!\nI see that you are "
		<< age << " years old and have " << numPets << " pets." << endl;
}


