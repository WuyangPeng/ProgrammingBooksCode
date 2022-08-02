#pragma once
#include "displaydriver.h"

class HRDD : public DisplayDriver
{
public:
    HRDD(void);
    void draw(void);
public:
    ~HRDD(void);
};