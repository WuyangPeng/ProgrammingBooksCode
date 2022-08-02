//Variables, Addresses and Pointers 
//In this program we declare an int and double,
//and pointers, and assign the addresses
//into the pointers. 

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int a = 75;
	double b = 82.0;
	int *a_ptr;
	double *b_ptr;

	//now we assign the address of vars into pointers
	a_ptr = &a;          
	b_ptr = &b;

	//write out info
	cout << "VARIABLE    VALUES    ADDRESSES" <<
        "\n a     " << setw(12) << a << setw(12) << &a << 
		"\n b     " << setw(12) << b << setw(12) << &b << 
		"\n a_ptr "  << setw(12)<< a_ptr << setw(12) << &a_ptr << 
		"\n b_ptr "  << setw(12)<< b_ptr << setw(12) << &b_ptr << endl;

	return 0;
}

 