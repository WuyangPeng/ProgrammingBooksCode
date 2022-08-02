// File:  Doctor.cpp

#include "Doctor.h"
#include <iostream>
using namespace std;

Doctor::Doctor() 
{
	cout << "\nIn the default Doctor constructor ";
	speciality = "";
}

Doctor::Doctor(string n, int a, string spec): Person(n, a) 
{
	cout << "\nIn the overloaded Doctor constructor ";
	speciality = spec;
}

void Doctor::SetData(string n, int a, string spec)
{
	Person::SetData(n,a);
	speciality = spec;
}

void Doctor::WriteDoctor()
{
	Person::WritePerson();
	cout << "\nSpeciality:  " << speciality;
}

Doctor::~Doctor() 
{
	cout << "\nDestructing Doctor with a speciality of "
		<< speciality;
}

