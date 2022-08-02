#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg12_3.cpp
// program makes empirical comparisons of four searching methods,
// the sequential search, binary search, and the use of a binary
// search tree and a hash table. inputs 25025 word lists from files
// "udict.dat"/"sdict.dat". former file has words in random order,
// and later has words in sorted order. randomly ordered words are
// inserted into vector vrand and binary search tree bstree and
// hash table object ht. sorted words inserted into vector vsort.
// for each algorithm, a timer object used to determine number of
// seconds required to search for words in container. vsort words
// used as keys for sequential search and for find() function of
// binary search tree and hash table. words in vrand are keys for
// binary search

#include <iostream>
#include <fstream>
#include <vector>

#include "d_stree.h"
#include "d_hash.h"
#include "d_hashf.h"
#include "d_timer.h"
#include "d_search.h"

using namespace std;

int main()
{
	// vectors that store strings in random and sorted order
	vector<string> vrand, vsort;
	// declare a binary search tree and hash table with elements
	// from vrand. the hash table has 1373 buckets.
	hash<string, hFstring> ht(1373);
	stree<string> bstree;

	// objects used in the search tests
	ifstream unsortedStrings, sortedStrings;
	string word;
	timer t;
	int len, method, i;

	// open 25000+ word dictionaries
	unsortedStrings.open("udict.dat");
	sortedStrings.open("sdict.dat");

	while(true)
	{
		// input a word from the randomly ordered dictionary
		unsortedStrings >> word;
		if (!unsortedStrings)
			break;

		// insert word into the randomly ordered vector
		vrand.push_back(word);
		// insert word into the binary search tree
		bstree.insert(word);
		// insert word into the hash table
		ht.insert(word);

		// input a word from the sorted dictionary
		sortedStrings >> word;
		// insert word into the sorted vector
		vsort.push_back(word);
	}

	// output the number of words
	len = vrand.size();
	cout << "Number of words is " << len << endl << endl;

	// test the four search methods
	for (method = 0; method < 4; method++)
	{
		// start the timer
		t.start();
		// implement the search
		switch(method)
		{
			// sequential search of random words with list of sorted words
			case	0:	for (i = 0; i < len; i++)
							seqSearch(vrand, 0, len, vsort[i]);
						t.stop();
						cout << "Sequential search time is ";
						break;
			// binary search of sorted words with list of random words
			case	1:	for (i = 0; i < len; i++)
							binSearch(vsort, 0, len, vrand[i]);
						t.stop();
						cout << "Binary search time is ";
						break;
			// binary tree search of random words with list of sorted words
			case	2:	for (i = 0; i < len; i++)
							bstree.find(vsort[i]);
						t.stop();
						cout << "Binary tree search time is ";
						break;
			// hash search of random words with list of sorted words
			case	3:	for (i = 0; i < len; i++)
							ht.find(vsort[i]);
						t.stop();
						cout << "Hash search time is ";
						break;
		}
		cout << t.time() << " seconds" << endl;
	}

	return 0;
}

/*
Run:

Number of words is 25025

Sequential search time is 126.642 seconds
Binary search time is 0.21 seconds
Binary tree search time is 0.2 seconds
Hash search time is 0.121 seconds
*/
