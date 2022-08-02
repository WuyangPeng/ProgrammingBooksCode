#include "Circle.h"

Circle::Circle(XX_Circle *xxCircle)
{
    myXX_Circle = xxCircle;
}

Circle::~Circle(void)
{
    delete myXX_Circle;
}

void Circle::display()
{
    myXX_Circle->displayIt();
}
