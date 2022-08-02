//A program that asks the user to enter the
//letter of his favorite fruit. We use a switch 
//statement to determine the value of the letter.

#include <iostream>		//for cout, cin

using namespace std;

int main()
{

	string fruit;

	cout << "I'm going to try and guess your favorite"
			<< " fruit. \nPlease enter the first letter"
			<< " of your favorite fruit:  ";
	
	char firstLetter;
	cin >> firstLetter;

	switch (firstLetter)
	{
	case 'a':   case 'A':
		cout << "Is it apple? " << endl;
		break;
	case 'b':   case 'B':
		cout << "Is it banana? "<< endl;
		break;
	case 'c':   case 'C':
		cout << "Is it cantalope? "<< endl;
		break;
	default:
		cout << "I can't guess your favorite fruit.  ;-)" << endl;
	}

	return 0;
}


