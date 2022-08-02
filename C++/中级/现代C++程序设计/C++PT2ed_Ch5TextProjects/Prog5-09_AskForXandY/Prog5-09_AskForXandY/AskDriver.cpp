//Demonstrate the both pointers and references
//in one program.

#include <iostream>
using namespace std;

void AskForXandY(int *pX, int *pY);
void AskForXandY(int &rX, int &rY);

int main()
{
	int x, y;
	//Pass the addresses to the pointers.
	AskForXandY(&x,&y);

	//Use variable names when passing to references.
	//The addresses are actually passed.
	AskForXandY(x,y);

	return 0;
}

//Call by reference using pointers and indirection operator.
void AskForXandY(int *pX, int *pY)
{
	cout << "\n enter x and y  ";
	cin >> *pX >> *pY;
}

//Call by reference using reference parameters.
void AskForXandY(int &rX, int &rY)
{
	cout << "\n enter x and y   ";
	cin >> rX >> rY;
}

