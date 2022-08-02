//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RoutedEvents7;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
    srand(int(time(NULL)));
}

void MainPage::OnTapped(TappedRoutedEventArgs^ args)
{
    unsigned char r = unsigned char((rand() % 256));
    unsigned char g = unsigned char((rand() % 256));
    unsigned char b = unsigned char((rand() % 256));
    Color clr = ColorHelper::FromArgb(255, r, g, b);
    SolidColorBrush^ brush = ref new SolidColorBrush(clr);

    TextBlock^ txtblk = dynamic_cast<TextBlock^>(args->OriginalSource);
    if (txtblk != nullptr)
        txtblk->Foreground = brush;

    Grid^ grid = dynamic_cast<Grid^>(args->OriginalSource);
    if (grid != nullptr)
        grid->Background = brush;
}
