#pragma once
#include "CalcTax.h"

class SalesOrder
{
public:
    SalesOrder(void);
    void process (CalcTax *TaxToUse);
public:
    ~SalesOrder(void);
};