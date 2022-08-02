#pragma once
#include "Tax.h"
class USTax:public Tax
{
public:
 static USTax* Instance();
protected:
 USTax(void);
private:
 static USTax * myInstance;
};