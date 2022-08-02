#pragma once

#include "RudimentaryTextBox.xaml.h"

namespace BetterCharacterInput
{
    public ref class RudimentaryTextBoxPeer sealed : Windows::UI::Xaml::Automation::Peers::FrameworkElementAutomationPeer, 
                                                     Windows::UI::Xaml::Automation::Provider::ITextProvider, 
                                                     Windows::UI::Xaml::Automation::Provider::IValueProvider
    {
    private:
        RudimentaryTextBox^ rudimentaryTextBox;

    public:
        RudimentaryTextBoxPeer(RudimentaryTextBox^ owner);

    protected:
        virtual Platform::Object^ GetPatternCore(Windows::UI::Xaml::Automation::Peers::PatternInterface patternInterface) override;
         
    public:
        // Required for IValueProvider
        property Platform::String^ Value
        {
            virtual Platform::String^ get() { return rudimentaryTextBox->Text; }
        }

        property bool IsReadOnly
        {
            virtual bool get() { return false; }
        }

        virtual void SetValue(Platform::String^ value)
        {
            rudimentaryTextBox->Text = value;
        }

        // Required for ITextProvider
        property Windows::UI::Xaml::Automation::SupportedTextSelection SupportedTextSelection
        {
            virtual Windows::UI::Xaml::Automation::SupportedTextSelection get() { return Windows::UI::Xaml::Automation::SupportedTextSelection::None; }
        }

        property Windows::UI::Xaml::Automation::Provider::ITextRangeProvider^ DocumentRange
        {
            virtual Windows::UI::Xaml::Automation::Provider::ITextRangeProvider^ get() { return nullptr; }
        }

        virtual Windows::UI::Xaml::Automation::Provider::ITextRangeProvider^ RangeFromPoint(Windows::Foundation::Point screenLocation)
        {
            return nullptr;
        }

        virtual Windows::UI::Xaml::Automation::Provider::ITextRangeProvider^ RangeFromChild(Windows::UI::Xaml::Automation::Provider::IRawElementProviderSimple^ childElement)
        {
            return nullptr;
        }
        
        virtual Platform::Array<Windows::UI::Xaml::Automation::Provider::ITextRangeProvider^>^ GetVisibleRanges(void)
        {
            return nullptr;
        }
        
        virtual Platform::Array<Windows::UI::Xaml::Automation::Provider::ITextRangeProvider^>^ GetSelection(void)
        {
            return nullptr;
        }
    };
}