//Program illustrating the use of #defines

#include <iostream>
using namespace std;

#define PI 3.14159265
#define  RADIUS 5.257

int main()
{
	double circleArea;

	//The area of a circle is PI * Radius * Radius

	circleArea = PI * RADIUS * RADIUS;
	
	cout << "\nCircle Summary ";
	cout << "\nThe circle's radius is " << RADIUS;
	cout << "\nThe value of PI is " << PI;
	cout << "\nThe circle's area is " << circleArea << "\n";
	
	return 0;
}