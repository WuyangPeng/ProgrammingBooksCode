#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg11_4.cpp
// the program inputs the file "studwk.dat" that contains student names and
// time worked in a part-time job during the week. the time is given in
// time24 format. using the index operator, the information is stored and
// updated in a map<string, time24> object called studentWorker. the program
// concludes by displaying the contents of the map, showing in alphabetical
// order the name and total time worked during the week

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>

#include "d_time24.h"	// time24 class
#include "d_util.h"		// for writeMap()

using namespace std;

int main()
{
	// a map<string, time24> object whose entries are student names
	// and total hours worked during a week
	map<string, time24> studentWorker;
	// map iterator
	map<string, time24>::iterator iter;

	// object used to input the data from file "studwk.dat"
	ifstream fin;
	string studName;
	time24 workTime;

	// open the file "studwk.dat"
	fin.open("studwk.dat");

	// input successive lines in the file consisting of the
	// student name and the scheduled work time
	while (true)
	{
		fin >> studName;
		if (!fin)
			break;
		fin >> workTime;

		// add a new student with workTime as time worked or update the
		// accumulated work time if the student is already in the map
		studentWorker[studName] += workTime;

	}

	// output the map, one key-value pair per line
	writeMap(studentWorker,"\n");

	return 0;
}

/*
File: "studwk.dat"

Tolan	4:15
Dong	3:00
Tolan	3:15
Weber	5:30
Tolan	2:45
Brock	4:20
Dong	4:00
Dong	3:30
Tolan	3:15
Weber	2:30

Run:

Brock   4:20
Dong  10:30
Tolan  13:30
Weber   8:00
*/
