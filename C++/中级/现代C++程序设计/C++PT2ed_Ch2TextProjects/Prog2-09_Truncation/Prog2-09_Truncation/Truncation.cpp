//Variable Values Illustration Program
//Declare and assign values into variables.  

#include <iostream>     //for cout
using namespace std;

int main ()             
{ 
	
	int money = 435.83;		//will only store 435

	short int nNFLfans = 56332;   //attendance at NFL game

	float pi=3.1415926535;	   // float only hold 7 places
	double PI = 3.1415926535;	// double is good to 15 places

	double x = 15;		//double has 15 digits of precision
	
	cout << "Values";
	cout << "\nmoney (int) " << money;
	cout << "\nNFL fans (short int) " << nNFLfans;

	//Tell cout to write 14 places of precision
	cout.setf(ios::showpoint | ios::fixed);
	cout.precision(14);

	cout << "\npi as a float " << pi;
	cout << "\nPI as a double " << PI;
	cout << "\nx (double) " << x << "\n";;

	return 0;
}
