//Nested if statements sample program

#include <iostream>
using namespace std;

int main()
{	
	
	int number;  

	cout << "This program will tell you if your number is "
			<< "\npositive and between 1 and 10. ";

	cout << "\nPlease enter a whole number:   ";
	cin >> number;

	if(number > 0)  //positive number
	{
		cout << "The number is positive. " << endl;
			
		if(number >= 1 && number <= 10)
		{
			cout << "It is between 1 and 10." << endl;
		}
				
	}
	else
	{
		cout << "The number not positive." << endl;
	}
	return 0;
}
