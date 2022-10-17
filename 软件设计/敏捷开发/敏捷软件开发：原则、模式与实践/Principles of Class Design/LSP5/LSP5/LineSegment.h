#ifndef GEOMETRY_LINESEGMENT_H
#define GEOMETRY_LINESEGMENT_H

#include "Line.h"

class LineSegment : public Line
{
public:
    LineSegment(const Point& p1, const Point& p2);
    double GetLength() const;

    virtual bool IsOm(const Point&) const;
};

#endif