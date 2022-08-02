//
// RudimentaryTextBox.xaml.cpp
// Implementation of the RudimentaryTextBox class
//

#include "pch.h"
#include "RudimentaryTextBox.xaml.h"
#include "RudimentaryTextBoxPeer.h"

using namespace BetterCharacterInput;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Automation::Peers;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

RudimentaryTextBox::RudimentaryTextBox()
{
    InitializeComponent();
    this->IsTabStop = true;
    this->Text = "";
}

void RudimentaryTextBox::OnTapped(TappedRoutedEventArgs^ args)
{
    this->Focus(Windows::UI::Xaml::FocusState::Programmatic);
}
            
void RudimentaryTextBox::OnGotFocus(RoutedEventArgs^ args)
{
    characterReceivedToken = Window::Current->CoreWindow->CharacterReceived += 
        ref new TypedEventHandler<CoreWindow^, 
                                  CharacterReceivedEventArgs^>(this, &RudimentaryTextBox::OnCoreWindowCharacterReceived);
}

void RudimentaryTextBox::OnLostFocus(Windows::UI::Xaml::RoutedEventArgs^ args)
{
    Window::Current->CoreWindow->CharacterReceived -= characterReceivedToken;
}

AutomationPeer^ RudimentaryTextBox::OnCreateAutomationPeer()
{
    return ref new RudimentaryTextBoxPeer(this);
}

void RudimentaryTextBox::OnCoreWindowCharacterReceived(CoreWindow^ sender, CharacterReceivedEventArgs^ args)
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

