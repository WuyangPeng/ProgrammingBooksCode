//File:  RainBarrelEst.cpp

#include "RainBarrelEst.h"

#include <iostream>
#include <string>
using namespace std;

RainBarrelEst::RainBarrelEst()
{
	cout << "Hello from your"
		<< " Rain Barrel Estimator Object!"
		<< "\nI'll calculate required barrel"
		<< " capacity given \nrain and snow totals"
		<< " in inches " << endl;
	
	barrelCapacity = 0;
}

void RainBarrelEst::AskForData()
{
	cout << "\nDescription of collection surface? ";
	getline(cin,desc);

	cout << "Timeframe for collection? ";
	getline(cin,timeframe);

	cout << "Enter total square footage"
		<< " of your collection surface: ";
	cin >> sqFootage;

	cout << "Enter total rainfall in inches: ";
	cin >> rainInches;

	//set rain values into RainVolCalc object
	rainy.SetInches(rainInches);
	rainy.SetSqFeet(sqFootage);

	//now ask about snow?
	char snowResponse;
	cout << "Will there be any snow ?  y/n ";
	cin >> snowResponse;
	cin.ignore();

	if(snowResponse == 'y')
	{
		cout << "What type of snow?"
			<< " powder, packed, sleet? ";
		getline(cin,typeOfSnow);

		cout << "How many inches of " 
			<< typeOfSnow  << " will be on your " 
			<< desc << "? "; 
		cin >> snowInches;
		cin.ignore();

		snowy.SetType(typeOfSnow);
		snowy.SetInches(snowInches);
		snowy.SetSqFeet(sqFootage);
	}
}

void RainBarrelEst::WriteData()
{
	cout << "Results for the " << desc 
			<< "\nduring " << timeframe << endl;

	cout << rainy.GetVolumeString() << endl
		<< snowy.GetVolumeString() << endl;

	float totalGal = rainy.GetGallons() +
					snowy.GetGallons();

	cout << "\nTotal Gallons for Barrel:  "
		<< totalGal << endl;

}