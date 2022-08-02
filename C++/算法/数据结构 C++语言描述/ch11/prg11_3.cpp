#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg11_3.cpp
// the program reads a file "curracct.dat" containing the login names of
// university students who want a computer account for the current academic
// year. it also reads the file "oldacct.dat" containing the login names of
// students from the previous year. using set operations, the program
// computes the set of new accounts, accounts carried over from the previous
// year, and accounts for students who have not requested a current
// account. using writeContainer(), the program outputs the login names
// in the sets

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>

#include "d_setops.h"
#include "d_util.h"

using namespace std;

int main()
{
	// declare sets for current and new computer accounts along with iterator
	set<string> oldAcct, currAcct, newAcct, carryOverAcct, obsoleteAcct;

	// objects used by the program
	string acct;
	ifstream finOldAcct, finCurrAcct;

	// open file of old accounts and current accounts
	finOldAcct.open("oldacct.dat");
	finCurrAcct.open("curracct.dat");

	// input the set of old accounts
	while(true)
	{
		finOldAcct >> acct;
		if (!finOldAcct)
			break;
		oldAcct.insert(acct);
	}

	// input the set of current accounts
	while(true)
	{
		finCurrAcct >> acct;
		if (!finCurrAcct)
			break;
		currAcct.insert(acct);
	}

	// use set intersection to determine the set of
	// carryover accounts
	carryOverAcct = currAcct * oldAcct;

	// use set differnce to determine the set of new accounts
	// and obsolete accounts
	newAcct = currAcct - oldAcct;
	obsoleteAcct = oldAcct - currAcct;

	// output the set of old accounts
	cout << "Old Accounts:" << endl;
	writeContainer(oldAcct.begin(), oldAcct.end(), "   ");
	cout << endl << endl;

	// output the set of current accounts
	cout << "Current Accounts:" << endl;
	writeContainer(currAcct.begin(), currAcct.end(), "   ");
	cout << endl << endl;

	// output the set of new accounts
	cout << "New Accounts:" << endl;
	writeContainer(newAcct.begin(), newAcct.end(), "   ");
	cout << endl << endl;

	// output the set of carryover accounts
	cout << "Carryover Accounts:" << endl;
	writeContainer(carryOverAcct.begin(), carryOverAcct.end(), "   ");
	cout << endl << endl;

	// output the set of obsolete accounts
	cout << "Obsolete Accounts:" << endl;
	writeContainer(obsoleteAcct.begin(),obsoleteAcct.end(), "   ");
	cout << endl;

	return 0;
}

/*
File "curracct.dat"

fbrue
ascott
wtubbs

File "oldacct.dat"

tmiller
lhung
fbrue
gharris

Run:

Old Accounts:
fbrue   gharris   lhung   tmiller

Current Accounts:
ascott   fbrue   wtubbs

New Accounts:
ascott   wtubbs

Carryover Accounts:
fbrue

Obsolete Accounts:
gharris   lhung   tmiller
*/
