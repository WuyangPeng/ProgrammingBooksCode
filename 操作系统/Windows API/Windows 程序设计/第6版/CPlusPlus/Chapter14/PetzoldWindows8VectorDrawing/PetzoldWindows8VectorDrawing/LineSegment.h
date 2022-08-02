#pragma once

#include "IGeometrySegment.h"

namespace PetzoldWindows8VectorDrawing
{
    public ref class LineSegment sealed : IGeometrySegment
    {
    private:
        Windows::Foundation::Point point1, point2;
        float a, b;                                // as in x = ay + b

    public:
        LineSegment() {}
        void Set(Windows::Foundation::Point point1, Windows::Foundation::Point point2);
        virtual void GetAllX(float y, Windows::Foundation::Collections::IVector<float>^ xCollection);
    };
}