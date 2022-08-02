#pragma once

#include "IGeometrySegment.h"

namespace PetzoldWindows8VectorDrawing
{
    public ref class ArcSegment sealed : IGeometrySegment
    {
    private:
        Windows::Foundation::Point center, point1, point2;
        float radius, angle1, angle2;

    public:
        ArcSegment() {};
        void Set(Windows::Foundation::Point center, float radius, Windows::Foundation::Point point1, Windows::Foundation::Point point2);
        virtual void GetAllX(float y, Windows::Foundation::Collections::IVector<float>^ xCollection);

    private:
        void TryY(float y, float x, Windows::Foundation::Collections::IVector<float>^ xCollection);
    };
}