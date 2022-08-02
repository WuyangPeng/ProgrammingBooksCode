#pragma once
#include "Tax.h"
class USTax:public Tax
{
public:
 static USTax* getInstance();
 virtual double calcTax(double qty, double price);
protected:
 USTax(void);
 ~USTax(void);
private:
 static USTax * myInstance;
}; 