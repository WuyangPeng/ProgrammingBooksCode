// File: prg7_1.cpp
// the user enters a non-negative decimal number and a base in the
// range 2 <= base <= 16. a call to the function multibaseOutput()
// displays the number in the specified base. the program terminates
// when the user enters a number of 0 and a base 0

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// output integer num in base b
string multibaseOutput(int num, int b);

int main()
{
	int num, b;	// decimal number and base

	// prompt for a non-negative number and the desired base 2 <= B <= 16
	cout << "Enter a non-negative decimal number and base "
		  << "(2 <= B <= 16)" << endl << "or 0 0 to terminate: ";
	cin >> num >> b;

	// continue until the user enters a base of 0
	while (b != 0)
	{
		cout << "    " << num << " base " << b << " is "
			  << multibaseOutput(num, b) << endl;

		cout << "Enter a non-negative decimal number and base "
			  << "(2 <= B <= 16)" << endl << "or 0 0 to terminate: ";
		cin >> num >> b;
	}

	return 0;
}

string multibaseOutput(int num, int b)
{
	// digitChar[digit] is the character that represents
	// the digit, 0 <= digit <= 15
	string digitChar = "0123456789ABCDEF", numStr = "";

	// stack holds the base-b digits of num
	stack<char> stk;

	// extract base b digits right to left and push on stack s
	do
	{
		// push right-most digit on the stack
		stk.push(digitChar[num % b]);
		num /= b;				// remove right-most digit from num
	} while (num != 0);		// continue until all digits found

	while (!stk.empty())		// flush the stack
	{
		numStr += stk.top();	// add digit on top of stack to numStr
		stk.pop();				// pop the stack
	}

	return numStr;
}

/*
Run:

Enter a non-negative decimal number and base (2 <= B <= 16)
or 0 0 to terminate: 27 2
    27 base 2 is 11011
Enter a non-negative decimal number and base (2 <= B <= 16)
or 0 0 to terminate: 300 16
    300 base 16 is 12C
Enter a non-negative decimal number and base (2 <= B <= 16)
or 0 0 to terminate: 75 8
    75 base 8 is 113
Enter a non-negative decimal number and base (2 <= B <= 16)
or 0 0 to terminate: 0 0
*/
