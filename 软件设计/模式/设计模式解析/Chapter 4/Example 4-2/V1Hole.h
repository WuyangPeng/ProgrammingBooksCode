#pragma once
#include "holefeature.h"

class V1Hole :
    public HoleFeature
{
public:
    V1Hole(int, int);
    double getX(); 
    
public:
    ~V1Hole(void);
private:
    int myModelNumber;
    int myID;
};