//Casting Chars into Ints, 
//Using ios flags to view in octal and hex notation

#include <iostream>		//for cout and cin
#include <iomanip>		//for setw

using namespace std;

int main ()
{
	char char1, char2;
	int nChar1, nChar2;

	cout << "Enter two characters ==> ";
	cin >> char1 >> char2;

	cout << "\nYour Characters: " << setw(5) << char1
			<< setw(5) << char2;
	
	nChar1 = static_cast<int>(char1);    //cast into integers
	nChar2 = static_cast<int>(char2);

	cout << "\n   Decimal form: " << setw(5) << nChar1
			<< setw(5) << nChar2;

	//turn off decimal flag, turn on octal flag
	cout.unsetf(ios::dec);
	cout.setf(ios::oct);
	cout << "\n     Octal form: " << setw(5) << nChar1  
			<< setw(5) << nChar2;

	//turn off octal, turn on hex
	cout.unsetf(ios::oct);
	cout.setf(ios::hex);
	cout << "\n       Hex form: " << setw(5) << nChar1  
			<< setw(5) << nChar2 << endl;
	
	return 0;
}
