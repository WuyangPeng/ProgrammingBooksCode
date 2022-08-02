//Demonstrate the both pointers and references
//in one program.

#include <iostream>
#include <string>
#include <iomanip>		//for setw
using namespace std;

void AskUsingPtrs(int *pInt, double *pD, string *pStr);
void AskUsingRefs(int &rInt, double &rD, string &rStr);

int main()
{
	//declare 6 variables
	int n, m;
	double  u, v;
	string s1, s2;

	//Pass the addresses to the pointers.
	AskUsingPtrs(&m, &u, &s1);

	//Use variable names when passing to references.
	//The addresses are actually passed.
	AskUsingRefs(n, v, s2);

	cout << "\nIn main function";
	cout << "\nThe integers are: " << m << " and " << n ;
	cout << "\nThe doubles are: " << u << " and " << v ;
	cout << "\nThe first string is: " << s1 ;
	cout << "\nThe second string is: " << s2 << endl;

	return 0;
}

//Call by reference using pointers and indirection operator.
void AskUsingPtrs(int *pInt, double *pD, string *pStr)
{
	cout << "In AskUsingPtrs Function";
	cout << "\nPlease enter an integer: ";
	cin >> *pInt;

	cout << "Please enter a double:  ";
	cin >> *pD;
	cin.ignore();

	cout << "Please enter a string:  ";
	getline(cin,*pStr);
}

//Call by reference using reference parameters.
void AskUsingRefs(int &rInt, double &rD, string &rStr)
{
	cout << "\nIn AskUsingRefs Function";
	cout << "\nPlease enter an integer: ";
	cin >> rInt;

	cout << "Please enter a double:  ";
	cin >> rD;
	cin.ignore();

	cout << "Please enter a string:  ";
	getline(cin,rStr);
}

