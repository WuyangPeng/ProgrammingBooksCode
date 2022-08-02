#include "pch.h"
#include "LineSegment.h"

using namespace PetzoldWindows8VectorDrawing;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

void LineSegment::Set(Point point1, Point point2)
{
    this->point1 = point1;
    this->point2 = point2;

    a = (point2.X - point1.X) / (point2.Y - point1.Y);
    b = point1.X - a * point1.Y;
}

void LineSegment::GetAllX(float y, IVector<float>^ xCollection)
{
    if ((point2.Y > point1.Y && y >= point1.Y && y < point2.Y) ||
        (point2.Y < point1.Y && y <= point1.Y && y > point2.Y))
    {
        xCollection->Append(a * y + b);
    }
}
