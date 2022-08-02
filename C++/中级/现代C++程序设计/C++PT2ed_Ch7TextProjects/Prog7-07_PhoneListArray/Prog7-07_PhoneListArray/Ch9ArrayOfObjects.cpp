//File: ArrayOfObjects.cpp
//Array of Objects Program      
//This program  uses an array of PhoneList objects
//It read 5 entries from a data file.

#include <iostream>      
#include <string>         
#include <fstream>
		
#include "PhoneList.h"

using namespace std;
#define FILE_IN "phonebook.txt"

int main()
{
	//make an array of 5 PhoneList objects
	PhoneList mylist[5];   
	
	//input stream for reading from file
	ifstream input;                  

	//open input 
	input.open(FILE_IN, ios::in); 
 
	//Check to be sure file is opened.  
	if(!input)  
	{
		cout << "\nCan't find input file " << FILE_IN;
		cout << "\nExiting program, bye bye \n ";
		exit(1);
	}

	string buffer;
	int count = 0;

	//read until we reach end of file
	//use set functions for each object
	while( !input.eof() )  
	{
		//read name
		getline(input,buffer);
		mylist[count].SetName(buffer);

		//read address
		getline(input,buffer);
		mylist[count].SetAddress(buffer);

		//read number
		getline(input,buffer);
		mylist[count].SetNumber(buffer);

		++count;
	}

	cout.setf(ios::left);    //left justify output

	cout << "\nYour Address Book contains these " 
		<< count << " listings: ";

	for(int i=0; i< count ; ++i)
	{
		mylist[i].ShowListing();
	}

	input.close();
	cout << "\nAnd a gracious goodbye!  \n";
	return 0;
}
