#pragma once
#include "resfactory.h"
#include "LRDD.h"
#include "LRPD.h"

class LowResFact :     public ResFactory
{
public:
    LowResFact(void);
    DisplayDriver* getDispDrvr(void);
    PrintDriver* getPrtDrvr(void);
public:
    ~LowResFact(void);
};