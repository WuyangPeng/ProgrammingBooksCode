#pragma once
#include "Shape.h"
#include "XX_Circle.h"

class Circle : public Shape
{
public:
    Circle(XX_Circle *xxCircle);
    void display();
public:
    ~Circle(void);
private:
    XX_Circle *myXX_Circle;
};