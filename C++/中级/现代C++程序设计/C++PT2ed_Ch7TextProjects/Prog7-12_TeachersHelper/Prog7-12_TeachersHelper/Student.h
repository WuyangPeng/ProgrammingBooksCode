//File: Student.h

#ifndef _STUDENT_H
#define _STUDENT_H

#include <string>
using namespace std;

class Student
{
private:
	string name, ID;
	int testScore[4];
	float ave;

public:
	Student();

	void SetNameID(string n, string i);
	void SetTestScores(int sc[]);
	
	float GetAverage(){ return ave; }
	string GetName(){ return name; }
	string GetID(){ return ID; }
};

#endif

