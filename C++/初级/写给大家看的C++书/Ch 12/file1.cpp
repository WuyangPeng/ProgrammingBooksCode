// file1.cpp - Script 12.x

#include <iostream>

// Include the vars.h
// header file.
#include "vars.h"

// Define some meaningless variables.
int plainFile1 = 3;
static int staticFile1 = 30;
extern int externVar;

int main() {

	printVar("plainFile1", plainFile1);
	
	std::cout << "Press Enter or Return to continue.";
	std::cin.get();
	return 0;
	
} // End of main().

