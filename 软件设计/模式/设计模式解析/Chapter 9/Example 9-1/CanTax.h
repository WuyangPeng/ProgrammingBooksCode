#pragma once
#include "calctax.h"

class CanTax :
    public CalcTax
{
public:
    CanTax(void);
    double taxAmount( long, double);
public:
    ~CanTax(void);
};