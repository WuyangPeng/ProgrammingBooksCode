#pragma once
#include "DisplayDriver.h"
#include "PrintDriver.h"
#include "ResFactory.h"

class ApControl
{
public:
    ApControl(void);
    void doPrint(void);
    void doDraw(void);
public:
    ~ApControl(void);
private:
    ResFactory *myResFactory;
    DisplayDriver *myDisplayDriver;
    PrintDriver *myPrintDriver;
};