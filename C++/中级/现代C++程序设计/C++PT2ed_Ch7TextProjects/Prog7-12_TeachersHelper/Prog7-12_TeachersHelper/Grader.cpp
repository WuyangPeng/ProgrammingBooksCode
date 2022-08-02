//File: Grader.cpp

#include "Grader.h"

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#define  FILE  "StudentGrades.txt"

Grader::Grader()
{
	total = 0;
	ReadStudentFile();
}

void Grader::ComputeCourseStats()
{
	//loop through array of kids
	//obtaining the students' average
	//to compute course average
	//remember high and low ave too

	float sum = 0;
	courseHigh = kids[0].GetAverage();
	courseLow = courseHigh;
	lowKid = highKid = 0;

	float score;

	for(int i = 0; i < total; ++ i)
	{
		score = kids[i].GetAverage();
		sum = sum + score;

		if(score < courseLow)
		{
			lowKid = i;
			courseLow = score;
		}

		if(score > courseHigh)
		{
			highKid = i;
			courseHigh = score;
		}
	}

	courseAve = sum/total;
}
	
void Grader::WriteResultsFile()
{
	ofstream output;

	string file;
	cout << "\n Please enter the output file ";
	getline(cin,file);

	//convert the string to a c-string
	output.open(file.c_str() );

	if(!output)
	{
		cout << "\n Trouble opening output file."
			<< "\n Can't write the file. " << endl;
	}

	//set output's precision
	output.setf(ios::fixed);
	output.precision(2);

	output << "\n Grade Results for " << college 
			<< "'s \n " << courseName 
			<< "\n ID " << courseID << endl;

	string stName, stID;
	float stAve;
	
	output << setw(20) << "Name" << setw(8) 
			<< "ID" << setw(10) << "Ave" << endl;

	for(int i = 0; i < total; ++i)
	{
		stName = kids[i].GetName();
		stID = kids[i].GetID();
		stAve = kids[i].GetAverage();

		output << setw(20) << stName << setw(8) 
			<< stID << setw(10) << stAve << endl;
	}

	output << "\n Course Ave " << courseAve 
			<< "\n High Ave was " << courseHigh 
			<< " by " << kids[highKid].GetName()
			<< "\n Low Ave was " << courseLow
			<< " by " << kids[lowKid].GetName();

	output.close();
	cout << "\n All Done! \n Check " << file 
		<< " for " << courseName << " grade results!"
		<< endl;
}
	
void Grader::ReadStudentFile()
{
	ifstream input;
	input.open(FILE);
	if(!input)
	{
		cout << "\n Can't find the "
			<< " StudentGrades.txt file."
			<< " \n Exiting program!" ;

		//hold for an Enter key, so the user sees it
		cin.get();
		exit(1);
	}

	//Ok, open and ready to go
	//read first line, college
	getline(input,college);
	
	//next two lines are the course and course ID
	getline(input,courseName);
	getline(input,courseID);

	//rest of file are students, 3 lines per 
	//we'll read until the end of file
	//counting students as we go

	string name, id;
	int g[4];
	int count = 0;
	char comma;

	//each pass, read each student's data
	while(!input.eof() )
	{
		getline(input,name);
		getline(input,id);

/*  WHOOPS!  This code was originally written in VC++ 6.0, which 
	handles this input sequence as described in the text, page 439. 
		input >> g[0] >> comma >> g[1] >> comma
			>> g[2] >> comma >> g[3];
		input.ignore();

	Visual C++ 2005 doesn't parse this. It needs to be read in the
	manner shown below.

	Sorry about this.  :-)=)

	Barbara Johnston, September 28, 2007    */

		//read each value using a delimiter and fill a char array,
		//then use atoi to convert to an int. 
		
		//read the first 3 to the comma, then last to the end of the line.
		char buf[10];
		input.getline(buf,10,',');
		g[0] = atoi(buf);
		input.getline(buf,10,',');
		g[1] = atoi(buf);
		input.getline(buf,10,',');
		g[2] = atoi(buf);
		input.getline(buf,10);
		g[3] = atoi(buf);


		kids[count].SetNameID(name,id);
		kids[count].SetTestScores(g);
		++count;
	}

	//set the total number of students in file
	total = count;

	cout << "\n We have read " << total  
		<< " student grades from " << FILE << endl;
	//close the file
	input.close();
}
