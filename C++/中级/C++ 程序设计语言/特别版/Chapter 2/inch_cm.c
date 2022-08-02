// Simple inch<->cm conversion program illustrating basic I/O and computation.

// pg 50, sec 3.6, Input

// No guarantees offered. Constructive comments to bs@research.att.com



#include<iostream>

using namespace std;


int main()
{
	const float factor = 2.54;	// 1 inch equals 2.54 cm
	float x, in, cm;
	char ch = 0;

	cout << "enter length: ";

	cin >> x;		// read a floating-point number
	cin >> ch;		// read a suffix

	switch (ch) {
	case 'i':		// inch
		in = x;
		cm = x*factor;
		break;
	case 'c':		// cm
		in = x/factor;
		cm = x;
		break;
	default:
		in = cm = 0;
		break;
	}

	cout << in << " in = " << cm << " cm\n";

	return 0;	// redundant in ISO C++
}
