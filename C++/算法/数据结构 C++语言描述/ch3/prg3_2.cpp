// File: prg3_2.cpp
// the program prompts the user to enter a non-negative
// decimal number and a corresponding base in the range
// 2 <= base <= 10. it calls the recursive function
// displayInBase() that outputs the number in the
// desired base

#include <iostream>
#include <string>

using namespace std;

// output n with base 2 <= b <= 10
void displayInBase(int n, int b);

int main()
{
	int number, base;

	// prompt for number and base
	cout << "Input number and base:  ";
	cin >> number >> base;

	if (base >= 2 && base <= 10)
	{
		// output statement with function call 
		cout << "    " << number << " (base 10) = ";
		displayInBase(number,base);
		cout << " (base " << base << ")" << endl;
	}
	else
		cout << "The base must be in the range 2 <= base <= 10" << endl;
	
	return 0;
}

void displayInBase(int n, int base)
{
	// if n != 0, have another significant digit to display
	if (n > 0)
	{
		// output the digits in n/base
		displayInBase(n/base, base);

		// output the remainder
		cout << n % base;
	}
}

/*
Run 1:

Input number and base:  85 8
    85 (base 10) = 125 (base 8)

Run 2:

Input number and base:  25 2
    25 (base 10) = 11001 (base 2)

Run 3:

Input number and base:  9 4
    9 (base 10) = 21 (base 4)

Run 4:

Input number and base:  1555 3
    1555 (base 10) = 2010121 (base 3)
*/
