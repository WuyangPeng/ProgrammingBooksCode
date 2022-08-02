//File: Kitty.cpp

#include "Kitty.h"
#include <iostream>
#include <string>

using namespace std;

Kitty::Kitty()       //constructor
{
    breed = "unknown";
    name = "Kitty Kitty";
    favFood = "fresh chicken";
}

void Kitty::PrintCatInfo()
{
    cout << "\n" << name << " is a(n) " << breed 
		<< " cat who loves " << favFood;
}                                                    
