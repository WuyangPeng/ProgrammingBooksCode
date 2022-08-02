/*
 * This file contains code from "C++ Primer, Fourth Edition", by Stanley B.
 * Lippman, Jose Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
 * "Copyright (c) 2005 by Objectwrite, Inc., Jose Lajoie, and Barbara E. Moo."
 * 
 * 
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 * 
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address: 
 * 
 * 	Pearson Education, Inc.
 * 	Rights and Contracts Department
 * 	75 Arlington Street, Suite 300
 * 	Boston, MA 02216
 * 	Fax: (617) 848-7047
*/ 

#include "algs_preamble.h"
// combine elements into a parenthesized, comma-separated pair
string combine(string x, string y)
{
	return "(" + x + ", " + y + ")";
}
// add two strings, each separated by a comma
string concatenate(string x, string y)
{
	if (x.empty())
		return y;
	return x + ", " + y;
}

int main()
{
	vector<string> names, values;
	names.push_back("if");
	values.push_back("keyword");
	names.push_back("string");
	values.push_back("library type");
	names.push_back("sort");
	values.push_back("algorithm");

	cout << inner_product(names.begin(), names.end(),
	                      values.begin(), string(),
	                      concatenate, combine);
}
