// File:  Doctor.h

#ifndef _DOCTOR_H
#define _DOCTOR_H

#include "Person.h"

#include <iostream>
using namespace std;

class Doctor:public Person
{
private:
	string speciality;

public:
	Doctor();
	Doctor(string n, int a, string spec);
	void SetData(string n, int a, string spec);

	void WriteDoctor();

	~Doctor();
};

#endif