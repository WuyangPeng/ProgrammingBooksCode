//Famous Year Program with switch

#include <iostream>
using namespace std;

int main()
{
	int year;  
	cout << "Please enter your favorite year   ";
	cin >> year;

	cout << "Your year: " << year << " is famous because ";
	switch(year)  //check for a famous year
	{
		case 1920:
			cout << "Women were allowed to vote!\n";
			break;
		case 1776:
			cout << "the Declaration of Independence was drafted!\n";
			break;
		case 1969:
			cout << "Neil Armstrong walked on the moon!\n";
			break;
		default:
		cout << "\n...oh, not sure what happened in your year.\n"; 
	}

	return 0;
}
