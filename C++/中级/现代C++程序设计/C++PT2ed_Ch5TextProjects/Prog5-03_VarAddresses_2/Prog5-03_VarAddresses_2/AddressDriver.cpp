//This program shows the five properties of 
//these three C++ data items. 
//A variable's memory address (in hex notation)
//is obtained by using the address operator &. 

//The sizeof operator gives us the number of bytes
//that are reserved for C++ variables. 

#include <iostream>
#include <string>
#include <iomanip>		//for setw
using namespace std;

int main()
{
	//declare and assign variables
	int n = 42;
	double  pi = 3.14159;
	string s = "I love C++";

	//write out variable's type, name, address, and bytes
	cout << "A program that shows the & and sizeof operators.\n";
	
	cout << "\nData Type   Name  Value      Address   Bytes";

	cout << "\n   int      n " << setw(8) << n << setw(14) 
			<< &n << setw(6) << sizeof(n);
	cout << "\n  double    pi " << setw(9) << pi << setw(12) 
			<< &pi << setw(6) << sizeof(pi);

	cout << "\n\n Class    Name    Value        Address  ";
	cout << " \nstring    s " << setw(14) << s << setw(12) 
			<< &s << endl;
	
	return 0;
}

