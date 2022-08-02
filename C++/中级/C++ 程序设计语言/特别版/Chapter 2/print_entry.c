// example illustrating the use of std::list.

// This is *not* an example of good style, just an illustration of facilities

// pp 54-55, sec 3.7.3

// No guarantees offered. Constructive comments to bs@research.att.com


#include<list>
#include<iostream>
#include<string>

using namespace std;


struct Entry {
	string name;
	int number;
	Entry(const string& n, int i) :name(n), number(i) { }
};

list<Entry> phone_book;

void print_entries()
/*
	this kind of function should use a parameter,
	rather then a global name
*/
{
	typedef list<Entry>::const_iterator LI;

	for (LI i = phone_book.begin(); i != phone_book.end(); ++i) {
		const Entry& e = *i;	// reference used as shorthand
			cout << '{' << e.name << ' ' << e.number << "}\n";
	}
}

void print_entry(const string& s)
/*
	Is this the right treatment of a string not found?
*/
{
	typedef list<Entry>::const_iterator LI;

	for (LI i = phone_book.begin(); i != phone_book.end(); ++i) {
		const Entry& e = *i;	// reference used as shorthand
		if (s == e.name) {
			cout << e.name << ' ' << e.number << '\n';
			return;
		}
	}
}

void f(const Entry& e, list<Entry>::iterator i, list<Entry>::iterator p)
/*
	just some nonsense code
*/
{
	phone_book.push_front(e);	// add at beginning
	phone_book.push_back(e);	// add at end
	phone_book.insert(i,e);		// add before the element referred to by `i'

	phone_book.erase(p);		// remove the element referred to by `p'
}

int main()
{

	phone_book.push_back(Entry("one",1));
	phone_book.push_back(Entry("two",2));
	phone_book.push_back(Entry("three",3));
	phone_book.push_back(Entry("four",4));
	phone_book.push_back(Entry("five",5));
	Entry six("six",6);
	print_entries();
	f(six,phone_book.begin(),phone_book.begin());
	print_entries();
	print_entry("four");
	print_entry("seven");
	print_entry("three");
}
