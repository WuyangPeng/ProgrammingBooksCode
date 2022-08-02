#pragma once

#include "IGeometrySegment.h"
#include "LineSegment.h"
#include "ArcSegment.h"

namespace PetzoldWindows8VectorDrawing
{
    public ref class RoundCappedPath sealed : IGeometrySegment
    {
    private:
        LineSegment^ lineSegment1;
        ArcSegment^ arcSegment1;
        LineSegment^ lineSegment2;
        ArcSegment^ arcSegment2;

    public:
        RoundCappedPath();
        void Set(Windows::Foundation::Point point1, Windows::Foundation::Point point2, float radius1, float radius2);
        virtual void GetAllX(float y, Windows::Foundation::Collections::IVector<float>^ xCollection);
    };
}