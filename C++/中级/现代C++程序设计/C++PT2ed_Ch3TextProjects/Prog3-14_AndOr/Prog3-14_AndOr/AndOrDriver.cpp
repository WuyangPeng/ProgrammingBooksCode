//This program demonstrates the AND Operator
//and OR operator for checking values inside and outside
//of numeric ranges.

//NOTE: if a "real" program, you could use just the AND
//or just the OR, no need to use both!

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int number;
	string answer;

	cout << "This program asks the user to enter a whole number."
		<< "\nIt then determines if the number is between -25 to + 25"
		<< "\nusing both AND and OR operators.\n";

	do
	{
		cout << "\nPlease enter a whole number.  ";
		cin >> number;
		cin.ignore();

		//One way to check, use OR operator, the number
		//could be below low range OR above high range.

		if(number < -25 || number > 25)
		{
			cout << "The number " << number << " is outside +/-25.";
		}
		else
		{
			cout << "The number " << number << " is inside +/-25.";
		}


		//A different way to check, use AND operator, the number
		//could be above low value AND below high value.

		if(number >= -25 && number <= 25)	
		{
			cout << "\nThe number " << number << " is inside +/-25.";
		}
		else
		{
			cout << "\nThe number " << number << " is outside +/-25.";
		}

		cout << "\nSee another number?  yes/no ";
		getline(cin,answer);

	}while(answer == "yes");

	return 0;
}