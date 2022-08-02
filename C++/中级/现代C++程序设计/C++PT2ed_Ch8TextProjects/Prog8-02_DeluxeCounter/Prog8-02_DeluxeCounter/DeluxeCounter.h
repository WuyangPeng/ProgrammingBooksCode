//File: DeluxeCounter.h

#ifndef _DELUXE_COUNTER_H
#define _DELUXE_COUNTER_H

#include <iostream>
#include <string>
using namespace std;

#include "Counter.h"

//This class inherits all the protected 
//and public members of the Counter class

class DeluxeCounter : public Counter
{
private:
	string name, what;

public:
	DeluxeCounter();
	DeluxeCounter(string n, string w, int c);

	//set name and what
	void SetName(string n){ name = n; }
	void SetWhat(string w){ what = w; }

	//decrement counter too
	void operator --(){ --count; }

	//new version of print, includes name/what
	void PrintCount();
};

#endif




