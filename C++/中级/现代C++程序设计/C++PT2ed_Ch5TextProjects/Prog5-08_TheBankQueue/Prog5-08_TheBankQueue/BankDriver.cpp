//This program models standing in line
//at the C++ bank. It uses a C++ queue object
//to hold the customers' names.

#include <iostream>
#include <queue>		//for queue object
#include <string>

using namespace std;

//function declarations
int ShowMenu();
void ShowLineInfo(queue<string> &rLine);
void AddToTheLine(queue<string> &rLine);
void ServeFirst(queue<string> &rLine);

int main()
{
	cout << "Welcome to the C++ Bank \n";
	queue<string> bankLine;

	int choice = 0;
	while(choice != 4)
	{
		choice = ShowMenu();
		switch(choice)
		{
		case 1:				//show line info
			ShowLineInfo(bankLine);
			break;
		case 2:				//add person to line
			AddToTheLine(bankLine);
			break;

		case 3:				//serve first person 
			ServeFirst(bankLine);
			break;
		}
	}

	cout << "Thanks for using the C++ Bank! " << endl;

	return 0;
}

void ShowLineInfo(queue<string> &rLine)
{
	int num = rLine.size();
	if(num == 0)
		cout << "There is no one standing in line. " << endl;
	else
	{
		cout << "Total customers in line: " << num << endl;
		cout << rLine.front() << " is at the front of the line.\n";
	}
}

void AddToTheLine(queue<string> &rLine)
{
	string name;
	cout << "Who do we add at the end of the line? ";
	getline(cin, name);
	
	//Use push() function to push the person onto
	//the end of the queue. 
	rLine.push(name);
}


void ServeFirst(queue<string> &rLine)
{
	//check if line is empty or not
	if(rLine.empty() == true)
		cout << "No one in line, let's have a coffee break.\n";
	else
	{
		cout << "NEXT!  Now serving " << rLine.front() << endl;
		
		//Now pop this person off of the queue.
		rLine.pop();
	}
}

int ShowMenu()
{
	int choice;
	cout << "1. Show Line Info.    2. Add Person"
		<< "  3. Serve person  4. Exit ==>  ";
	cin >> choice;
	cin.ignore();		//strip off Enter key! 
	return choice;
}
