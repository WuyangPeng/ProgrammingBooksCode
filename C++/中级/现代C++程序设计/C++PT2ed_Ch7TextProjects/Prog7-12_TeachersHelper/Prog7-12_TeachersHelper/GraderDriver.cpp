//File: GraderDriver.cpp
//This program uses the Grader class to
//help us determine grades for C++ students.

//Note to reader: error in the code has been fixed here! 
//Sorry!  See ReadStudentFile in Grader class. 
//Barbara Johnston

#include "Grader.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "\n The Teacher's Helper Program! \n";

	Grader kelly;

	kelly.ComputeCourseStats();

	kelly.WriteResultsFile();

	return 0;
}