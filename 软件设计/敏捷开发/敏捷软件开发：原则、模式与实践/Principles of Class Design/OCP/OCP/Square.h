#pragma once
#include "Shape.h"

struct Square
{
    ShapeType itsType;
    double itsSide;
    Point itsTopLeft;
};

void DrawSquare(Square* s);