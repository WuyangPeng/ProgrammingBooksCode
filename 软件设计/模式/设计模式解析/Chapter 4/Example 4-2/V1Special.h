#pragma once
#include "specialfeature.h"

class V1Special :
    public SpecialFeature
{
public:
    V1Special(int, int);
public:
    ~V1Special(void);
private:
    int myModelNumber;
    int myID;
};