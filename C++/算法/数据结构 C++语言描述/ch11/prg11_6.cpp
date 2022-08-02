#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg11_6.cpp
// the program initializes the multiset softwareSet with software
// product entries. the multiset has duplicates, since some of the
// products have the same vendor. the program outputs the number of
// software products and prompts for a vendor. after outputting the
// number of products for the vendor, the program outputs the set
// of products in the format
//    Vendor: company
//        Products: name1  name2   . . .

#include <iostream>
#include <string>
#include <set>

#include "d_prod.h"

using namespace std;

int main()
{
	product prodArr[] = 
		{product("Microsoft", "Visual C++"), product("Inprise", "C++ Builder"),
		 product("Microsoft", "Word"), product("Ramsoft", "MAS"),
		 product("Inprise", "J Builder"), product("Adobe", "Photoshop"),
		 product("Microsoft", "Excel"), product("Adobe", "Illustrator")};
	int prodArrSize = sizeof(prodArr)/sizeof(product);
	// softwareSet is a multiset of product objects
	multiset<product> softwareSet(prodArr, prodArr+prodArrSize);

	// an iterator and iterator pair for the output
	multiset<product>::iterator iter;
	pair<multiset<product>::iterator, multiset<product>::iterator> p;

	// vendor name used for input
	string vendorName;

	cout << "Number of software products = " << softwareSet.size()
		  << endl << endl;

	// prompt for the name of a vendor
	cout << "Enter a vendor name: ";
	cin >> vendorName;
	cout << endl;
	cout << "There are " << softwareSet.count(product(vendorName, ""))
		  << " " << vendorName << " products in the set" << endl << endl;

	// loop outputs the products in the ascending order of vendor (company)
	iter = softwareSet.begin();
	while (iter != softwareSet.end())
	{
		// determine the range of products with company (*iter).getCompany()
		p = softwareSet.equal_range(*iter);
		cout << "Vendor: " << (*iter).getCompany() << endl
			  << "    Products: ";
		// output each product for the company
		while (iter != p.second)
		{
			cout << (*iter).getName() << "  ";
			iter++;
		}
		cout << endl;
	}

	return 0;
}

/*
Run:

Number of software products = 8

Enter a vendor name: Microsoft

There are 3 Microsoft products in the set

Vendor: Adobe
    Products: Photoshop  Illustrator
Vendor: Inprise
    Products: C++ Builder  J Builder
Vendor: Microsoft
    Products: Visual C++  Word  Excel
Vendor: Ramsoft
    Products: MAS
*/
