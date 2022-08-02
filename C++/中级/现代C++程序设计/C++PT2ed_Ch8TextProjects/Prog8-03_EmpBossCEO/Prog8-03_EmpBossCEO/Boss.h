//File:  Boss.h

#ifndef  _BOSS_H
#define  _BOSS_H

#include "Employee.h"

class Boss: public Employee
{
protected:
	float bonus;
public:
	void AskEmpInfo();
	void WriteEmpInfo();
};

#endif
