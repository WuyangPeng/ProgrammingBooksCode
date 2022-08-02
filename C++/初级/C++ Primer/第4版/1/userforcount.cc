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

#include <iostream>

int main()
{
	std::cout << "Enter two numbers:" << std::endl;
	int v1, v2; 
	std::cin >> v1 >> v2; // read input

	// use smaller number as lower bound for summation
	// and larger number as upper bound
	int lower, upper;
	if (v1 <= v2) {
		lower = v1;
		upper = v2;
	} else {
		lower = v2;
		upper = v1;
	}

	int sum = 0;

	// sum values from lower up to and including upper
	for (int val = lower; val <= upper; ++val) 
		sum += val;  // sum = sum + val
	
	std::cout << "Sum of " << lower 
	          << " to " << upper 
	          << " inclusive is " 
	          << sum << std::endl;

	return 0;
}
