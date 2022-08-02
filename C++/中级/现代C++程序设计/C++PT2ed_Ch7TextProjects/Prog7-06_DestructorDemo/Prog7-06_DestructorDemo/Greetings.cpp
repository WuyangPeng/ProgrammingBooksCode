//File: Greetings.cpp

#include "Greetings.h"
#include <string>
#include <iostream>
using namespace std;

Greetings::Greetings()
{
	name = "Bob";
	cout << "Hello " << name << " from the default constructor!";
}

Greetings::Greetings(string n)
{
	name = n;
	cout << "\nHello " << name  
		<< "! How are you today? " << endl;
}

Greetings::Greetings(string g, string n)	
{
	name = n;
	cout << "\n" << g << "! " << name << endl << endl;
}

Greetings::~Greetings()	
{
	cout << "Goodbye " << name << " from the"
		" Greetings destructor! \n";
}
