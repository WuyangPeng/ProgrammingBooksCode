// Count occurrences of elements in various containers using find()
// to illustrate generic algoriths and iterators.

// pp 58-59, sec 3.8.1, Use of Iterators

// No guarantees offered. Constructive comments to bs@research.att.com


#include<iostream>
#include<algorithm>
#include<string>
#include<complex>
#include<vector>
#include<list>

using namespace std;

typedef complex<double> dcomplex;	// In the book, I cheated slightly, sorry
					// the standard library complex is a template



template<class C, class T> int count(const C& v, T val)
{
	typename C::const_iterator i = find(v.begin(),v.end(),val);	// "typename;" see C.13.5
	int n = 0;
	while (i != v.end()) {
		++n;
		++i;	// skip past the element we just found
		i = find(i,v.end(),val);
	}
	return n;
}

void f(list<dcomplex>& lc, vector<string>& vc, string s)
{
	int i1 = count(lc,dcomplex(1,3));
	int i2 = count(vc,"Chrysippus");
	int i3 = count(s,'x');

	cout << "number of complex(1,3)s " << i1 << "\n";
	cout << "number of \"Chrysippus\"s " << i2 << "\n";
	cout << "number of 'x's in \"" << s << "\" : " << i3 << "\n";
}

int main()
{
	vector<string> philo;
	philo.push_back("Aristotle");
	philo.push_back("Plato");
	philo.push_back("Chrysippus");
	philo.push_back("Zeno");

	list<dcomplex> spline;
	spline.push_back(dcomplex(1,3));
	spline.push_back(dcomplex(1,7));
	spline.push_back(dcomplex(1,3));
	spline.push_back(dcomplex(7,3));

	string boat = "Exxon Valdez";

	f(spline,philo,boat);

	return 0;	// redundant in ISO C++
}
