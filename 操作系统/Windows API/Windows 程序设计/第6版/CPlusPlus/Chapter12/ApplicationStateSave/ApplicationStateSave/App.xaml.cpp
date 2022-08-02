//
// App.xaml.cpp
// Implementation of the App class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ApplicationStateSave;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Application template is documented at http://go.microsoft.com/fwlink/?LinkId=234227

/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    InitializeComponent();
    Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used when the application is launched to open a specific file, to display
/// search results, and so forth.
/// </summary>
/// <param name="args">Details about the launch request and process.</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args)
{
    auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

    // Do not repeat app initialization when the Window already has content,
    // just ensure that the window is active
    if (rootFrame == nullptr)
    {
        // Create a Frame to act as the navigation context and associate it with
        // a SuspensionManager key
        rootFrame = ref new Frame();

        if (args->PreviousExecutionState == ApplicationExecutionState::Terminated)
        {
            // TODO: Restore the saved session state only when appropriate, scheduling the
            // final launch steps after the restore is complete

            // Code added for ApplicationStateSave project
            ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

            if (appData->Values->HasKey("NavigationState"))
                rootFrame->SetNavigationState(dynamic_cast<String^>(appData->Values->Lookup("NavigationState")));
        }

        if (rootFrame->Content == nullptr)
        {
            // When the navigation stack isn't restored navigate to the first page,
            // configuring the new page by passing required information as a navigation
            // parameter
            if (!rootFrame->Navigate(TypeName(MainPage::typeid), args->Arguments))
            {
                throw ref new FailureException("Failed to create initial page");
            }
        }
        // Place the frame in the current Window
        Window::Current->Content = rootFrame;
        // Ensure the current window is active
        Window::Current->Activate();
    }
    else
    {
        if (rootFrame->Content == nullptr)
        {
            // When the navigation stack isn't restored navigate to the first page,
            // configuring the new page by passing required information as a navigation
            // parameter
            if (!rootFrame->Navigate(TypeName(MainPage::typeid), args->Arguments))
            {
                throw ref new FailureException("Failed to create initial page");
            }
        }
        // Ensure the current window is active
        Window::Current->Activate();
    }

    // Code added for ApplicationStateSave project
    Window::Current->CoreWindow->Dispatcher->AcceleratorKeyActivated += ref new TypedEventHandler<CoreDispatcher^, AcceleratorKeyEventArgs^>(this, &App::OnAcceleratorKeyActivated);
    Window::Current->CoreWindow->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::OnPointerPressed);
}

void App::OnAcceleratorKeyActivated(CoreDispatcher^ sender, AcceleratorKeyEventArgs^ args)
{
    if ((args->EventType == CoreAcceleratorKeyEventType::SystemKeyDown ||
         args->EventType == CoreAcceleratorKeyEventType::KeyDown) &&
        (args->VirtualKey == VirtualKey::Left || 
         args->VirtualKey == VirtualKey::Right ||
         (int)args->VirtualKey == 166 || 
         (int)args->VirtualKey == 167))
    {
        CoreWindow^ window = Window::Current->CoreWindow;
        CoreVirtualKeyStates down = CoreVirtualKeyStates::Down;

        // Ignore key combinations where Shift or Ctrl is down
        if ((window->GetKeyState(VirtualKey::Shift) & down) == down ||
            (window->GetKeyState(VirtualKey::Control) & down) == down)
        {
            return;
        }

        // Get alt key state
        bool alt = (window->GetKeyState(VirtualKey::Menu) & down) == down;

        // Go back for Alt-Left key or browser left key
        if (args->VirtualKey == VirtualKey::Left && alt ||
            (int)args->VirtualKey == 166 && !alt)
        {
            GoBack();
            args->Handled = true;
        }

        // Go forward for Alt-Right key or browser right key
        if (args->VirtualKey == VirtualKey::Right && alt ||
            (int)args->VirtualKey == 167 && !alt)
        {
            GoForward();
            args->Handled = true;
        }
    }
}

void App::OnPointerPressed(CoreWindow^ sender, PointerEventArgs^ args)
{
    PointerPointProperties^ props = args->CurrentPoint->Properties;

     if (!props->IsLeftButtonPressed &&
         !props->IsMiddleButtonPressed &&
         !props->IsRightButtonPressed &&
         props->IsXButton1Pressed != props->IsXButton2Pressed)
     {
         if (props->IsXButton1Pressed)
             GoBack();
         else
             GoForward();

        args->Handled = true;
     } 
}

void App::GoBack()
{
    Frame^ frame = dynamic_cast<Frame^>(Window::Current->Content);

    if (frame != nullptr && frame->CanGoBack)
        frame->GoBack();
}

void App::GoForward()
{
    Frame^ frame = dynamic_cast<Frame^>(Window::Current->Content);

    if (frame != nullptr && frame->CanGoForward)
        frame->GoForward();
}

/// <summary>
/// Invoked when application execution is being suspended.  Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
    (void) sender;    // Unused parameter
    (void) e;    // Unused parameter

    //TODO: Save application state and stop any background activity

    // Code added for ApplicationStateSave project
    ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;
    appData->Values->Insert("NavigationState", dynamic_cast<Frame^>(Window::Current->Content)->GetNavigationState());
    // End of code added for ApplicationStateSave project
}
