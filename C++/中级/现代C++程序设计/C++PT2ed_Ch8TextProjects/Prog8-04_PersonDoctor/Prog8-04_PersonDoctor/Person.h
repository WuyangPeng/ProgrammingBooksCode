//File: Person.h

#ifndef _Person_H
#define _Person_H

#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
	string name;
	int age;
public:
	Person();
	Person(string n, int a);
	void SetData(string n, int a);
	void WritePerson();
	~Person();
};

#endif