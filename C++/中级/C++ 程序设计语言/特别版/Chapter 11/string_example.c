// Define simple string class, and exercise it a bit

// pp pp 292-298, sec 11.12, A String Class

// No guarantees offered. Constructive comments to bs@research.att.com

// writing your own string class is a good exercise.
// Once you have learned from that, throw it away and use std::string

#include<iostream>
using namespace std;

class String {
	struct Srep;			// representation
	Srep *rep;

	class Cref;			// reference to char
public:

	class Range { };		// for exceptions
	
	String();			// x = ""
	String(const char*);		// x = "abc" 
	String(const String&);	// x = other_string
	String& operator=(const char *);
	String& operator=(const String&);
	~String();

	void check(int i) const;

	char read(int i) const;
	void write(int i, char c); 

	Cref operator[](int i);
	char operator[](int i) const;

	int size() const;

	String& operator+=(const String&);
	String& operator+=(const char*);

	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);

	friend bool operator==(const String& x, const char* s);

	friend bool operator==(const String& x, const String& y);

	friend bool operator!=(const String& x, const char* s);

	friend bool operator!=(const String& x, const String& y);
};

String operator+(const String&, const String&);
String operator+(const String&, const char*);

struct String::Srep {
	char* s;	// pointer to elements
	int sz;		// number of characters
	int n;		// reference count

	Srep(int nsz, const char* p)
	{
		n = 1;
		sz = nsz;
		s = new char[sz+1];	// add space for terminator
		strcpy(s,p);
	}

	~Srep() { delete[] s; }

	Srep* get_own_copy()	// clone if necessary
	{
		if (n==1) return this;
		n--;	
		return new Srep(sz,s);
	}

	void assign(int nsz, const char* p)
	{
		if (sz != nsz) {
			delete[] s;
			sz = nsz;
			s = new char[sz+1];
		}
		strcpy(s,p);
	}

private:				// prevent copying:
	Srep(const Srep&);
	Srep& operator=(const Srep&);
};

class String::Cref {		// reference to s[i]
friend class String;
	String& s;
	int i;

	Cref(String& ss, int ii) : s(ss), i(ii) { }
	Cref(const Cref& r) : s(r.s), i(r.i) { }
	Cref();	// not defined, never used
public:
	operator char() const { s.check(i); return s.read(i); }	// yield value
	void operator=(char c) { s.write(i,c); }			// change value
};

String::String()		// the empty string is the default value 
{
	rep = new Srep(0,"");
}

String::String(const String& x)	// copy constructor
{
	x.rep->n++;
	rep = x.rep;	// share representation
}

String::~String()
{
	if (--rep->n == 0) delete rep;
}

String& String::operator=(const String& x)	// copy assignment
{
	x.rep->n++;				// protects against ``st = st''
	if (--rep->n == 0) delete rep;
	rep = x.rep;				// share representation
	return *this;
}

String::String(const char* s)
{
	rep = new Srep(strlen(s),s);
}

String& String::operator=(const char* s)
{
	if (rep->n == 1)			// recycle Srep
		rep->assign(strlen(s),s);
	else {					// use new Srep
		rep->n--;
		rep = new Srep(strlen(s),s);
	}
	return *this;
}

void String::check(int i) const
{
	if (i<0 || rep->sz<=i) throw Range();
}

char String::read(int i) const
{
	return rep->s[i];
}

void String::write(int i, char c)
{
	rep=rep->get_own_copy();
	rep->s[i]=c;
} 

String::Cref String::operator[](int i)
{
	check(i);
	return Cref(*this,i);
}

char String::operator[](int i) const
{
	check(i);
	return rep->s[i];
}

int String::size() const
{
	return rep->sz;
} 

ostream& operator<<(ostream& os, const String& s)
{
	return os << s.rep->s;
}

#include<string>

istream& operator>>(istream& is, String& s)
// this implementation is "almost cheating" :-)
{
	string ss;
	is >> ss;
	s = ss.c_str();
	return is;
}

bool operator==(const String& x, const char* s)
{
	return strcmp(x.rep->s, s) == 0;
}

bool operator==(const String& x, const String& y)
{
	return strcmp(x.rep->s, y.rep->s) == 0;
}

bool operator!=(const String& x, const char* s)
{
	return strcmp(x.rep->s, s) != 0;
}

bool operator!=(const String& x, const String& y)
{
	return strcmp(x.rep->s, y.rep->s) != 0;
}

void ff(String s, const String& r)
{
	char c1 = s[1];	// c1 = s.operator[](1).operator char()
	s[1] = 'c';		// s.operator[](1).operator=('c')

	char c2 = r[1];	// c2 = r.operator[](1)
//	r[1] = 'd';		// error: assignment to non-lvalue char, r.operator[](1) = 'd'
}

int hash(const String& s)
{
	int h = s.read(0);
	const int max = s.size();
	for (int i = 1; i<max; i++) h ^= s.read(i)>>1;	// unchecked access to s
	return h;
}

String f(String a, String b)
{
	a[2] = 'x';
	char c = b[3];
	cout << "in f: " << a << ' ' << b << ' ' << c << '\n';
	return b;
}


int main()
// very simple minded first test
{
	String x, y;
	cout << "Please enter two strings\n";
	cin >> x >> y;
	cout << "input: " << x << ' ' << y << '\n';

	String z = x;
	y = f(x,y);
	if (x != z) cout << "x corrupted!\n";
	x[0] = '!';
	if (x == z) cout << "write failed!\n";
	cout << "exit: " << x << ' ' << y << ' ' << z << '\n';
}
