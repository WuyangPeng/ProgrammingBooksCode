#pragma once
#include "printdriver.h"

class HRPD : public PrintDriver
{
public:
    HRPD(void);
    void print(void);
public:
    ~HRPD(void);
};