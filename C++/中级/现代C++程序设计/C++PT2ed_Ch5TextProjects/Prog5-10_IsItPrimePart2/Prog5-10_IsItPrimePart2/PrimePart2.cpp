//Is It Prime? Part 2
//Asks the user to enter a positive integer and
//determines if the number is prime.
//If it isn't prime, we obtain one of the numbers
//divisors, other than 1 and itself.


#include <iostream>
#include <string>
using namespace std;

//function declarations
int GetPositiveNumber(); 
bool CheckIt(int number);

//use reference variable to obtain divisor value     
bool IsItPrime(int number, int &divisor);

int main()
{
	int number, divisor;
	string answer;

	do
	{
		//get the number from the user
		number = GetPositiveNumber();

		//now check if it is prime
		bool result = IsItPrime(number, divisor);

		if(result == true) 
		{
			cout << "The value " << number << " is prime.  \n";
		}
		else
		{
			cout << "The value " << number << " is NOT prime.";
			cout << "\nOne divisor is " << divisor << endl;
		}

		cout << "Do another number? yes/no ";
		getline(cin,answer);
		cout << endl;

	}while(answer == "yes");

	return 0;
}

int GetPositiveNumber()
{
	int number;
	bool OK;

	do 
	{
		cout << "Please enter a positive integer ==>  ";
		cin >> number;
		cin.ignore();  //strip out the Enter key from queue
		OK = CheckIt(number);  //true if positive

		if(OK == false)
		{
			cout << "\nValue is not positive, please re-enter ";
		}
	}while(OK == false);

	return number;
}

bool CheckIt(int number)
{
	if(number <= 0)	return false;
	else	return true;
}


bool IsItPrime(int number, int &divisor)
{
	int remainder, ctr=2;
	divisor = -1;				//set to -1 in case prime
	
	//loop from 2 to n-1 and check remainder from modulus
	//if a number doesn't have a remainder, there is a
	//value that "goes into" it, therefore not prime
	while(ctr < number )  
	{
		 remainder = number%ctr;
		 if(remainder == 0)  
		 {
			  //ah ha! number has a divisor, not prime
			 divisor = ctr;
			 return false;   
		 }
		 ctr++;
	}

	//since we divided the number by all values 
	//from 2 to n-1, and didn't have a 0 remainder
	//the number is prime

	return true;
}
