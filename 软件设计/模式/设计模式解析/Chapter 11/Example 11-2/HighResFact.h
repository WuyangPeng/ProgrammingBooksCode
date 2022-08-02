#pragma once
#include "resfactory.h"
#include "HRDD.h"
#include "HRPD.h"

class HighResFact : public ResFactory
{
public:
    HighResFact(void);
    DisplayDriver* getDispDrvr(void);
    PrintDriver* getPrtDrvr(void);
public:
    ~HighResFact(void);
};