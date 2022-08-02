#pragma once
#include "cutoutfeature.h"
#include "OOGFeature.h"

class V2Cutout :
    public CutoutFeature
{
public:
    V2Cutout(OOGFeature *feature);
public:
    ~V2Cutout(void);
private:
    OOGFeature *myOOGFeature;
};