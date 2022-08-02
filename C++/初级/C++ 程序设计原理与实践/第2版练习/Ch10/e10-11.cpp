// Bjarne Stroustrup 7/26/2009
// Chapter 10 Exercise 11

/*
	produce a sum of all whitespace-separated integers in a text fine. For example
		bears: 17 elephants 9 end
		should output 26

	Note that 12.7 contains no whitespace-separated integeres, nor does 12f. Had we considered
	those 12s numbers to be added the exercise would have been simpler.

*/

#include "std_lib_facilities.h"	

/*
	We can find whitespac-separated words: istreams do that by default, but how do we know that a word
	represents a number? Chapter 11 will show the general way to do extract numeric values from strings:
	use a stringstream. Here we have to use a more tedious strategy:
		"Try to read an int and if that fails read a word"
*/


bool whitespace(char ch)
	// accept "space, tab, or newline" as our definition of "whitespace"
	// see 11.6: isspace() for the standard definition
{
		return (ch==' ' || ch=='\t' || ch=='\n');
}

bool digit(char ch)
	// see 11.6: isdigit() for the standard definition
{
	switch (ch) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return true;
	default:
		return false;
	}
}

int main()
try
{
	cout << "please enter an input file names: ";
	string name;
	cin>>name;
	ifstream is(name.c_str());
	if (!is) error("bad input file name ", name);
	
	string s;
	int n;
	int sum = 0;
	int count = 0;	// I just want to know how many integers I found
	char ch;

	while(is>>ch) {	// skips whitespace
		if (digit(ch)) {	// we found an integer, but what about 12.7 and 12F?
			is.putback(ch);	// put the digit back so that we can read the whole integer
			if (is>>n) {
				if (is.get(ch) && whitespace(ch)) {	// is the character following the integer a whitespace?
					++count;
					sum+=n;
				}
				else {
					is.putback(ch);	// in case the next character is a whitespace (example: foo 12F bar)
					is>>s;			// read the rest of the string
				}
			}
			else {
				error("impossible");	// error message "just in case"
			}
		}
		else {
			is.putback(ch);
			is>>s;			// read the string as a string
		}
	};

	cout << "integer count: " << count << " sum: " << sum << '\n';

	keep_window_open("~");	// For some Windows(tm) setups
}
catch (runtime_error e) {	// this code is to produce error messages; it will be described in Chapter 5
	cout << e.what() << '\n';
	keep_window_open("~");	// For some Windows(tm) setups
}
catch (...) {	// this code is to produce error messages; it will be described in Chapter 5
	cout << "exiting\n";
	keep_window_open("~");	// For some Windows(tm) setups
}

/*

	This is messy code (but then the problem was messy). How do we know that code is correct?
	Those nested if look like the kind of code that might harbor bugs.

	Among other things I tested with this file:

	12 hello12 34foo 10f beard
	100.10 bad
	nnn
	sdd 112 23 14
	77a 145 -10000 d
	1212

	I tried with and without a newline after that final 1212. That makes a difference: end of file
	is not considered whitespace by this program. Text input files that do not end with a newline
	are often a problem (a design and/or implementation problem).

	Note that (according to the problem statement) -10000 is not a whitespace-separated integer.
*/

