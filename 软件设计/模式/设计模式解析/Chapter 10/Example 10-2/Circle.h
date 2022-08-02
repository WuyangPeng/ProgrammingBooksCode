#pragma once
#include "Shape.h"

class Circle :
    public Shape
{
public:
    Circle(double, double, double);
    virtual void draw();
    virtual void drawCircle(double, double, double)=0;

public:
    ~Circle(void);
protected:
    double _x, _y, _r;
};