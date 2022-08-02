//
// JiggleButton.xaml.h
// Declaration of the JiggleButton class
//

#pragma once

#include "JiggleButton.g.h"

namespace JiggleButtonDemo
{
    public ref class JiggleButton sealed
    {
    public:
        JiggleButton();

    private:
        void OnJiggleButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
