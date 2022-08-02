//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace PathMarkupSyntaxCode
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        Windows::UI::Xaml::Media::Geometry^ PathMarkupToGeometry(Platform::String^ pathMarkup);
    };
}
