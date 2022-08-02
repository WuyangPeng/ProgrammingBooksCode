//Demonstrate how to read C-string character data and
//numeric data in a program.

#include <iostream>
using namespace std;

int main()
{

	cout << "The How Old Are You Claire? Program "
		<< "\nasks our friend, Claire some personal questions.\n";

	char husband[25], footballTeam[25];
	int age, numKids;

	//ask Claire for husband's name, her age, 
	//favorite football team and number of kids

	cout << "Hi Claire, what is your husband's name? ";

	//use getline to read into the character array
	cin.getline(husband, 25);

	//Now ask age
	cout << "How old are you?   ";
	cin >> age;
	cin.ignore();  //strip off Enter key left by cin

	//Team name? Use another getline
	cout << "What is your favorite football team?   ";
	cin.getline(footballTeam,25);

	//Number of kids
	cout << "How many kids do you have?    ";
	cin >> numKids;
	cin.ignore();


	// write info out to screen
	cout << "\nHi Claire! Your husband is " << husband
		<< ".\nYour team is " << footballTeam << 
		". \nYou are " << age << " years old and have " 
		<< numKids << " kids." << endl;

	return 0;
}
