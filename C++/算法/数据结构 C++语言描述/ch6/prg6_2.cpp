// File: prg6_2.cpp
// the program uses the class, wordFreq, that stores a word
// and the number of times it has occurred in a document. declare
// a list, wf, of wordFreq objects. prompt the user for the name
// of a file containing words and read the file word by word. if
// a word is in the list, increase its frequency by 1; otherwise,
// insert the word into the list with frequency 1. sort the final
// list and output each word and the number of times it occurs
// in the file

#include <iostream>
#include <fstream>
#include <cstdlib>		// for exit()
#include <list>
#include <string>

#include "d_search.h"	// for list seqSearch()
#include "d_wfreq.h"		// for wordFreq
#include "d_util.h"		// for writeList()

using namespace std;

int main()
{
	ifstream fin;
	// words read from file and inserted into wf
	list<wordFreq> wf;
	// use for seqSearch() and displaying the list
	list<wordFreq>::iterator iter;
	// prompt for the name of the file
	string fileName, word;

	cout << "Enter the name of the file containing the words: ";
	cin >> fileName;

	// error checking
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	// read a word until end-of-file
	while (fin >> word)
	{
		// declare a wordFreq object with frequency 1
		wordFreq obj(word);

		// search for word in the list wf
		iter = seqSearch<wordFreq> (wf.begin(), wf.end(), obj);

		// did we locate the word?
		if (iter != wf.end())
			// yes. increment the word frequency
			(*iter).increment();
		else
			// word is new. insert obj into the list
			wf.push_back(obj);
	}

	// list member function sort() orders the list
	wf.sort();

	// output each object on a separate line
	cout << endl;
	writeList(wf, "\n");

	return 0;
}

/*
File "wf.dat"

peter piper picked a peck of pickled peppers
a peck of pickled peppers peter piper picked
if peter piper picked a peck of pickled peppers
where is the peck that peter piper picked

Run:

Enter the name of the file containing the words: wf.dat

a (3)
if (1)
is (1)
of (3)
peck (4)
peppers (3)
peter (4)
picked (4)
pickled (3)
piper (4)
that (1)
the (1)
where (1)
*/
