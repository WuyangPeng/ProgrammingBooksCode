//File: Grader.h

#ifndef _GRADER_H
#define _GRADER_H

#include "Student.h"
#include <string>
using namespace std;

class Grader
{
private:
	Student kids[10];
	int total;
	string courseName, courseID, college; 
	float courseAve, courseHigh, courseLow;
	int highKid, lowKid;
	void ReadStudentFile();

public:
	Grader();
	void ComputeCourseStats();
	void WriteResultsFile();
};

#endif
