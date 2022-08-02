//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RoutedEvents5;

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
    contentGrid->Background = GetRandomBrush();
}

void MainPage::OnTextBlockTapped(Object^ sender, TappedRoutedEventArgs^ args)
{
    TextBlock^ txtblk = dynamic_cast<TextBlock^>(sender);
    txtblk->Foreground = GetRandomBrush();
    args->Handled = true;
}

Brush^ MainPage::GetRandomBrush()
{
    unsigned char r = unsigned char((rand() % 256));
    unsigned char g = unsigned char((rand() % 256));
    unsigned char b = unsigned char((rand() % 256));
    Color clr = ColorHelper::FromArgb(255, r, g, b);
    return ref new SolidColorBrush(clr);
}


