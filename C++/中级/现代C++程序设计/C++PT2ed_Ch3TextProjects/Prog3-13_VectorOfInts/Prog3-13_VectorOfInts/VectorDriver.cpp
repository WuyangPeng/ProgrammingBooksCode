#include <iostream>		//for cout and cin
#include <vector>		//for vector 
#include <iomanip>		//for setw()

using namespace std;

int main()
{
	vector<int> vNums;	//vector of ints

	cout <<"Demonstration of C++ Vectors ";

	//use the push_back() function to add 5 integers to the vector
	vNums.push_back(35);
	vNums.push_back(99);
	vNums.push_back(27);
	vNums.push_back(3);
	vNums.push_back(54);

	//use size() function to see how many numbers are in the vector
	cout << "\nThe vector has " << vNums.size() << " numbers.";

	//add another 2 number
	vNums.push_back(15);
	vNums.push_back(72);
	
	cout << "\nNow there are " << vNums.size()  << " numbers it.";

	//use the at() function to obtain the values from the vector
	//first element is at(0)

	cout << "\nHere are the numbers in the vector. \n";
	for(int i = 0; i < vNums.size(); ++i)
	{
		cout << setw(5) << vNums.at(i);
	}

	cout << endl;
	return 0;
}
