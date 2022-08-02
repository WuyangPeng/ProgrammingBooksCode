//File: FBPlayer.cpp

#include "FBPlayer.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
             
FBPlayer::FBPlayer()
{
	weight = 0;
	feet = inches = totalinches = 0;
	name = "";
}

bool FBPlayer::operator > (FBPlayer p)
{
	//the taller player is "bigger"
    if(feet > p.feet) return true;

    //if two players are the same height,
	//the heavier player is "bigger"
    if(feet == p.feet)
    {
        if(inches > p.inches) return true;
        else if(inches == p.inches)
        {
            if(weight > p.weight) return true;
            else return false;
        }
        else return false;
    }
    else
        return false;
}                                             

void FBPlayer::SetHeight(int ft, int in)
{
    feet = ft;
    inches = in;
}

void FBPlayer::WriteInfo()
{
    cout << endl << setw(25) <<  name 
		<< setw(8) << feet << "' " 
		<< setw(3) << inches << "\" "  
		<< setw(8) << weight << " pounds";
}

    