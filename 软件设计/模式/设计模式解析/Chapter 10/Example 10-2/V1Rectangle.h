#pragma once
#include "Rectangle.h"

class V1Rectangle : public Rectangle
{
public:
    V1Rectangle(double, double, double, double);
    void drawLine( double, double, double, double);
public:
    ~V1Rectangle(void);
};