//This program fills a BINGO card using
//the rand() function. 

//We use several of our own functions to help us.

#include <iostream>
#include <iomanip>
using namespace std;

//Function prototypes
void PrintCard(int BCard[][5]);
void FillCard(int BCard[][5]);

int main()
{
	//use 2D array of ints for our card
	int BingoCard[5][5];

	cout <<"We're going to generate a BINGO card"
		<< "\nusing the random number generator."
		<< "\nNo duplicate values allowed on our card!";

	FillCard(BingoCard);

	PrintCard(BingoCard);

	return 0;
}

/*This card fills the Bingo card with random numbers.
	BINGO cards have 75 random numbers
	First Col  B  1-15
	Second Col I 16-30
	Third Col  N 31-45
	Fourth Col G 46-60
	Fifth Col  O 61-75

  We also use a bool check array to keep track
  of generated value. If we have used a number
  we have to re-generate one for that square.
  This prevents duplicate values on card.   */

void FillCard(int BCard[][5])
{
	int row, col, value, i;
	bool check[76];    //need values 1-75

	//First fill check array with falses
	for(i = 0; i < 76; ++i)  
		check[i] = false;
	
	bool again;  //flag to get another value

	for(col = 0; col < 5; ++ col) //work on each col
	{
		//now go down each row
		for(row = 0; row < 5; ++ row)
		{
			//check if we're at [2][2] FREE
			if(row == 2 && col == 2)
			{
				BCard[row][col] = 100; //indicate FREE
				continue;	//jump to next loop iteration
			}

			again = true;
			do
			{
				//first generate a number between 1-15
				value = rand()%15 + 1;

				//offset it by 15 for each column
				value = value + (col*15);
	
				//now check if we've gotten that number before
				//if we have, do this again	
				if(check[value] == false) 
				{
					BCard[row][col] = value;
					check[value] = true;
					again = false;
				}
			}while(again == true);
		}
	}
}

void PrintCard(int BCard[][5])
{
	cout << "\nHere is your BINGO card. Good Luck! \n";
	char Top[10] = "BINGO";
	int row, col, i;

	for(i = 0; i < 5; ++i)
		cout << setw(6) << Top[i];

	cout << endl;

	//now print the card, row by row
	for(row = 0; row < 5; ++ row)
	{
		for(col = 0; col < 5; ++ col)
		{
			if(col == 2 && row == 2)
				cout << setw(6) << "FREE";
			else
				cout << setw(6) << BCard[row][col];
		}
		cout << endl; 
	}
}



