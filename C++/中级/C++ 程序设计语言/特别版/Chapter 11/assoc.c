// Simple associative array example
// to illustrate overloading of subscripting

// pp 286-287, sec 11.8 Subscripting

// No guarantees offered. Constructive comments to bs@research.att.com

#include<vector>
#include<string>
#include<iostream>
using namespace std;

class Assoc {
	struct Pair {
		string name;
		double val;
		Pair(string n ="", double v =0) :name(n), val(v) { }
	};
	vector<Pair> vec;

	Assoc(const Assoc&);			// private to prevent copying
	Assoc& operator=(const Assoc&);	// private to prevent copying
public:
	Assoc() {}
	const double& operator[](const string&);
	double& operator[](string&);
	void print_all() const;
};

const double& Assoc::operator[](const string& s)
	// search for s; return its value if found; otherwise, make a new Pair and return the default value 0
{
	for (vector<Pair>::const_iterator p = vec.begin(); p!=vec.end(); ++p)
		if (s == p->name) return p->val;

	vec.push_back(Pair(s,0));	// initial value: 0

	return vec.back().val;		// return last element (_org.element_)
}

double& Assoc::operator[](string& s)
	// search for s; return its value if found; otherwise, make a new Pair and return the default value 0
{
	for (vector<Pair>::iterator p = vec.begin(); p!=vec.end(); ++p)
		if (s == p->name) return p->val;

	vec.push_back(Pair(s,0));	// initial value: 0

	return vec.back().val;		// return last element (_org.element_)
}

void Assoc::print_all() const
{
	for (vector<Pair>::const_iterator p = vec.begin(); p!=vec.end(); ++p)
		cout << p->name << ": " << p->val << '\n';
}

int main()	// count the occurrences of each word on input
{
	string buf;
	Assoc vec;
	while (cin>>buf) vec[buf]++;
	vec.print_all();
}
