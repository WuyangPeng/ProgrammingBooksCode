#pragma once
#include "Circle.h"

class V2Circle : public Circle
{
public:
    V2Circle(double, double, double);
    void drawCircle( double, double, double);
public:
    ~V2Circle(void);
};