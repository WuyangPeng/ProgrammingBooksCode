//Calculate volume of a dumbbell.

#include <iostream>		//needed for cout and cin
#include <iomanip>		//needed for setw()
#include <cmath>		//for power function

using namespace std;

int main()
{
	float pi = static_cast<float>(3.14159265);
	float rs, rbar, lbar;
	float sphVol, barVol, totalVol;

	//obtain dumbbell dimensions
	cout << "Please enter radius of the end-spheres: ";
	cin	>>rs;
		
	cout << "Please enter radius and length of the bar: ";
	cin	>>rbar >> lbar;

	//calculate sphere vol
	sphVol = 4.0/3.0*pi*pow(rs,3);

	//calculate the bar volume
	barVol = pi*pow(rbar,2)*lbar;

	//total volume is bar volume + 2(sphere volumes)
	totalVol = barVol + 2.0*sphVol;

	//write results
	cout.setf(ios::fixed | ios::showpoint); //write w/ 4 digits of prec
	cout.precision(3);

	cout <<"Dumbbell Volume Results \n";
	cout << setw(15) << "Sphere Radius" << setw(15) <<"Bar Radius" <<
		setw(15) << "Bar Length" << setw(15) << "Total Volume" << endl;

	cout << setw(15) << rs << setw(15) << rbar <<
		setw(15) << lbar << setw(15) << totalVol<< endl;

	return 0;
}
