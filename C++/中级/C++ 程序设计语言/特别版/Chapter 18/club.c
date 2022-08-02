// Simple test program to exercise standard algorithms and function objects

// "Club" examples scattered throughout Chapter 18 

// No guarantees offered. Constructive comments to bs@research.att.com

#include<list>
#include<iostream>
#include<algorithm>
#include<functional>
#include<string>
#include<vector>
#include<iterator>
using namespace std;

namespace {
	string noname = "";
	string noaddr = "";
}

struct Person {
	string name;
	string addr;

	Person(const string& n, const string& a = noaddr) :name(n), addr(a) { }
};

struct Club {
	string name;
	list<Person*> members;
	list<Person*> officers;
	// ...
	string town;

	Club(const string& n) :name(n) {}
};

class Club_eq : public unary_function<Club,bool> {
	string s;
public:
	explicit Club_eq(const string& ss) : s(ss) { }
	bool operator()(const Club& c) const { return c.name==s; }
};


class Extract_officers {
	list<Person*>& lst;
public:
	explicit Extract_officers(list<Person*>& x) : lst(x) { }

	void operator() (const Club& c) const
	{ copy(c.officers.begin(),c.officers.end(),back_inserter(lst)); }
};

void extract(const list<Club>& lc, list<Person*>& off)
// place the officers from `lc' on `off'
{
	for_each(lc.begin(),lc.end(),Extract_officers(off));
}

class Print_name {
	ostream& os;
public:
	Print_name(ostream& s) :os(s) { }
	void operator()(Person* p) { os << p->name << endl; }
};


void extract_and_print(const list<Club>& lc)
{
	cout << "\nPrint officers:\n";

	list<Person*> off;
	extract(lc,off);
	for_each(off.begin(),off.end(),Print_name(cout));
}

string nameof(const Club& c) { return c.name; }	// extract name string


void f(list<Club>& lc)
{
	cout << "\nPrint names:\n";

	transform(lc.begin(),lc.end(),ostream_iterator<string>(cout,"\n"),nameof);
}

bool operator==(const Person& x, const Person& y)
// equality for object
{
	// compare x and y for equality
	return x.name == y.name;	// simple minded
}

bool operator<(const Person& x, const Person& y)
// less than for object
{
	// compare x and y for order
	return x.name < y.name;	// simple minded
}

bool Person_eq(const Person* x, const Person* y)
// equality through pointer
{
	return *x == *y;
}

bool Person_lt(const Person* x, const Person* y)
// less than through pointer
{
	return *x < *y;
}

void extract_and_print2(const list<Club>& lc)
{
	cout << "\nPrint officers in alphabetic order:\n";

	list<Person*> off;	// not list
	extract(lc,off);
	off.sort(Person_lt);
	//sort(off.begin(),off.end(),Person_lt);
	list<Person*>::iterator p = unique(off.begin(),off.end(),Person_eq);
	for_each(off.begin(),p,Print_name(cout));
}


class located_in : public unary_function<Club,bool> {
	string town;
public:
	located_in(const string& ss) :town(ss) { }
	bool operator()(const Club& c) const { return c.town == town; }
};

void ff(list<Club>& lc)
{
	cout << "\nPrint clubs located in Kbh:\n";

	remove_copy_if(lc.begin(),lc.end(),
		ostream_iterator<Club>(cout),not1(located_in("Kbh")));
}

ostream& operator<<(ostream& s, const Person& p)
{
	return s << "(" << p.name << "," << p.addr << ")";
}

ostream& operator<<(ostream& s, const list<Person*>& c)
{
	for (list<Person*>::const_iterator p = c.begin(); p!=c.end(); ++p)
		s << **p << ", ";
	return s;
}

template<class T> ostream& operator<<(ostream& s, const list<T>& c)
{
//	for (list<T>::const_iterator p = c.begin(); p!=c.end(); ++p)
//		s << *p << ", ";
	copy(c.begin(),c.end(),ostream_iterator<T>(s,", "));
	return s;
}
ostream& operator<<(ostream& s, const Club& c)
{
	s << c.name << "{ ";
	s << "[off: " << c.officers << " ]";
	s << "[mem: " << c.members << " ]";
	s << c.town ;
	return s << " }\n";
}

void make_person_list(list<Person*>& lst,
	const string& s1 = noname,
	const string& s2 = noname,
	const string& s3  = noname)
{
	if (&s1!=&noname) lst.push_back(new Person(s1));
	if (&s2!=&noname) lst.push_back(new Person(s2));
	if (&s3!=&noname) lst.push_back(new Person(s3));
}

int main()
{
	list<Club> snoot;
	snoot.push_back(Club("Horsy"));
	make_person_list(snoot.back().members,"Major","Tops");
	make_person_list(snoot.back().officers,"Major","Tops");
	snoot.back().town = "Kbh";
	snoot.push_back(Club("Hunt"));
	make_person_list(snoot.back().members,"Elk","Fox","Hare");
	make_person_list(snoot.back().officers,"Riffle");
	snoot.back().town = "Kbh";
	snoot.push_back(Club("Over_eat"));
	make_person_list(snoot.back().members,"Dinner","Breakfast","Lunch");
	make_person_list(snoot.back().officers,"Dinner","Lunch");
	snoot.back().town = "Paris";
	snoot.push_back(Club("Drink_and_be_merry"));
	make_person_list(snoot.back().members,"Beer","Red","Wiskey");
	make_person_list(snoot.back().officers,"Red");
	snoot.back().town = "Paris";

	cout << snoot;

	f(snoot);

	ff(snoot);

	extract_and_print(snoot);

	extract_and_print2(snoot);
}
