//File: BoatFunctions.cpp
//This file contains the function definitions
//of for the functions declared in BoatFunctions.h

#include <iostream>
#include <string>
using namespace std;

//display a program greeting
void WriteGreeting()
{
	cout << "Welcome to the C++ Boat Rental Program"
			<< "\nWe have a fine selection of watercraft for your"
			<< " enjoyment. \n";
}

//ask user to select a boat type
string WhatKindOfBoat()
{
	int choice;
	
	cout << "\nSelect your boat:"
		<< "\n1-paddle boat $5/hr"
		<< "\n2-canoe  $8/hr"
		<< "\n3-speed boat  $30/hr plus gasoline"
		<< "\n4-party barge $60/hr plus gasoline\n ==> ";
	cin >> choice;
	cin.ignore();

	switch(choice)
	{
	case 1: return "paddle boat";
	case 2: return "canoe";
	case 3: return "speed boat";
	case 4: return "party barge";
	default: return "paddle";  //just in case mistyped
	}
}

//how long to keep the boat?
int RentalDuration(string boatType)
{
	int hours;

	cout << "\nHow long do you wish to use the " << boatType << "?";
	cout << "\nRental options:  \n2 hours \n4 hours (1/2 day)"
		<< "\n8 hours (all day) \n ==> ";
	cin >> hours;
	cin.ignore();

	//check to be sure hrs are 2, 4, or 8
	if(hours == 2 || hours == 4 || hours == 8)
	{
		return hours;    //valid rental time
	}
	else
	{
		//make the user keep the boat all day  ;-)
		cout << "\nInvalid hours, we're sure you want the" <<
			boatType << " all day.";
		return 8;
	}
}

//if it is party barge or speed boat, set the 
//gasoline per hour usage rate
int GasolineReqmt(string boatType)
{
	int gallonsPerHour;
	if(boatType == "speed boat")
		gallonsPerHour = 3;
	else if(boatType == "party barge")
		gallonsPerHour = 2;
	
	cout << "\nThe " << boatType << " uses " << gallonsPerHour
		<< " gallons of gas each hour. ";

	return gallonsPerHour;
}

//calculate total rental cost
float CalcRentalCost(string boatType, int hours)
{
	float boatCost, gasCost= static_cast<float>(0.0);
	float gallonsPerHour;

	if(boatType == "speed boat" || boatType == "party barge")
	{
		cout << "\nThe " << boatType << 
			" has gasoline $ur-charge $$ ";

		gallonsPerHour = GasolineReqmt(boatType);

		cout << "\nThe C++ Gas Center charges only $10/gallon.\n";
		gasCost = hours*gallonsPerHour*10;
	}

	if(boatType == "paddle boat") boatCost = hours * 5.0;
	else if(boatType == "canoe")boatCost = hours * 8.0;
	else if(boatType == "speed boat")boatCost = hours * 30 + gasCost;
	else //this is the party barge
		boatCost = hours * 60 + gasCost;

	return boatCost;
}

