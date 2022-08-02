//File: Greetings.h

#ifndef GREETING_H
#define GREETING_H

#include <string>
using namespace std;

class Greetings
{
private:
	string name;

public:

	//default constructor, writes greeting to Bob
	Greetings();			

	//overloaded cosntructors
	//writes standard greeting to name
	Greetings(string n);			

	//writes greeting to name
	Greetings(string g, string n);	

	//destructor
	~Greetings();		
};

#endif