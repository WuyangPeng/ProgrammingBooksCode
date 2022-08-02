//File: PhoneList.h
//This class represents one phone entry.

#ifndef _PHONELIST_H
#define _PHONELIST_H

#include <string>
using namespace std;

class PhoneList
{
private:
	string name, address;
	string phNumber;
public:
	PhoneList();
	void SetName(string n) { name = n; }
	void SetAddress(string addr) { address = addr; }
	void SetNumber(string phN) { phNumber = phN;}
	void ShowListing();

};

#endif