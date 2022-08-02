//A program that demonstrates the sizeof operator.

#include <iostream>
using namespace std;

int main()
{
	char c;
	double d;
	float f;
	int i;
	long  l;

	//Use sizeof with data types
	cout << "The sizeof Demonstration Program.";
	cout << "\nNumber of bytes reserved in RAM for:"
		<< "\n  char  " << sizeof(c) 
		<< "\ndouble  " << sizeof(d) 
		<< "\n float  " << sizeof(f) 
		<< "\n   int  " << sizeof(i) 
		<< "\n  long  " << sizeof(l) << endl;

	return 0;
}
