// Bjarne Stroustrup 7/26/2009
// Chapter 10 Exercise 9

/*
	Merge two sorted files; that is the files are ordered so that word[i]<word[i+1] in each input file,
	now copy from the two files so that word[i]<word[i+1] in the resulting output file,

*/

#include "std_lib_facilities.h"	

/*
	If you think about it for a short while, you'll realize this is simple:
		we know how to open files (and here we need three)
		we know how to read strings from an input stream until there are no more to read
	
	The problem here is one of devising an algorithm:
		The two input files may not have the same number of elements
		As long as there are words in both files, we have to copy words from one until
		we find a word from the other that's larger.
	Most people's first attempt at that is a rat's nest of if statements. Just try!

	Because merging data from several sources is a common and important problem, there are
	many solutions to "how to merge." I cannot go into that in any detail.
*/


/*
	here is part of my first draft solution:

	string s1;
	string s2;
	while (is1>>s1 && is2>>s2) {	// as long as there are words in both files
		if (s1<s2) {
			os << s1 << '\n';
			while (is1>>s1 && s1<s2) os << s1 << '\n';	// copy from is1 as long as s1<s2
			os << s2 << '\n';
			is1.putback(s1);	// not "consumed" and there may not be a s1
		}
		else {	// s1 >= s2
			os << s2 << '\n';
			while (is2>>s2 && !(s1<s2)) os << s2 << '\n';	// copy from is2 as long as s1>=s2
			os << s1 << '\n';
			is2.putback(s2);	// not "consumed" and there may not be a s2
		}
	}

	The problem here is that there is no putback of strings into an istream. That makes sense because
	a string might be a million characters long, but it does spoil a relatively simple solution.

	To proceed along this line, we need is something like the Toke_stream from 6.8, except for strings.

*/

/*

	But do we really need a stream of strings with pushback? Can't we be just a little bit more clever?

*/


int main()
try
{
	cout << "please enter two input file names: ";
	string n1,n2;
	cin>>n1>>n2;
	ifstream is1(n1.c_str());
	if (!is1) error("bad input file name ", n1);
	ifstream is2(n2.c_str());
	if (!is2) error("bad input file name ", n2);
	
	cout << "please enter an output file names: ";
	string n;
	cin>>n;
	ofstream os(n.c_str());
	if (!os) error("bad output file name ", n);

	string s1 = "";	// use "" to mean "no word available"
					// note: cin>>s1 can never read an empty string into s1
					// so we can use "" to indicate that we need to read
	string s2 = "";
	while (true) {
		if (s1=="" && !(is1>>s1)) break;	// no more words in n1
											// note: "break" breaks out of a loop
		if (s2=="" && !(is2>>s2)) break;	// no more words in n2
		if (s1<s2) { 
			os << s1 << '\n';
			s1 = "";	// we have consumed s1
		}
		else {	// s1 >= s2
			os << s2 << '\n';
			s2 = "";	// we have consumed s2
		}
	}

	if (s1!="") os << s1 << '\n';	// in case s1 was left over
	if (s2!="") os << s2 << '\n';	// in case s2 was left over

	while (is1>>s1) os << s1 << '\n';	// in case n1 has more words
	while (is2>>s2) os << s2 << '\n';	// in case n2 has more words

	keep_window_open("~");	// For some Windows(tm) setups
}
catch (runtime_error e) {	// this code is to produce error messages; it will be described in Chapter 5
	cout << e.what() << '\n';
	keep_window_open("~");	// For some Windows(tm) setups
}
catch (...) {	// this code is to produce error messages; it will be described in Chapter 5
	cout << "exiting\n";
	keep_window_open("~");	// For some Windows(tm) setups
}

/*
	How many characters of this program would you have to change to get a program that merged files
	of whitespace-separated sorted integers? floating-point numbers? Roman numbers?
*/

