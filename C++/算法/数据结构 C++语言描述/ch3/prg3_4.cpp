// File: prg3_4.cpp
// the program prompts the user to input a rational
// number in the form p/q and displays it as a mixed number.

#include <iostream>

using namespace std;

// compute the greatest common divisor of the nonnegative
// integers a and b where both a and b cannot be 0
int gcd(int a, int b);

int main()
{
	int numerator, denominator, wholePart, remainder, divisor;
	char slash;

	cout << "Enter a rational number (numerator/denominator): ";
	cin >> numerator >> slash >> denominator;

	// compute the quotient (whole part) and the remainder
	wholePart = numerator / denominator;
	remainder = numerator % denominator;

	if (remainder == 0)
		// the rational number is an integer
		cout << wholePart << endl;
	else
	{
		// number in mixed form is "wholePart remainder/divisor"
		// output wholePart if it is not 0
		if (wholePart != 0)
			cout << wholePart << ' ';

		// compute the greatest common divisor of the remainder
		// and the divisor
		divisor = gcd(remainder, denominator);
		// output the fractional part in lowest terms by dividing
		// the remainder and divisor by their gcd
		cout << remainder/divisor << '/' << denominator/divisor
			  << endl;
	}

	return 0;
}

int gcd(int a, int b)
{
	if (b == 0)
		return a;				// a divides a and 0
	else
		return gcd(b, a%b);	// recursive step
}

/*
Run 1:

Enter a rational number (numerator/denominator): 6/8
3/4

Run 2:

Enter a rational number (numerator/denominator): 535/1
535

Run 3:

Enter a rational number (numerator/denominator): 535/2
267 1/2

Run 4:

Enter a rational number (numerator/denominator): 324/88
3 15/22
*/
