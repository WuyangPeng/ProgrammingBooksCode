#pragma once
#include "drawing.h"
#include "DP2.h"

class V2Drawing : public Drawing
{
public:
    V2Drawing(void);
public:
    ~V2Drawing(void);
    void drawLine( double, double, double, double);
    void drawCircle( double, double, double);
private:
    DP2 myDP2;
};