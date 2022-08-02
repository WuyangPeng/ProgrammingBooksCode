#ifdef __BORLANDC__
// suppress the warning message about comparing signed and unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg11_5.cpp
// prompt user for name of a text file containing identifiers,
// where an identifier begins with a letter ('A'..'Z', 'a'..'z')
// followed by 0 or more letters or digits ('0'..'9'). function
// concordance() takes a file name as an argument and uses a map
// with key string and value set<int> to determine each identifier,
// the number of lines on which it occurs, and the line numbers on
// which it appears. concordance() calls writeConcordance() to
// display the results in the format
//           identifier			n:  line# line# line#  . . .

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <set>
#include <map>
#include <ctype.h>	// for functions isalpha() and isdigit()

#include "d_util.h"

using namespace std;

// input filename and output a concordance
void concordance(const string& filename);

// output the identifier, the number of lines containing the
// identifier, and the list of lines having the identifier
void writeConcordance(const map<string,set<int> >& concordance);

int main()
{
	string filename;

	// get the file name
	cout << "Enter the file name: ";
	cin >> filename;
	cout << endl;

	// create the concordance
	concordance(filename);

	return 0;
}

void concordance(const string& filename)
{
	// declare the concordance map
	map<string, set<int> > concordanceMap;

	// objects to create identifiers and maintain line numbers
	char ch;
	string identifier = "";
	bool beginIdentifier = true;
	int lineNumber = 1;

	// file objects
	ifstream fin;

	// open the input file
	fin.open(filename.c_str());

	if (!fin)
	{
		cerr << "Cannot open '" << filename << "'" << endl;
		exit(1);
	}

	// read the file character by character to determine each
	// identifier and update line numbers
	while(true)
	{
		fin.get(ch);
		if (!fin)
			break;

		// check for a letter that begins an identifier
		if (isalpha(ch) && beginIdentifier)
		{
			// add char to identifier and continue scan
			identifier += ch;
			beginIdentifier = false;
		}

		// check if subsequent letter or digit in an identifier
		else if ((isalpha(ch) || isdigit(ch)) && !beginIdentifier)
			identifier += ch;

		// not part of an identifier
		else
		{
			// if we have just finished with an identifier,
			// use the index operator to access a map entry with
			// identifier as the key. if not in the map, the operator
			// adds an entry with an empty set as the value component.
			// if in the map, the operator accesses the set component.
			// in either case, insert the current line number
			if (!beginIdentifier && identifier != "")
				concordanceMap[identifier].insert(lineNumber);

			// increment lineNumber if ch == '\n'
			if (ch == '\n')
				lineNumber++;

			// reset objects preparing for next identifier
			beginIdentifier = true;
			identifier = "";
		}
	}

	// output the concordance
	writeConcordance(concordanceMap);
}

void writeConcordance(const map<string,set<int> >& concordance)
{	map<string, set<int> >::const_iterator iter =
									concordance.begin();
	int i;

	while (iter != concordance.end())
	{	cout << (*iter).first;	// output key
		// pad output to 12 characters using blanks
		if ((*iter).first.length() < 12)
			for (i=0;i < 12 - (*iter).first.length();i++)
				cout << ' ';
		cout << setw(4) << (*iter).second.size() << ":    ";
		writeContainer((*iter).second.begin(),(*iter).second.end());
		cout << endl;
		iter++;
	}
	cout << endl;
}

/*
File: "concord.txt"

int m, n;
double a = 3, b = 2, hypotenuse

cin << m;
if (n <= 5)
	n = 2*m;
else
	n = m * m;

cout << n << endl;

hypotenuse = sqrt(a*a + b*b);
cout << hypotenuse << endl;

Run:

Enter the file name: concord.txt

a              2:    2  12
b              2:    2  12
cin            1:    4
cout           2:    10  13
double         1:    2
else           1:    7
endl           2:    10  13
hypotenuse     3:    2  12  13
if             1:    5
int            1:    1
m              4:    1  4  6  8
n              5:    1  5  6  8  10
sqrt           1:    12
*/
