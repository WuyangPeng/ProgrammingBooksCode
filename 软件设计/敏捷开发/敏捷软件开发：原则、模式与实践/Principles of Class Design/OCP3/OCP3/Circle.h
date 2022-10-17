#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
    virtual bool Precedes(const Shape&) const;
};


