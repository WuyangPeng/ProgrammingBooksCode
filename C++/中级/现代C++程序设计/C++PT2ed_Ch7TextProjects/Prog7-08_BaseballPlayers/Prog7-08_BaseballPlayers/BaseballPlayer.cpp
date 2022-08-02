//File: BaseballPlayer.cpp

#include "BaseballPlayer.h"
#include <iostream>
#include <string>

using namespace std;

BaseballPlayer::BaseballPlayer()
{
	name = "";
	homers = RBI = 0;
}

BaseballPlayer::BaseballPlayer(string n,int h, int rbi)
{
	name = n;
	homers = h;
	RBI = rbi;
}

bool BaseballPlayer::operator > (BaseballPlayer bbp)
{
	if( homers > bbp.homers)
		return true;
	else if(homers == bbp.homers)
	{
		if(RBI > bbp.RBI)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool BaseballPlayer::operator < (BaseballPlayer bbp)
{
	if( homers < bbp.homers)
		return false;
	else if(homers == bbp.homers)
	{
		if(RBI < bbp.RBI)
			return false;
		else
			return true;
	}
	else
		return true;
}

void BaseballPlayer::operator ! ()
{
	++homers;
	cout << "\n" << name  << " just hit a homer!";
	cout << "\nHe now has " << homers << " home runs!\n";
}

void BaseballPlayer::WritePlayerStats()
{
	cout << "" << name << " has " << homers << 
		" home runs " << "and " << RBI << " RBIs " << endl;
}