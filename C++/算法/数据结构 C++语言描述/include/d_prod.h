#ifndef PRODUCT_CLASS
#define PRODUCT_CLASS

#include <string>

using namespace std;

class product
{
	public:
		product(const string& cmpny = "", const string& nm = "" ):
					company(cmpny), name(nm)
		{}

		// access the value of the product company
		string getCompany() const
		{ return company; }

		// access the value of the product name
		string getName() const
		{ return name; }

		// determine order of objects based on value of company
		friend bool operator< (const product& lhs, const product& rhs)
		{ return lhs.company < rhs.company; }

		// check for objects with the same company
		friend bool operator== (const product& lhs, const product& rhs)
		{ return lhs.company == rhs.company; }

	 private:
		string company;
		string name;
};

#endif	// PRODUCT_CLASS
