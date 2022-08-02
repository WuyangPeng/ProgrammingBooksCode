//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "StudentPage.xaml.h"

namespace DisplayHighSchoolStudents
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void OnGridViewItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ args);
    };
}
