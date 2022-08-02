#pragma once

#include "UniformGridBase.h"

namespace PetzoldProgrammingWindows6Chapter11
{
    public ref class DistributedUniformGrid sealed : UniformGridBase
    {
    public:
        DistributedUniformGrid();

    protected:
        virtual Windows::Foundation::Size ArrangeOverride(Windows::Foundation::Size finalSize) override;
    };
}