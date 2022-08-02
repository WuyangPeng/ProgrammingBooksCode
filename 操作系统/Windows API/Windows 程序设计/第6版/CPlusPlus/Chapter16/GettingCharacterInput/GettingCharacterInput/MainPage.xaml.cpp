//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace GettingCharacterInput;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

MainPage::MainPage()
{
    InitializeComponent();
    Window::Current->CoreWindow->CharacterReceived += 
        ref new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &MainPage::OnCoreWindowCharacterReceived);
}

void MainPage::OnCoreWindowCharacterReceived(CoreWindow^ sender, CharacterReceivedEventArgs^ args)
{
    // Process Backspace key
    if (args->KeyCode == 8 && txtblk->Text->Length() > 0)
    {
        std::wstring str(txtblk->Text->Data());
        txtblk->Text = ref new String(str.substr(0, str.length() - 1).c_str());
    }
    // All other keys
    else
    {
        wchar_t str[2] = { args->KeyCode, 0 };
        txtblk->Text += ref new String(str);
    }
}

