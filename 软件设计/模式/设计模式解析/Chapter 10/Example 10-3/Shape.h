#pragma once
#include "Drawing.h"

class Shape
{
public:
    Shape(Drawing *aDrawing);
    virtual void draw()= 0;

protected:
    Drawing *myDrawing;
    void drawLine( double, double, double, double);
    void drawCircle( double, double, double);

public:
    ~Shape(void);
};