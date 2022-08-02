#include "pch.h"
#include "App.h"

using namespace StrippedDownHello;
using namespace Platform;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;

int main(Array<String^>^ args)
{
    Application::Start(ref new ApplicationInitializationCallback([](ApplicationInitializationCallbackParams^ params) 
    {
        StrippedDownHello::App^ app = ref new App();
    }));
}

void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ pArgs)
{
    TextBlock^ txtblk = ref new TextBlock();
    txtblk->Text = "Stripped-Down Windows 8";
    txtblk->FontFamily = ref new FontFamily("Lucida sans Typewriter");
    txtblk->FontSize = 96;
    txtblk->Foreground = ref new SolidColorBrush(Colors::Red);
    txtblk->HorizontalAlignment = HorizontalAlignment::Center;
    txtblk->VerticalAlignment = VerticalAlignment::Center;

    Window::Current->Content = txtblk;
    Window::Current->Activate();
}
