//DrawLines function has a 
//default parameter input list. 

#include <iostream>
using namespace std;

//The prototype contains the default values.
void DrawLines(char symbol = '%', int numOfSymbols= 25, 
			   int numOfLines = 1 );  


int main()
{
	cout << "The DrawLines Program \n\n";
	cout << "Default Line 25 % on 1 line";
	DrawLines();    
	cout << "\nChange to 30 @ to a line";
	DrawLines('@', 30);  
	cout << "\nNow draw 15 # on 3 lines";
	DrawLines('#',15,3);
	cout << "\n\nLast line has 6 % on 1 line";
	DrawLines('%',6);

	cout << "\nNo more lines for you. \n";

	return 0;

}

//The function definition does not contain the default values.
void DrawLines(char symbol, int numSymbols, int numOfLines )  
{
	int i, j;
	cout << "\n";
	for(i=0; i < numOfLines; ++i)
	{
		for(j=0; j< numSymbols; ++j)
		{
			cout << symbol;
		}
		cout << "\n";
	}
}

