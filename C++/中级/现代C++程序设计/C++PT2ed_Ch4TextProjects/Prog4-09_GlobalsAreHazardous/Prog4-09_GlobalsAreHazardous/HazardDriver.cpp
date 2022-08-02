//This program does not compile.
//There is a conflict using a global variable
//and cmath library.

#include <iostream>		//for cout
#include <cmath>		//for sqrt
using namespace std;

//declare two global variables
double y0, y1;

int main()
{
	//assign value into y0
	y0 = 5000.0;

	//take the square root
	y1 = sqrt(y0);

	//write result
	cout << "\n Square root of " << y0 << " is " << y1;

	return 0;
}