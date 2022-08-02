//File: RainBarrelDriver.cpp

#include <iostream>
#include <string>
using namespace std;

#include "RainBarrelEst.h"

int main()
{
	RainBarrelEst barrel;

	barrel.AskForData();
	barrel.WriteData();

	return 0;
}
