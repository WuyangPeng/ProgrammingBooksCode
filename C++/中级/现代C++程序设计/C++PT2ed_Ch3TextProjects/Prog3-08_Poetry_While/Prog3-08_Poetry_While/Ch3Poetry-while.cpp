//while loop and Poetry program

#include <iostream>		//for cout, getline
#include <string>		//for string object
using namespace std;

int main()
{

	string answer = "yes";   //initialize answer to yes  

	cout << "Here is my lovely poem.";

	while(answer == "yes")   //keep going until not yes
	{
		cout << "\nRoses are red, violets are blue" <<
		"\nI Love C++, how about you?";

		cout << "\nWould you like to see my poem again?  yes/no  ";
		getline(cin, answer);
	}

	cout << "\nDid you enjoy my poem?" << endl;
	return 0;
}
