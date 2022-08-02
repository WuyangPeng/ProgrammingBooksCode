#pragma once
#include "cutoutfeature.h"

class V1Cutout :
    public CutoutFeature
{
public:
    V1Cutout(int, int);
public:
    ~V1Cutout(void);
private:
    int myModelNumber;
    int myID;
};