//File: FBSortDriver.cpp
//This program demonstrates how overloaded
//operators in classes can be used to sort
//an array of Football Player objects. 

#include "FBPlayer.h"
#include <iostream>
#include <fstream>
using namespace std;

#define FILE "Players.txt"

bool ReadFootballPlayers(string &rName, 
						 FBPlayer team[], int& rTotal);

void SortPlayers(FBPlayer team[], int total);

int main()
{
	FBPlayer team[6];  //football player objects
	string teamName;
    int total;

    cout << "Welcome to the Sorting Football "
		" Players Program  \n";

    bool bError = ReadFootballPlayers(teamName, team, total);
    if(bError)
    {
        cout << "\n\ncouldn't find file " << FILE;
        exit(1);
    }

	cout << "\nTeam: " << teamName;

    cout << "\nThe original order of players: ";
    for (int i= 0; i < total; ++ i)
    {
        team[i].WriteInfo();
    }

    SortPlayers(team, total);

    cout << "\n\nThe sorted Players are: ";
	                                                       
	for (int i= 0; i < total; ++ i)
    {
        team[i].WriteInfo();
    }

    cout << "\nThese are big fellows! \n";
   
    return 0;
}

void SortPlayers(FBPlayer team[], int total)
{
	// a classic bubble sort for FBPlayers
	// sorts from low to high

    int i, j;
    FBPlayer temp;
    for(i = 0; i < (total - 1) ; ++i)           
    {
        for(j = 1; j < total; ++j)
		{
			//this is possible since we've 
			//defined the > for FBPlayer objectsRe
            if(team[j-1] > team[j] )
            {
                temp = team[j];
                team[j] = team[j-1];
                team[j-1] = temp;
            }
        }
    }
}

bool ReadFootballPlayers(string &rTeamName, 
						FBPlayer team[], int &rTotal)
{                           
    //opens and reads the input filename, 
	//and fills the team data

    int wt, ft, in;
    string buffer;

    ifstream input;
    input.open(FILE);

    if(!input)return true;

	//first read the team name
    getline(input,rTeamName);
	
	int i = 0;

	while (! input.eof() )
    {
		//Read the name
        getline(input, buffer);
        team[i].SetName(buffer);

		//now read 3 ints
        input >> ft >> in >> wt;
		
		//strip off end of line
        input.ignore();

		//set data into object
        team[i].SetWeight(wt);
        team[i].SetHeight(ft,in);

		++i;
    }

	rTotal = i;
    input.close();

    return false;
}
