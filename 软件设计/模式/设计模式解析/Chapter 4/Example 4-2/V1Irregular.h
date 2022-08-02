#pragma once
#include "irregularfeature.h"

class V1Irregular :
    public IrregularFeature
{
public:
    V1Irregular(int, int);
public:
    ~V1Irregular(void);
private:
    int myModelNumber;
    int myID;
};