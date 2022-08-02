//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
    this->NavigationCacheMode = Windows::UI::Xaml::Navigation::NavigationCacheMode::Enabled;
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    // Nothing to do here for this program
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ args)
{
    if (args->SourcePageType.Name == DialogPage::typeid->FullName)
        completedEventToken = dynamic_cast<DialogPage^>(args->Content)->Completed += 
                    ref new EventHandler<ReturnData^>(this, &MainPage::OnDialogPageCompleted);
}

void MainPage::OnGotoButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    // Create PassData object
    PassData^ passData = ref new PassData();

    // Set the InitializeColor property from the RadioButton controls
    for each (UIElement^ child in radioStack->Children)
    {
        RadioButton^ radioButton = dynamic_cast<RadioButton^>(child);
        if (radioButton->IsChecked->Value)
            passData->InitializeColor = (Color)radioButton->Tag;
    }

    // Pass that object to Navigate
    this->Frame->Navigate(TypeName(DialogPage::typeid), passData);
}

void MainPage::OnDialogPageCompleted(Object^ sender, ReturnData^ args)
{
    // Set background from returned color
    Color clr1 = args->ReturnColor;
    contentGrid->Background = ref new SolidColorBrush(clr1);

    // Set RadioButon for returned color
    for each (UIElement^ child in radioStack->Children)
    {
        RadioButton^ radioButton = dynamic_cast<RadioButton^>(child);
        Color clr2 = (Color)radioButton->Tag;
        radioButton->IsChecked = 
            (clr1.A == clr2.A && clr1.R == clr2.R && clr1.G == clr2.G && clr1.B == clr2.B);

        dynamic_cast<DialogPage^>(sender)->Completed -= completedEventToken;
    }
}
