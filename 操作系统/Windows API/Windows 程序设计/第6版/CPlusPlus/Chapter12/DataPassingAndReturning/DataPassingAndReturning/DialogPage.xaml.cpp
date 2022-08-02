//
// DialogPage.xaml.cpp
// Implementation of the DialogPage class
//

#include "pch.h"
#include "DialogPage.xaml.h"

using namespace DataPassingAndReturning;

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

DialogPage::DialogPage()
{
    InitializeComponent();
}

void DialogPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    // Get the object passed as the second argument to Navigate
    PassData^ passData = dynamic_cast<PassData^>(args->Parameter);
    Color clr1 = passData->InitializeColor;

    // Use that to initialize the RadioButton controls
    for each (UIElement^ child in radioStack->Children)
    {
        RadioButton^ radioButton = dynamic_cast<RadioButton^>(child);
        Color clr2 = (Color)radioButton->Tag;
        radioButton->IsChecked = 
            (clr1.A == clr2.A && clr1.R == clr2.R && clr1.G == clr2.G && clr1.B == clr2.B);
    }
}

void DialogPage::OnNavigatedFrom(NavigationEventArgs^ args)
{
    // Create ReturnData object
    ReturnData^ returnData = ref new ReturnData();

    // Set the ReturnColor property from the RadioButton controls
    for each (UIElement^ child in radioStack->Children)
    {
        RadioButton^ radioButton = dynamic_cast<RadioButton^>(child);
        if (radioButton->IsChecked->Value)
            returnData->ReturnColor = (Color)radioButton->Tag;
    }

    // Fire the Completed event
    Completed(this, returnData);
}

void DialogPage::OnReturnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->GoBack();
}
