// vars.h - Script 12.x

#include <string>

// Define some meaningless variables.
int plainVar = 1;
static int staticVar = 10;
int externVar = 100;

// Need constants.
int plainConstant = 2;
extern int externConstant = 20;

// Create a function for
// printing a variable's value.
inline void printVar(std::string name, int value) {
	std::cout << "The value of " 
	<< name << " is " 
	<< value << "\n";
}
