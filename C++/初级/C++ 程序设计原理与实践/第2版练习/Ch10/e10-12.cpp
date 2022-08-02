// Bjarne Stroustrup 1/17/2010
// Chapter 10 Exercise 12

/*
	Write a program that given a file name and a word outputs each line that contains that
	word together with the line number. Hint: getline().

*/

#include "../std_lib_facilities.h"	


/*
	What is "a word"? I "carelessly" used that phrase in the problem statement and now I/we have to decide what it
	should mean. Beware of casual wording in requirements.

	OK: Let's define "word" as "whatever string's >> think it is (that is, "a whitespace terminated sequence of characters").
	Alternative definitions, such as "an arbitrary sequence of characters specified by the user" could be even more
	interesting as an exercise.

	This exercise gets much easier after Chapter 11! (then I could use getline() and strstream).

	However, let me solve it here without using anything from Chapter 11 except the getline() mentioned in the hint.
*/

bool match(const string& s, int i, const string& w)
	// is s[i] the start of w?
{
	for (int j=0; j<w.size(); ++j) {
		if (s.size()<=j+i) return false;	// we ran out of character to match against
		if (s[i+j]!=w[j]) return false;
	}
	return true;	// we matched all of w
}


int main()
try
{
	cout << "Please enter an input file names: ";
	string name;
	cin>>name;
	ifstream ifs(name.c_str());
	if (!ifs) error("bad input file name: ", name);
	
	cout << "Please enter a word to search for: ";
	string word;
	cin >> word;

	int line_no = 0;
	string line;
	while (getline(ifs,line)) {
		++line_no;	// we read another line
		for (int i=0; i<line.size(); ++i)
			if (match(line,i,word)) {
				cout << line_no << ": " << line << '\n';
				break;	// don't find a word twice
			}
	}

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

	If you wonder what file to use as input, try this source file.
	For testing, I searched it for "search" and "ifs" and (correctly got two matches for "search" and four for "ifs"

	This exercise gets much more interestinmg in Chaoter 23 where we can use a regular expression pattern instead of a plain word.
*/
