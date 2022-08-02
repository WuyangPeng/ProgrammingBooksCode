//A demonstration of how you can obtain the
//desired range of random numbers using % and arithmetic.

#include <iostream>		//for cout and cin
#include <cstdlib>		//for srand() and rand()
#include <iomanip>		//for setw()
#include <ctime>		//for time()
using namespace std;

int main()
{

	cout << "This program generates three sets of random"
			<< " numbers \nusing the % operator and arithmetic\n";

	//Use the time to seed rand()
	srand( (unsigned)time(NULL) );

	int number;
	
	cout << "\nIf we rand()%N, we get values between 0 and N-1 "
			<< "\nHere we pick N of 7, we get values between 0 - 6.\n";

	for(int i = 0; i < 10; ++i)
	{
		number = rand()%7;		//gives us values from 0 - 6
		cout << setw(5) << number;
	}


	cout << "\n\nFor values between 0.000 and 1.000, we generate "
			<< "\nintegers between 0 - 1000, and divide by 1000. \n";
		
	double random;
	cout.precision(3);
	cout.setf(ios::fixed);
	for(int i = 0; i < 10; ++i)
	{
		number = rand()%1001;		//gives us values from 0 to 1000
		random = number/1000.0;		//divide by 1000.0 not 1000
		cout << setw(7) << random;
	}	


	cout << "\n\nFor a value between -25 and 25, obtain 0 - 50"
			<< "\nand subtract 25. \n";
	for(int i = 0; i < 10; ++i)
	{
		number = rand()%51;		//gives us 0 to 50
		number = number - 25;
		cout << setw(5) << number;
	}
		
	cout <<"\n\nPretty cool, isn't it? " << endl;

	return 0;
}

