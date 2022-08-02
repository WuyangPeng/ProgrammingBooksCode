//A program that shows how to use the 
//address operator to obtain variable memory addresses.

#include <iostream>
using namespace std;

int main()
{
	float x = static_cast<float>(1.0);
	float y = static_cast<float>(2.0);
	int i = 3, j = 4;
	double q = 5.0, r = 6.0;
	
	cout.setf(ios::fixed);
	cout.precision(7);
	
	cout << "\program that shows variable values and addresses.";
	cout << "\nValue of x = " << x << " Address = " << &x;
	cout << "\nValue of y = " << y << " Address = " << &y;
	cout << "\nValue of i = " << i << " Address = " << &i;
	cout << "\nValue of j = " << j << " Address = " << &j;
	
	cout.precision(10);
	cout << "\nValue of q = " << q << " Address = " << &q;
	cout << "\nValue of r = " << r << " Address = " << &r <<endl;

	return 0;

}
