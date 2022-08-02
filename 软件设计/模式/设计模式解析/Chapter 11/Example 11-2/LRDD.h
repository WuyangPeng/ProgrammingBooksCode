#pragma once
#include "displaydriver.h"

class LRDD :
    public DisplayDriver
{
public:
    LRDD(void);
    void draw(void);
public:
    ~LRDD(void);
};