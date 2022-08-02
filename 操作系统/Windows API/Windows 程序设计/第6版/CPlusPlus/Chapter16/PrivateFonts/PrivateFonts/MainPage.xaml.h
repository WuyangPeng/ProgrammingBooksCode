//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace PrivateFonts
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        Concurrency::task<void> TransferFontFile(Windows::Storage::StorageFolder^ fontsFolder, Platform::String^ filename);
    };
}
