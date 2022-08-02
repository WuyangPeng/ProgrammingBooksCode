//File: FBPlayer.h
                               
#ifndef _FBPLAYER_H
#define _FBPLAYER_H

#include <string>
#include <iostream>
using namespace std;

class FBPlayer
{
private:
    int weight, feet, inches, totalinches;
    string name;
public:
    FBPlayer();
    void SetName(string n) { name = n;}
    void SetWeight(int w) { weight = w;}
    void SetHeight(int ft, int in);
    void WriteInfo();

	//the taller player is "bigger"
	//if they are the same height, then
	//the heavier player is "bigger"
    bool operator > (FBPlayer p);                   
};

#endif
