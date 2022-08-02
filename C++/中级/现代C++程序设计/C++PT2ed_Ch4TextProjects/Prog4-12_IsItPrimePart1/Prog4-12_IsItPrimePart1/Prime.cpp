//Is It Prime?
//Asks the user to enter a positive integer and
//determines if the number is prime.


#include <iostream>
#include <string>
using namespace std;

//function declarations
int AskPosNumber();      
bool IsItPrime(int number);
bool CheckIt(int number);

int main()
{
	int n;
	string answer;

	do
	{
		//get the number from the user
		n = AskPosNumber();

		//now check if it is prime
		bool result = IsItPrime(n);

		if(result == true) 
		{
			cout << "The value " << n << " is prime.";
		}
		else
		{
			cout << "The value " << n << " is NOT prime.";
		}

		cout << "\nDo another number? yes/no ";
		getline(cin,answer);
		cout << endl;
	}while(answer == "yes");

	return 0;
}


int AskPosNumber()
{
	int num;
	bool OK;

	do 
	{
		cout << "Please enter a positive integer ==>  ";
		cin >> num;
		cin.ignore();  //strip out the Enter key from queue
		OK = CheckIt(num);  //true if positive

		if(OK == false)
		{
			cout << "Value is not positive, please re-enter \n";
		}
	}while(OK == false);

	return num;
}

bool CheckIt(int number)
{
	if(number <= 0)	
		return false;
	else
		return true;
}


bool IsItPrime(int number)
{
	int remainder, ctr=2;
	
	//loop from 2 to n-1 and check remainder from modulus
	//if a number doesn't have a remainder, there is a
	//value that "goes into" it, therefore not prime
	while(ctr < number )  
	{
		 remainder = number%ctr;
		 if(remainder == 0)  
		 {
			  //ah ha! number has a divisor, not prime
			  return false;   
		 }
		 ctr++;
	}

	//since we divided the number by all values 
	//from 2 to n-1, and didn't have a 0 remainder
	//the number is prime

	return true;
}
