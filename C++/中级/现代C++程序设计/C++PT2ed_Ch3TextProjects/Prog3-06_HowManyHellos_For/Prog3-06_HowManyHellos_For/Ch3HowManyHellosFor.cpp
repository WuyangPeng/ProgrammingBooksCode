//A program to write hellos using a for loop
 
#include <iostream>
using namespace std;

int main()
{
	int counter, howMany; 

	cout << "How many hellos would you like to see?  ";
	cin >> howMany;

	//for loop executes howmany times
	for(counter = 0; counter < howMany; ++counter)   
	{
		cout << "\nHello!";
	}

	cout << "\nThat's a lot of hellos!   \n";

	return 0;
}
