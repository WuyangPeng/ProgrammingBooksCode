//A program that generates 100 random numbers
//in one function and uses a bubble sort to 
//sort the array.

#include <iostream>
#include <ctime>		//for time function
#include <cstdlib>		//for rand()
using namespace std;


//functions need array [] in prototype
void Sort(int numbers[], int total);  
void GenRandNums(int numbers[], int total);
void ShowFirstLast5(int numbers[], int total);  
						   
int main()
{
	int numbers[100], total = 100;

	cout << "Make 'em, Show 'em, Sort 'em, Show 'em again. ";


	GenRandNums(numbers, total);

	cout << "\nHere are the unsorted values.";
	ShowFirstLast5(numbers, total);

	Sort(numbers, total);

	cout << "\nHere are the sorted values.";
	ShowFirstLast5(numbers, total);

	return 0;
}

//Generate a "total" number of random values.
void GenRandNums(int numbers[], int total)
{

	//Seed the generator with the system time.
	srand(time (NULL) );
	for (int i = 0; i < total; ++ i)
	{
		//rand() gives us values between 0 and 32767
		numbers[i] = rand();
	}
}

//Sort using the Bubble sort technique, slow but simple. 
//Sorts array from low to high
void Sort(int numbers[], int total)
{
	int i,j, temp;

	//compare adjacent values, switch if out of order
	for(i = 0; i < total-1; ++i)
	{
		for(j = 1; j < total; ++ j)
		{
			if(numbers[j-1] > numbers[j])
			{
				temp = numbers[j];
				numbers[j] =numbers[j-1];
				numbers[j-1] = temp;
			}
		}
	}
}


void ShowFirstLast5(int numbers[], int total)
{
	cout << "\nFirst 5 values \n";

	for(int i = 0; i < 5; ++i)
		cout << "numbers[" << i << "] " << numbers[i] << endl;
	
	cout << "\nLast 5 values \n";
	for(int i = total - 5; i < total; ++i)
		cout << "numbers[" << i << "] " << numbers[i] << endl;

}

