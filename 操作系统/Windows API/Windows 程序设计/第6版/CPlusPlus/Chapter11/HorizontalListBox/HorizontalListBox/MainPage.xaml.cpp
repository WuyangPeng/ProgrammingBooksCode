//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace HorizontalListBox;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace PetzoldProgrammingWindows6Chapter11;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnItemLoaded(Object^ sender, RoutedEventArgs^ args)
{
    OutputDebugString(("Item Loaded: " +
        dynamic_cast<NamedColor^>(dynamic_cast<FrameworkElement^>(sender)->DataContext)->Name
            + "\r\n")->Data());
}
