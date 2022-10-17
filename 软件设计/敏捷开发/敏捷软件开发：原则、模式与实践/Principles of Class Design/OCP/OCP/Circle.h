#pragma once

#include "Shape.h"

struct Circle
{
    ShapeType itsType;
    double itsRadius;
    Point itsCenter;
};

void DrawCircle(Circle* s);