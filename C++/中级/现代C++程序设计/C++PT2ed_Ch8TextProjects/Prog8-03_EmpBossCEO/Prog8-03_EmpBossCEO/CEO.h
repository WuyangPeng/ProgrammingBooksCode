//File:  CEO.h

#ifndef  _CEO_H
#define  _CEO_H

#include "Boss.h"

class CEO: public Boss
{
protected:
	int stock_options;
public:
	void AskEmpInfo();
	void WriteEmpInfo();
};

#endif
