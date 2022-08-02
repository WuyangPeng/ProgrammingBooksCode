// This program demonstrates how to use a 
//stringstream object to create a nicely formatted string.

#include <iostream>	//for cout
#include <string>	//for strings
#include <sstream>	//for stringstream 

using namespace std;

int main()
{

	cout << "Welcome to the StringStream Demo program.\n\n";

	//create a few data variables that we'll format
	//into a single string

	//PI to 15 places
	double pi = 3.141592653589793;
	float dollar = 1.00;
	int dozen = 12;

	string text;

	//we want to have the string text contain this:
	//A dozen is 12, a dollar is $1.00 and
	//the value of pi to 10 places is 3.1415926536.

	//Create a stringstream object.
	stringstream ss;

	//Now using our usual cout "tools", we can use
	//these tools with ss. 

	ss << "A dozen is " << dozen << ", a dollar is $";
	ss.setf(ios::fixed);
	ss.precision(2);
	ss << dollar << " and \nthe value of pi to 10 places is ";
	ss.precision(10);
	ss << pi << ".";

	//now we assign the contents of ss into a string
	//use the str() function.

	text = ss.str();
	cout << "\nHere is our formatted text string:\n" << text << endl;

	//Add one more piece of data into the formatted string:
	ss << "\nThere are 2 \"+\"s in C++.";
	
	text = ss.str();
	cout << "\nHere is the final string: \n" << text << endl;

	return 0;
}


