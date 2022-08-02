#pragma once

class Shape
{
public:
    Shape(void);
    virtual void draw()= 0;
public:
    ~Shape(void);
};