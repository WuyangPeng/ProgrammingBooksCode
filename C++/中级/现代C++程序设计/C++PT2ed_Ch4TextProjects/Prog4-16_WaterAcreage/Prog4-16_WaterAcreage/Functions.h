//File:  Functions.h

//This file contains the prototypes for the
//C++ Farm Irrigation program.

#include <iostream>
#include <string>
using namespace std;

int AskDepthOfWater();
float AskIrrigationRate();
float AskFieldSize();
void WriteGreeting();
string CalculateTimeAndGallons(int depth, float rate, 
							   float acres);
