//Program asks the user to enter a woman's name.
//Search our vector to see if the name is in it.
//If it is, write out the origin/meaning of the name.

#include <iostream>		//cout, cin, getline
#include <string>		//string object
#include <vector>		//vector objects

using namespace std;

int main()
{

	cout << "Welcome to the C++ Name Search Program\n\n";

	//Create 2 string vectors, names and origins.
	vector<string> names;
	vector<string> origins;

	//First load up our vectors.
	names.push_back("Barbara");
	origins.push_back("greek, meaning stranger");

	names.push_back("Kelly");
	origins.push_back("celtic, meaning warrior or defender");

	names.push_back("Claire");
	origins.push_back("french, meaning bright and clear");

	names.push_back("Janis");
	origins.push_back("english, God is gracious");

	names.push_back("Ciara");
	origins.push_back("celtic, meaning black and mysterious");
		
	names.push_back("Lucy");
	origins.push_back("latin, meaning bringer of light");

	//Variables for the guessing logic
	string answer, userName;

	do
	{
		bool bDidNotFindIt = true;   

		cout << "Please enter a woman's name, such as Kelly: ";
		getline(cin,userName);

		//Search our name vector until we either find it, or
		//run out of names. Stop looking when we find it.

		int index = 0;   
		while(index < names.size()  && bDidNotFindIt == true)
		{
			if(userName == names.at(index))
			{
				cout << "Here is your name: " << names.at(index);
				cout << "\nOrigin: " << origins.at(index);

				bDidNotFindIt = false;    //we did find it!
			}
			else
			{
				++ index;
			}
		}

		//check the bDidNotFindIt variable
		//if it is still true, we didn't find the user's name
		if(bDidNotFindIt)
		{
			cout << "Sorry. " << userName << " isn't in our vector. ";
		}

		cout << "\n\nDo another name?  yes/no ";
		getline(cin,answer);

	}while (answer == "yes");

	return 0;
}