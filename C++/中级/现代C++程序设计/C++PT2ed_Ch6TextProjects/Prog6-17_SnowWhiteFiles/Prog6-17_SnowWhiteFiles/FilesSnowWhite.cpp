//File: FilesSnowWhite.cpp
//A short program with the Seven Dwarfs
//Uses a 2D Character String Array.

#include <iostream>
using namespace std;

#include "DwarfFunctions.h"


int main()
{
	// Declare three 2-D arrays
	char dwarfs[7][10];
	char verticalDwarfs[10][8];
	char backwardsDwarfs[7][10];
	
	bool good = ReadNames(dwarfs);
	if( !good)
	{
		cout << "\nCouldn't find the file. ";
		exit(1);
	}

	TurnVertical(dwarfs,verticalDwarfs);
	ReverseNames(dwarfs, backwardsDwarfs);
	WriteArraysToScreen(dwarfs, 
				verticalDwarfs,backwardsDwarfs);

	return 0;
}

