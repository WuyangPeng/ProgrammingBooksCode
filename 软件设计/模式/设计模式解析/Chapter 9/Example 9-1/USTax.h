#pragma once
#include "calctax.h"

class USTax :
    public CalcTax
{
public:
    USTax(void);
    double taxAmount( long, double);

public:
    ~USTax(void);
};