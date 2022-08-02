//File: Student.cpp

#include "Student.h"

Student::Student()
{
	name = ID = "";
	ave = static_cast<float>(0.0);

	for(int i = 0; i < 4; ++i)
		testScore[i] = 0;
}

void Student::SetNameID(string n, string i)
{
	name = n;
	ID = i;
}

void Student::SetTestScores(int sc[])
{
	int i;
	
	//copy the test scores into the array
	for(i = 0; i < 4; ++i)
		testScore[i] = sc[i];
	
	float sum = 0;
	
	//sum and determine average
	for(i = 0; i < 4; ++i)
		sum += testScore[i];

	ave = sum/4.0;
}

