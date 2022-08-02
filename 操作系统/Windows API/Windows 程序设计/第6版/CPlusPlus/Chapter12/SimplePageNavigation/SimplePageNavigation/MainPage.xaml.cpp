//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    forwardButton->IsEnabled = this->Frame->CanGoForward;
    backButton->IsEnabled = this->Frame->CanGoBack;
}

void MainPage::OnGotoButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->Navigate(TypeName(SecondPage::typeid));
}

void MainPage::OnForwardButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->GoForward();
}

void MainPage::OnBackButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    this->Frame->GoBack();
}



