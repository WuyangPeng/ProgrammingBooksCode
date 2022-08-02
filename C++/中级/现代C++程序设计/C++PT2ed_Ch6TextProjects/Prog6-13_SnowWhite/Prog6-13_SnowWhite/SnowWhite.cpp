//A short program with Snow White and The Seven Dwarfs
//Uses a 2D C-string Array.

#include <iostream>
using namespace std;

//prototype shows input is a 2-D array 
void WriteNames(char dwarfs[][10]); 

int main()
{
	// Declare and initialize the array
	char dwarfs[7][10] = { "Doc", "Grumpy",
			"Dopey", "Bashful", "Sleepy",
			"Sneezy", "Happy" };

	WriteNames(dwarfs);

	return 0;
}

//function to write the seven names
void WriteNames(char dwarfs[][10])
{
	cout << "Here are the Seven Dwarfs \n";
	for (int i = 0; i < 7; ++i) 
	{
		cout << "Dwarf # " << i+1 << " is " << dwarfs[i] << endl;
	}
}

