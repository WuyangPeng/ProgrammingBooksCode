#pragma once
#include "Rectangle.h"

class V2Rectangle : public Rectangle
{
public:
    V2Rectangle(double, double, double, double);
    void drawLine( double, double, double, double);
public:
    ~V2Rectangle(void);
};