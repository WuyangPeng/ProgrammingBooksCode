//This program fills a BINGO card using
//the rand() function. 
//We do not check for duplicates on the card. :-(

//The card is represented by a 5x5 int array.

//BINGO cards have 75 random numbers
// First Col  B  1-15
//Second Col  I 16-30
// Third Col  N 31-45
//Fourth Col  G 46-60
// Fifth Col  O 61-75

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	//use 2D array of ints for our card
	int BingoCard[5][5];

	cout <<"We're going to generate a BINGO card"
		<< "\nusing the random number generator. ";

	//We'll fill the card column by column. 

	int row, col, value;
	
	for(col = 0; col < 5; ++ col) //work on each col
	{
		//now go down each row
		for(row = 0; row < 5; ++ row)
		{
			//check if we're at [2][2] FREE
			if(row == 2 && col == 2)
			{
				BingoCard[row][col] = 100; 
				continue;   //jump to next loop iteration
			}
			
			//first generate a number between 1-15
			value = rand()%15 + 1;

			//offset it by 15 for each column
			BingoCard[row][col] = value + (col*15);
		}
	}

	cout << "\nHere is your BINGO card. Good Luck! \n";
	char Top[10] = "BINGO";

	for(int i = 0; i < 5; ++i)
		cout << setw(6) << Top[i];

	cout << endl;

	//now print the card row by row
	//use nested loops again
	for(row = 0; row < 5; ++ row)
	{
		for(col = 0; col < 5; ++ col)
		{
			if(col == 2 && row == 2)
				cout << setw(6) << "FREE";
			else
				cout << setw(6) << BingoCard[row][col];
		}
		cout << endl; 
	}

	return 0;
}