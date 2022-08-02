//File:  BoatFunctions.h

//This file contains the prototypes for the
//C++ Boat Rental program.

#include <string>
using namespace std;

string WhatKindOfBoat();
int RentalDuration(string boatType);
int GasolineReqmt(string boatType);
float CalcRentalCost(string boatType, int hours);
void WriteGreeting();
