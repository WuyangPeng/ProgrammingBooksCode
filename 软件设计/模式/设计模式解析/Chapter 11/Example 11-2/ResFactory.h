#pragma once
#include "DisplayDriver.h"
#include "PrintDriver.h"

class ResFactory
{
public:
    ResFactory(void);
    virtual DisplayDriver* getDispDrvr(void)=0;
    virtual PrintDriver* getPrtDrvr(void)=0;
    static ResFactory* getFactory(void);
public:
    ~ResFactory(void);
};