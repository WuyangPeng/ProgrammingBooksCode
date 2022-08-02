//
// SecondPage.xaml.cpp
// Implementation of the SecondPage class
//

#include "pch.h"
#include "SecondPage.xaml.h"

using namespace SimplePageNavigation;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

SecondPage::SecondPage()
{
    InitializeComponent();
}

void SecondPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    forwardButton->IsEnabled = this->Frame->CanGoForward;
    backButton->IsEnabled = this->Frame->CanGoBack;
}

void SecondPage::OnGotoButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->Navigate(TypeName(MainPage::typeid));
}

void SecondPage::OnForwardButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->GoForward();
}

void SecondPage::OnBackButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->GoBack();
}

