//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleKeypad;

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

MainPage::MainPage()
{
    InitializeComponent();
    inputString = L"";
}

void MainPage::OnCharButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ btn = dynamic_cast<Button^>(sender);
    inputString += dynamic_cast<String^>(btn->Content)->Data();
    FormatText();
}

void MainPage::OnDeleteButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    inputString = inputString.substr(0, inputString.length() - 1);
    FormatText();
}

void MainPage::FormatText()
{
    std::wstring formatted = inputString;
    bool hasNonNumbers = inputString.find_first_of(L"*#") != inputString.npos;
    
    if (hasNonNumbers || inputString.length() < 4 || inputString.length() > 10)
    {
    }
    else if (inputString.length() < 8)
    {
        formatted = inputString.substr(0, 3)
                        .append(L"-")
                        .append(inputString.substr(3, inputString.length() - 3));
    }
    else
    {
        formatted = std::wstring(L"(").append(inputString.substr(0, 3))
                        .append(L")")
                        .append(inputString.substr(3, 3))
                        .append(L"-")
                        .append(inputString.substr(6, inputString.length() - 6));
    }

    resultText->Text = ref new String(formatted.c_str());
    deleteButton->IsEnabled = formatted.length() > 0;
}

