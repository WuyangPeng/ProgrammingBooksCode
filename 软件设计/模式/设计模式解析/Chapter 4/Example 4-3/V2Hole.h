#pragma once
#include "holefeature.h"
#include "OOGFeature.h"

class V2Hole :
    public HoleFeature
{
public:
    V2Hole(OOGFeature *feature);
    double getX();
public:
    ~V2Hole(void);
private:
    OOGFeature *myOOGFeature;
};