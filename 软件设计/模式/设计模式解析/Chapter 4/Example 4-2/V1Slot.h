#pragma once
#include "slotfeature.h"

class V1Slot :
    public SlotFeature
{
public:
    V1Slot(int, int);
    double getX1();
    double getX2();
public:
    ~V1Slot(void);
private:
    int myModelNumber;
    int myID;
};