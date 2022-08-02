#pragma once

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Drawing.h"
#include "V1Drawing.h"
#include "V2Drawing.h"

class Factory
{
public:
    Factory(void);
    ~Factory(void);
    Shape** getShapes();
};