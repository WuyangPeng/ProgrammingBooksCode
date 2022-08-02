//This program show how to initialize 
//C-strings and C++ string objects.
//It also shows the importance of the NULL char.

#include <iostream>
#include <string>
using namespace std;

int main()
{
	//First use a C++ string
	string strObject = "This text is in a string object!";

	//Declare C-string and initialize.
	char cppLove[20] = "I love C++!";

	//Declare and fill individual elements.
	//(whoops!) no null placed here
	char noNullText[20];
	
	noNullText[0] = 'W';
	noNullText[1] = 'h';
	noNullText[2] = 'o';
	noNullText[3] = 'o';
	noNullText[4] = 'p';
	noNullText[5] = 's';
	noNullText[6] = ' ';
	noNullText[7] = 'n';
	noNullText[8] = 'o';
	noNullText[9] = ' ';	
	noNullText[10] = 'n';
	noNullText[11] = 'u';
	noNullText[12] = 'l';	
	noNullText[13] = 'l';

	//Declare, but don't put anything in it
	char noText[20]; 

	//Now write all four:
	cout << "Write out the four pieces of text data." << endl;
	cout << "String object: " << strObject << endl;
	cout << "     C++ love: " << cppLove << endl;
	cout << "   noNullText: " << noNullText << endl;
	cout << "      No text: " << noText << endl;

	return 0;
}
