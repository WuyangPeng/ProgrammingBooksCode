#pragma once

class CalcTax
{
public:
    CalcTax(void);
    double virtual taxAmount( long, double)= 0;
public:
    ~CalcTax(void);
};