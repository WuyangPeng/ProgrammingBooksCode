#include <algorithm>
#ifndef __GNUC__
#include <ios>
#endif
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Ptr.h"
#include "Student_info.h"

using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::sort;
using std::streamsize;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;

#ifdef _MSC_VER
#include "../minmax.h"
#else
using std::max;
#endif

bool compare_Core_handles(const Ptr<Core>& lhs, const Ptr<Core>& rhs) {
	return compare(*lhs, *rhs);
}
int main()
{
	vector< Ptr<Core> > students;       // changed type
	Ptr<Core> record;                   // changed type
	char ch;
	string::size_type maxlen = 0;

	// read and store the data
	while (cin >> ch) {
		if (ch == 'U')
			record = new Core;      // allocate a `Core' object
		else
			record = new Grad;      // allocate a `Grad' object

		record->read(cin);  //  `Ptr<T>::->', then `virtual' call to `read'
		maxlen = max(maxlen, record->name().size()); // `Ptr<T>::->'
		students.push_back(record);
	}

	// `compare' must be rewritten to work on `const Ptr<Core>&'
	sort(students.begin(), students.end(), compare_Core_handles);

	// write the names and grades
#ifdef _MSC_VER
	for (std::vector< Ptr<Core> >::size_type i = 0;
#else
	for (vector< Ptr<Core> >::size_type i = 0;
#endif
	     i != students.size(); ++i) {
		// `students[i]' is a `Ptr', which we dereference to call the functions
		cout << students[i]->name()
		     << string(maxlen + 1 - students[i]->name().size(), ' ');
		try {
			double final_grade = students[i]->grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
			     << setprecision(prec) << endl;
		} catch (domain_error e) {
			cout << e.what() << endl;
		}
		// no `delete' statement
	}
	return 0;
}

