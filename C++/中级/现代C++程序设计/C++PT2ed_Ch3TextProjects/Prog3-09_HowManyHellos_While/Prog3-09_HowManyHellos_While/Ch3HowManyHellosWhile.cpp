//Writing hellos with a while loop 

#include <iostream>
using namespace std;

int main()
{
	int counter, howMany; 
	
	cout << "How many hellos would you like to see?    ";
	cin >> howMany;

	counter = 0;
	
	while(counter < howMany)   //loop executes howMany times
		{
			cout << "\nHello!";
			++counter;
		}
	
	cout << "\nThat's a lot of hellos!   \n";
	
	return 0;
}
