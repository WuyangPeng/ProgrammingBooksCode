#ifndef GEOMETRY_LINESEGMENT_H
#define GEOMETRY_LINESEGMENT_H

#include "geometry/LinearObject.h"

class LineSegment : public LinearObject
{
public:
    LineSegment(const Point& p1, const Point& p2);
    double GetLength() const;

    virtual bool IsOm(const Point&) const;
};

#endif