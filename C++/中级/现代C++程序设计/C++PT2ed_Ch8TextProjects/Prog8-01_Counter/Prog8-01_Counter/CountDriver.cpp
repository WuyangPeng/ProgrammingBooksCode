//File: CountDriver.cpp
//Sample program with a counter object


#include "Counter.h"
#include <iostream>
using namespace std;

int main()
{
	//make a Counter object
	//its constructor sets HowMany count = 0

	Counter HowMany;    

	cout << "Sample program with class Counter  \n";
	
	HowMany.PrintCount();
	
	cout << "\nIncrement HowMany twice: ";
	++HowMany;
	++HowMany;
	
	HowMany.PrintCount();
	
	cout << "\nNow set the count back to zero. ";
	HowMany.SetCount(0);  

	HowMany.PrintCount();
	cout << "\n\nAll finished counting! \n";

	return 0;
}
