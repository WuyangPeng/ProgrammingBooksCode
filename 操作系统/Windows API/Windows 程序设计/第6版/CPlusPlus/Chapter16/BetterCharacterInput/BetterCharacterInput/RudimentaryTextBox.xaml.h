//
// RudimentaryTextBox.xaml.h
// Declaration of the RudimentaryTextBox class
//

#pragma once

#include "RudimentaryTextBox.g.h"

namespace BetterCharacterInput
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class RudimentaryTextBox sealed
    {
    private:
        Windows::Foundation::EventRegistrationToken characterReceivedToken;

    public:
        RudimentaryTextBox();
        property Platform::String^ Text;

    protected:
        virtual void OnTapped(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args) override;
        virtual void OnGotFocus(Windows::UI::Xaml::RoutedEventArgs^ args) override;
        virtual void OnLostFocus(Windows::UI::Xaml::RoutedEventArgs^ args) override;
        virtual Windows::UI::Xaml::Automation::Peers::AutomationPeer^ OnCreateAutomationPeer() override;

    private:
        void OnCoreWindowCharacterReceived(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CharacterReceivedEventArgs^ args);
    };
}
