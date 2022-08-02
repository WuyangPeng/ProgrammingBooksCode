
#include "pch.h"
#include "RudimentaryTextBoxPeer.h"

using namespace BetterCharacterInput;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Automation;
using namespace Windows::UI::Xaml::Automation::Peers;
using namespace Windows::UI::Xaml::Automation::Provider;

RudimentaryTextBoxPeer::RudimentaryTextBoxPeer(RudimentaryTextBox^ owner) : FrameworkElementAutomationPeer(owner)
{
    this->rudimentaryTextBox = owner;
}

Object^ RudimentaryTextBoxPeer::GetPatternCore(PatternInterface patternInterface)
{
    if (patternInterface == PatternInterface::Value || patternInterface == PatternInterface::Text)
    {
        return this;
    }
    return FrameworkElementAutomationPeer::GetPatternCore(patternInterface);
}
