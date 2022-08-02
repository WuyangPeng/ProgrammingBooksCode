//Writing the ABC's using a for loop

#include <iostream>		//for cout
#include <iomanip>		//for setw
using namespace std;

int main()
{
	int letter_ctr, i;
	cout << "We're going to write our ABC's   \n";

	letter_ctr = 0;
	for(i = 65; i < 91; ++i)		//A = 65, Z = 90
	{
		//we cast the integer into a character
		cout << setw(6) << static_cast<char>(i);

		letter_ctr++;				// incr letter counter
		if(letter_ctr == 7) 		// newline if we've written 7
		{
			cout << endl;
			letter_ctr = 0;
		}
	}

	cout << "\nThere are our ABCs." << endl;

	return 0;
}
