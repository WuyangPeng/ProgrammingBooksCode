#pragma once
#include "Shape.h"

class Square : public Shape
{
public:
    virtual bool Precedes(const Shape&) const;
};