#pragma once
#include "specialfeature.h"
#include "OOGFeature.h"

class V2Special :
    public SpecialFeature
{
public:
    V2Special(OOGFeature *feature);
public:
    ~V2Special(void);
private:
    OOGFeature *myOOGFeature;
};