//File:  Counter.h
//A simple class that has an integer counter.

//To use this as a parent class, we need to
//change the private data to protected so
//it is inherited by the child class!

#ifndef _COUNTER_H
#define _COUNTER_H

#include <iostream>
using namespace std;

class Counter
{
protected:		// <-- protected, not private
	int count;
public:
	Counter(){count = 0;}
	void operator ++(){ ++count; }
	int GetCount() { return count; }
	void SetCount( int c ) { count = c; }
	void PrintCount() { cout << "\nThe count is " << count; }
};

#endif
