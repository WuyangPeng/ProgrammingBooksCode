// Read file and output sorted list of words.
// Illustrates generic algoriths and I/O.

// Note: This program reads the name of its input and out files
// from standard input.

// p6 61, sec 3.8.3, Iterators and I/O

// No guarantees offered. Constructive comments to bs@research.att.com

// August 20, 2002

#include<fstream>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>
#include<vector>

using namespace std;



int main()
{
	string from, to;
	cin >> from >> to;			// get source and target file names

	ifstream is(from.c_str());		// input stream (c_str(); see sec3.5.1, sec20.3.7)
	istream_iterator<string> ii(is);	// input iterator for stream
	istream_iterator<string> eos;		// input sentinel


	vector<string> b(ii,eos);		// b is a vector initialized from input
	sort(b.begin(),b.end());		// sort the buffer

	ofstream os(to.c_str());		// output stream
	ostream_iterator<string> oo(os,"\n");	// output iterator for stream

	unique_copy(b.begin(),b.end(),oo);	// copy buffer to output,
						// discard replicated values

	return !is.eof() && !os;		// return error state (sec3.2, sec21.3.3)
}
