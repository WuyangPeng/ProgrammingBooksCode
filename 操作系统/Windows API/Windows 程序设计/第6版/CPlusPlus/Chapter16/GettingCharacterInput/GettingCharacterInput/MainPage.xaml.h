//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace GettingCharacterInput
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnCoreWindowCharacterReceived(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CharacterReceivedEventArgs^ args);
    };
}
