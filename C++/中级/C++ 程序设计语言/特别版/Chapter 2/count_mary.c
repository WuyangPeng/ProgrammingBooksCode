// Count occurrences of character in string using find()
// to illustrate simple use of iterators and algorithms.

// pp 57-58, sec 3.8.1, Use of Iterators

// No guarantees offered. Constructive comments to bs@research.att.com


#include<iostream>
#include<algorithm>
#include<string>

using namespace std;


int count(const string& s, char c)	// count occurrences of c in s
{
	int n = 0;
	string::const_iterator i = find(s.begin(),s.end(),c);
	while (i != s.end()) {
		++n;
		i = find(i+1,s.end(),c);
	}
	return n;
}


void f()
{
	string m = "Mary had a little lamb";
	int a_count = count(m,'a');

	cout << "\"" << m << "\" contains " << a_count << " 'a's\n";
}

int main()
{
	f();

	return 0;	// redundant in ISO C++
}
