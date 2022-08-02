#pragma once
#include "CalcTax.h"

class TaskController
{
public:
    TaskController(void);
    void process();
    CalcTax *getTaxRulesForCountry();
public:
    ~TaskController(void);
};