#pragma once

class Point
{
    double x, y;
};

class Rectangle
{
public:
    virtual void SetWidth(double w)
    {
        itsWidth = w;
    }

    virtual void SetHeight(double h)
    {
        itsHeight = h;
    }

    double GetHeight() const
    {
        return itsHeight;
    }

    double GetWidth() const
    {
        return itsWidth;
    }

private:
    Point itsTopLeft;
    double itsWidth;
    double itsHeight;
};