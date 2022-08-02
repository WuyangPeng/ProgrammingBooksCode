#ifndef GRADUATE_CLASS
#define GRADUATE_CLASS

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class graduate
{
	public:
		// default constructor; objects are initialized with input >>
		graduate()
		{}

		// return the degree obtained by the graduate
		string getDegree() const
		{ return degree; }

		// two objects are equal if they have the same name
		friend bool operator== (const graduate& lhs, const graduate& rhs)
		{
			return lhs.name == rhs.name;
		}

		// two objects are equal if the names are alpabetically ordered
		friend bool operator< (const graduate& lhs, const graduate& rhs)
		{
			return lhs.name < rhs.name;
		}

		// input name and degree from a file. each line contains
		// the name, ssn and degree separated by a tab character
		friend istream& operator>> (istream& istr, graduate& grad)
		{
			getline(istr, grad.name,'\t');		
			getline(istr, grad.degree,'\n');

			return istr;
		}

		// output the name and degree for the graduate
		friend ostream& operator<< (ostream& ostr, const graduate& grad)
		{
			// left justify output
			ostr.setf(ios::left, ios::adjustfield);

			ostr << setw(20) << grad.name << grad.degree;

			// restore right justification
			ostr.setf(ios::right, ios::adjustfield);

			return ostr;
		}

	private:
		string name;
		string degree;
};

#endif	// GRADUATE_CLASS
