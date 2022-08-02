//assign from left to right, not right to left

#include <iostream>
#include <math.h>
using namespace std;


int main()
{
	double x, sqrootX;
	x = 5.2;       //assign number from right to left

	sqrootX = sqrt(x);  //calculate on right, assign to left

	cout << "Square root of " << x << " is " << sqrootX << "\n\n";

	return 0;
}


/* Here is the incorrect code
int main()
{
	double x, sqrootX;
	5.2 = x;       // can't assign from right to left

	sqrt(x) = sqrootX; // can't call sqrt on left of = sign

	cout << "\n Square root of " << x << " is " << sqrootX << "\n\n";

	return 0;
}

  */