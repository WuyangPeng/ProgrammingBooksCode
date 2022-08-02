//Temperature conversion demonstrating
//how to code from C to F and F to C equations.  

//Notice how we end up where we started! :-)

#include <iostream>     //for cout and cin
using namespace std;

int main ()             
{ 
	double celsius, farenheit;

	//Format cout output for 3 decimal places 
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(3);

	cout << "Welcome to the C++ Temp Converter Program";

	cout << "\nBegin by entering the current temp in F ==> ";
	cin >> farenheit;
	cout << "You entered " << farenheit << " F"
		<< "\nLet's convert it to Celsius " ;

	//Convert F to C
	//Notice that we code the fraction correctly!  
	celsius = 5.0/9.0*(farenheit - 32.0);
	cout << "\nResultant Celsius temp = " << celsius;

	cout << "\n\nLet's be sure we calculated C correctly"
			<< "\nby converting it back to F ";

	//Convert celsius back to farenheit degrees
	farenheit = 9.0/5.0*celsius + 32.0;
	cout << "\n\nResultant Farenheit temp = " << farenheit;

	cout << "\nAre they the same temps?  :-) \n\n" ;
	
	return 0;
}
