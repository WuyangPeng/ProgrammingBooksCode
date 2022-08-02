//File: Kitty.h

#ifndef _KITTY_H
#define _KITTY_H

#include <iostream>
#include <string>
using namespace std;

class Kitty
{
private:
    string breed, name;
    string favFood;

public:
    Kitty();
    void SetBreed(string b){breed = b;}
    void SetName(string n) {name = n; }
    void SetFavFood(string ff) {favFood = ff; }
    void PrintCatInfo();
};

#endif