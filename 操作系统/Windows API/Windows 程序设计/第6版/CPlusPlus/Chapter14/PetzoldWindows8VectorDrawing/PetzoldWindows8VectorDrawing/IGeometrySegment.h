#pragma once

namespace PetzoldWindows8VectorDrawing
{
    public interface class IGeometrySegment
    {
        void GetAllX(float y, Windows::Foundation::Collections::IVector<float>^ xCollection);
    };
}
