//File: Vehicles.h
//To keep it simple, we'll leave all 
//three class declarations in this file.

//If the classes were of any size, they
//should be placed in separate .h files.

#ifndef  _VEHICLES_H
#define  _VEHICLES_H

#include <iostream>
#include <string>
using namespace std;


class Vehicle
{
protected:
	string owner, license;
	string VIN;

public:
	Vehicle(){};
	virtual void AskInfo();  
	virtual void WriteInfo();
};


class RV:public Vehicle
{
private:
	char category;	//RV class A, B, C

public:
	RV(){};
	void AskInfo();
	void WriteInfo();
};


class Semi:public Vehicle
{
private:
	double weightCap;	//weight capacity
public:
	Semi(){};
	void AskInfo(); 
	void WriteInfo();
};

#endif
