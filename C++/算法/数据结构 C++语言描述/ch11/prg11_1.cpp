
#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg11_1.cpp
// input the name of a file containing lowercase letters
// and no punctuation marks. call spellChecker() to check
// its spelling. the function creates a dictionay by
// inserting the whitespace separated lowercase words in
// the file "dict.dat" into a set. the function then
// reads the words in the document, looking each up in
// the set. a word is considered misspelled if it is not
// in the set. in this situation, prompt the user
// to add the word to the dictionary (input 'a'), ignore the
// word because is it actually spelled correctly ('i') or
// confirm it as misspelled (input 'm')

#include <iostream>
#include <fstream>
#include <string>
#include <set>

#include "d_util.h"	// for writeContainer()

using namespace std;

// check filename for spelling errors
void spellChecker(string& filename);

int main()
{
	string fileName;

	cout << "Enter the document to spell check: ";
	cin >> fileName;

	// check the spelling
	spellChecker(fileName);

	return 0;
}

void spellChecker(string& filename)
{
	// sets storing the dictionary and the misspelled words
	set<string> dictionary, misspelledWords;

	// dictionary and document streams
	ifstream dict, doc;
	string word;
	char response;

	// open "dict.dat"
	dict.open("dict.dat");
	if (!dict)
	{
		cerr << "Cannot open \"dict.dat\"" << endl;
		exit(1);
	}

	// open the document file
	doc.open(filename.c_str());
	if (!doc)
	{
		cerr << "Cannot open " << filename << endl;
		exit(1);
	}

	// insert each word from the file "dict.dat" into the dictionary set
	while(true)
	{
		dict >> word;
		if (!dict)
			break;

		// insert into the dictionary
		dictionary.insert(word);
	}

	// read the document word by word and check spelling
	while(true)
	{
		doc >> word;
		if (!doc)
			break;

		// lookup word up in the dictionary. if not present
		// assume word is misspelled. prompt user to add or ignore word
		if (dictionary.find(word) == dictionary.end())
		{
			cout << word << endl;
			cout << "    'a' (add)  'i' (ignore)  'm'  (misspelled) " ;
			cin >> response;
			// if response is 'a' add to dictionary; otherwise add to the
			// set of misspelled words
			if (response == 'a')
				dictionary.insert(word);
			else if (response == 'm')
				misspelledWords.insert(word);
		}
	}

	// display the set of misspelled words
	cout << endl << "Set of misspelled words" << endl;
	writeContainer(misspelledWords.begin(), misspelledWords.end());
	cout << endl;
}

/*
File "spell.tst"
teh message contians the url for the web-page
and a misspeled url for the email adress

Run:

Enter the document to spell check: spell.tst

teh
    'a' (add)  'i' (ignore)  'm'  (misspelled) m
contians
    'a' (add)  'i' (ignore)  'm'  (misspelled) m
url
    'a' (add)  'i' (ignore)  'm'  (misspelled) a
web-page
    'a' (add)  'i' (ignore)  'm'  (misspelled) i
misspeled
    'a' (add)  'i' (ignore)  'm'  (misspelled) m
email
    'a' (add)  'i' (ignore)  'm'  (misspelled) i
adress
    'a' (add)  'i' (ignore)  'm'  (misspelled) m

Set of misspelled words
adress  contians  misspeled  teh
*/
