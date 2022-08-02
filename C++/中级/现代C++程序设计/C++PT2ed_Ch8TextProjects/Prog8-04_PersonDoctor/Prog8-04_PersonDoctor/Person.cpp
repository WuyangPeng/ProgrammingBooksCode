//File: Person.cpp

#include "Person.h"

Person::Person()
{ 
	cout << "\nIn the default Person constructor"; 
	name = "";
	age = 0;
}

Person::Person(string n, int a)
{ 
	cout << "\nIn the overloaded Person constructor"; 
	name = n;
	age = a;
}

void Person::SetData(string n, int a)
{ 
	name = n;
	age = a;
}

Person::~Person()
{
	cout << "\nDestructing Person " << name << endl; 
}

void Person::WritePerson()
{	
	cout << "\n" << name << " is " << age << 
		" years old. "; 
}
