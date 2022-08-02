//Demonstrate how to use C-strings to read both
// character data and numeric data into a program.

//The input data in the C-string buffer can be 
//converted to the desired numeric data.

#include <iostream>
using namespace std;

int main()
{

	cout << "The How Old Are You Claire? Program Part 2"
		<< "\nOnce again, ask our friend, "
		<< " Claire some personal questions.\n\n";

	char husband[25], footballTeam[25];
	//make a temporary buffer to read in numeric data
	char buffer[25];  
	int age, numKids;

	double PI;

	//ask Claire for husband's name, her age, 
	//favorite football team and number of kids

	cout << "Hi Claire, what is your husband's name? ";
	cin.getline(husband, 25);

	//Now ask age
	cout << "How old are you? ";
	cin.getline(buffer,25);

	//convert using ASCII to Integer function
	age = atoi(buffer);
	
	//Team name? Use another getline
	cout << "What is your favorite football team? ";
	cin.getline(footballTeam,25);

	//Number of kids
	cout << "How many kids do you have? ";
	cin.getline(buffer,25);
	numKids = atoi(buffer);

	//Lets see if Claire knows PI's value.
	cout << "What is the value of PI? ";
	cin.getline(buffer,25);

	//convert to double with atof
	PI = atof(buffer);

	// write info out to screen
	cout << "\nHi Claire! Your husband is " << husband
		<< ".\nYour team is " << footballTeam << 
		". \nYou are " << age << " years old and have " 
		<< numKids << " kids.  \nPI is " << PI << endl;

	return 0;
}
