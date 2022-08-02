//A program that asks the user to enter a value (N),
//and then we sum the numbers from 1 to N 

#include <iostream>
#include <iomanip>
using namespace std;


//Function Prototypes
int Get_Number();         
int Add_1_to_N(int);

int main()
{
	int x,sum;

	x = Get_Number();		//call to function to get the user's number
	sum = Add_1_to_N(x);    //pass x, adder returns the sum 

	cout << "The result from adding 1 + 2 + ... + " << x << 
		" is " << sum << endl;

	return 0;
}

int Get_Number()         //Function header line
{
	int number;
	cout <<"Enter a number ";
	cin >> number;
	return number;
}

int Add_1_to_N(int n)
{
	int total = 0,i;

	for(i = 1; i <= n; ++i)
	{
		total = total + i;
	}
	return total;
}

