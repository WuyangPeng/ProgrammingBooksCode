//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ApplicationStateSave;

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
    // Enable buttons
    forwardButton->IsEnabled = this->Frame->CanGoForward;
    backButton->IsEnabled = this->Frame->CanGoBack;

    // Construct a dictionary key
    int pageKey = this->Frame->BackStackDepth;

    if (args->NavigationMode != NavigationMode::New)
    {
        // Get the page state dictionary for this page
        this->PageState = SaveStatePage::Pages->Lookup(pageKey);

        // Get the page state from the dictionary
        txtbox->Text = dynamic_cast<String^>(this->PageState->Lookup("TextBoxText"));
    }

    SaveStatePage::OnNavigatedTo(args);
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ args)
{
    this->PageState->Clear();

    // Save the page state in the dictionary
    this->PageState->Insert("TextBoxText", txtbox->Text);
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



