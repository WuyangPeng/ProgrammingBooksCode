#pragma once
#include "slotfeature.h"
#include "OOGFeature.h"

class V2Slot :
    public SlotFeature
{
public:
    V2Slot(OOGFeature *feature);
    double getX1();
    double getX2();
public:
    ~V2Slot(void);
private:
    OOGFeature *myOOGFeature;
};