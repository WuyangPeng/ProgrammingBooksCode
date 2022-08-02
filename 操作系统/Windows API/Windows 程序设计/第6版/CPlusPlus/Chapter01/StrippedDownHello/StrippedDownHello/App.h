#pragma once

#include "pch.h"

namespace StrippedDownHello
{
    ref class App sealed : public Windows::UI::Xaml::Application
    {
    public:
        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ pArgs) override;
    };
}
