//File:  Counter.h
//A simple class that has an integer counter.

#ifndef _COUNTER_H
#define _COUNTER_H

#include <iostream>
using namespace std;

class Counter
{
private:
	int count;
public:
	Counter(){count = 0;}
	void operator ++(){ ++count; }
	int GetCount() { return count; }
	void SetCount( int c ) { count = c; }
	void PrintCount() { cout << "\nThe count is " << count; }
};

#endif
