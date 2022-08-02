//Demonstrate how rand() and srand() operate.

#include <iostream>		//for cout, cin
#include <cstdlib>		//for srand(), and rand()
#include <iomanip>		//for setw()
#include <string>		//for string
#include <ctime>		//for time()

using namespace std;

int main()
{
	cout << "Random Number Generator Demo ";

	int seed, number, i;
	string answer;
	
	cout << "\n\nFirst, here are 8 random numbers."
			<< "\nWe used the time function for seed value.\n";

	//seed with time, and see what we get
	srand( (unsigned)time( NULL ) );
	for(i = 0; i < 8; ++i)
	{
		number = rand();
		cout << setw(8) << number;
	}

	cout << "\nNow we'll let you choose the seed value. \n";
	do
	{
		
		cout << "\nPlease enter a seed value for rand()  ";
		cin >> seed;

		//cin >> leaves the enter key in keyboard queue
		//we need to strip it off so getline doesn't read it
		cin.ignore();	

		srand(seed);
		cout << "Eight numbers with seed  " << seed << endl;

		for(i = 0; i < 8; ++i)
		{
			number = rand();
			cout << setw(8) << number;
		}

		cout << "\nDo another set of numbers?  yes/no ";

		getline(cin,answer);

	}while(answer == "yes");

	return 0;
}