//File:  DeluxeCounter.cpp

#include "DeluxeCounter.h"

DeluxeCounter::DeluxeCounter()
{
	//automatically calls Count constructor
	//first, so count is getting set to 0 there
	name = "";
	what = "";

}
DeluxeCounter::DeluxeCounter(string n, string w, int c)
{
	//we assign values here
	count = c;
	name = n;
	what = w;
}

//new version of print, includes name/what
void DeluxeCounter::PrintCount()
{
	cout << "\n" << name << " has " << count
		<< " " << what << ".";
}
