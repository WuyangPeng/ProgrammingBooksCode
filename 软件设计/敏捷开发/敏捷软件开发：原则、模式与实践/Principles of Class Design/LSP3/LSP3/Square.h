#pragma once
#include "Rectangle.h"
class Square : public Rectangle
{
public:
    virtual void SetWidth(double w);

    virtual void SetHeight(double h);
};
