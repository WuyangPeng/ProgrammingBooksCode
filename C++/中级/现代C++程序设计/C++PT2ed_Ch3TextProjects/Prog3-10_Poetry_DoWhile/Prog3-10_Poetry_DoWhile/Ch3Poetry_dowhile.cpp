//do while loop and Poetry

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string answer; /*no need to initialize since we'll ask the user
                             before we check the condition */  

	cout << "Here is my lovely poem. ";

	do
	{	
		cout << "\nRoses are red, violets are blue" <<
		"\nI Love C++, how about you?";

		cout << "\nWould you like to see my poem again?  yes/no  ";
		getline(cin,answer);

	} while(answer == "yes");   //keep going until not yes

	cout << "\nDid you enjoy my poem?" << endl;
	
	return 0;
}
