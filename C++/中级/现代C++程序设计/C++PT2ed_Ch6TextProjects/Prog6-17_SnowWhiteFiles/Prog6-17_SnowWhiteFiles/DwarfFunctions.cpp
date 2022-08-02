//File: DwarfFunctions.cpp

#include <iostream>
#include <fstream>
using namespace std;

#include "DwarfFunctions.h"
#define INPUT_FILE "DwarfNames.txt"

void WriteArraysToScreen(char dwarfs[][10], 
			 char vertical[][8], char backwards[][10])
{
	int i;

	cout << "Here are the 7 Dwarfs \n";
	for (i = 0; i < 7; ++i) 
	{   
		cout <<  dwarfs[i] << endl;
	}
	
	cout << "\nHere are the  7 Dwarfs Backwards \n";
	for (i = 0; i < 7; ++i) 
	{   
		cout << backwards[i] << endl;
	}

	cout << "\nHere are the 7 Dwarfs Vertical \n";
	for (i = 0; i < 10; ++i) 
	{   
		cout << vertical[i] << endl;
	}
}

void TurnVertical(char dwarfs[][10],char verticalDwarfs[][8])
{
	//initialize 0-6 col w/ ' ' and last with nulls
	for (int row = 0; row < 10; ++row) 
	{   
		for(int col = 0; col < 8; ++col)
		{
			if(col != 7)
				verticalDwarfs[row][col] = ' ';
			else
				verticalDwarfs[row][col] = '\0';
		}
	}
	
	//Place first row into first column
	//fill letter by letter,
	for (int row = 0; row < 7; ++row) 
	{   
		//obtain the length of each dwarf's name
		int length = strlen(dwarfs[row]);

		//write dwarf's name down the column
		for(int  col = 0; col < length; ++col)
		{
			verticalDwarfs[col][row] = dwarfs[row][col];
		}
	}
}

void ReverseNames(char dwarfs[][10], char backwards[][10])
{
	//Let's first fill all the elements with blanks
	//and put a null in the last element.
	for (int row = 0; row < 7; ++row) 
	{   
		for(int  col = 0; col < 8; ++col)
		{
			backwards[row][col] = ' ';
		}
		backwards[row][9] = '\0';
	}


	//Now copy letters into each row  
	for (int row = 0; row < 7; ++row) 
	{   
		//obtain the length of each dwarf's name
		int length = strlen(dwarfs[row]);

		//write dwarf's name backward, fill from far end
		//need 2 indexes, dwarf & backwards
		int dwIndex = 0;

		for(int  col = 8; col >= 8-length+1; --col)
		{
			backwards[row][col] = dwarfs[row][dwIndex];
			++dwIndex;
		}
	}
}


//Function that reads the names.
bool ReadNames(char dwarfs[][10])
{
	ifstream input;		
	input.open(INPUT_FILE);

	//check that we've got the file open
	if(! input)
	{
		cout << "\nERROR Can't find " << INPUT_FILE;
		return false;
	}

	//We'll read until the end of the file.
	//Have to have an int for each array element.
	int count = 0;

	while(!input.eof() )
	{
		input.getline(dwarfs[count],10 );
		++count;
	}

	//all done reading, close the file
	input.close();

	return true;
}

