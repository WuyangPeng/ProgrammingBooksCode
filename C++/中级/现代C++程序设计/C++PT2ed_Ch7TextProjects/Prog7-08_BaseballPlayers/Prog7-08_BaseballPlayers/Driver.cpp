//File:  Driver.cpp

#include <iostream>
#include <string>
#include "BaseballPlayer.h"
using namespace std;

void CheckWhoIsGreater(BaseballPlayer &p1,
					   BaseballPlayer &p2);
int main()
{
	cout << "The Baseball Players Program! ";

	//Aaron is our first player object
	//He has 25 homers and 28 RBIs
	BaseballPlayer  bb1("Aaron", 25, 28);

	//Jorge is our second player object
	//He has 24 homers and 26 RBIs
	BaseballPlayer  bb2("Jorge", 24, 26);

	cout << " Here are our two players: \n";
	bb1.WritePlayerStats();
	bb2.WritePlayerStats();
	
	CheckWhoIsGreater(bb1, bb2);

	//Jorge is going to hit a home run!
	!bb2;

	CheckWhoIsGreater(bb1, bb2);

	//Jorge is hits another one!
	!bb2;

	CheckWhoIsGreater(bb1, bb2);

	return 0;
}

void CheckWhoIsGreater(BaseballPlayer &p1,
					   BaseballPlayer &p2)
{
	cout << "\nChecking:  Who is \"greater\"?";
	if(p1 > p2)
	{
		cout << "\n" << p1.GetName() << 
			" is greater!\n";
		p1.WritePlayerStats();
	}
	else
	{
		cout << "\n" << p2.GetName() << 
			" is greater!\n";
		p2.WritePlayerStats();
	}
}


