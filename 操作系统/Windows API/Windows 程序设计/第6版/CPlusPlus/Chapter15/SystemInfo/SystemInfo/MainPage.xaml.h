//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SystemInfo
{
    public enum class ProcessorType
    {
        x86 = 0,
        ia64 = 6,
        x64 = 9,
        Unknown = 65535
    };

    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        Platform::String^ ToHexString(uint64 value);
    };
}
