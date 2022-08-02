#pragma once
#include "drawing.h"
#include "DP1.h"

class V1Drawing : public Drawing
{
public:
    V1Drawing(void);
public:
    ~V1Drawing(void);
    void drawLine( double, double, double, double);
    void drawCircle( double, double, double);
private:
    DP1 myDP1;
};
