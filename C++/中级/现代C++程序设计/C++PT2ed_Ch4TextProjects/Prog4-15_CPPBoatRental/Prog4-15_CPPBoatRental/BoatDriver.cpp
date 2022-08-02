//File:  BoatDriver.cpp

//This file contains the main function for
//the C++ Boat Rental program.

#include "BoatFunctions.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
	WriteGreeting();

	string boatType;

	boatType = WhatKindOfBoat();
	int hours = RentalDuration(boatType);

	float cost = CalcRentalCost(boatType,hours);

	cout << "Your " << boatType << " will cost you $" 
		<< setprecision(2) << setiosflags(ios::fixed) <<  cost 
		<< " for " << hours << " hours. Have fun! \n";

	cout << "\nWould you be interested in renting life jackets? \n";

	return 0;
}
