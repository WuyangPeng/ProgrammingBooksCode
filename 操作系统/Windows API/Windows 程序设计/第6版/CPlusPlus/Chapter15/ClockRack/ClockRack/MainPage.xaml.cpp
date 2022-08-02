//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "TimeZoneClock.xaml.h"
#include "TimeZoneClockViewModel.h"

using namespace ClockRack;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization;
using namespace Windows::Storage;
using namespace Windows::UI::Popups;
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
    timeZoneManager = ref new TimeZoneManager();
    appSettings = ApplicationData::Current->LocalSettings->Values;
    calendar = ref new Calendar();

    // Load application settings for clocks
    int index = 0;

    while (appSettings->HasKey(index.ToString() + "Location"))
    {
        String^ preface = index.ToString();

        TimeZoneClockViewModel^ viewModel = ref new TimeZoneClockViewModel();
        viewModel->Location = dynamic_cast<String^>(appSettings->Lookup(preface + "Location"));
        viewModel->TimeZoneKey = dynamic_cast<String^>(appSettings->Lookup(preface + "TimeZoneKey"));
        viewModel->ForegroundName = dynamic_cast<String^>(appSettings->Lookup(preface + "Foreground"));
        viewModel->BackgroundName = dynamic_cast<String^>(appSettings->Lookup(preface + "Background"));

        TimeZoneClock^ clock = ref new TimeZoneClock();
        clock->DataContext = viewModel;
        uniformGrid->Children->Append(clock);
        index += 1;
    }

    // If there are no settings, make a default Clock
    if (uniformGrid->Children->Size == 0)
    {
        TimeZoneClock^ clock = ref new TimeZoneClock();
        clock->DataContext = ref new TimeZoneClockViewModel();
        uniformGrid->Children->Append(clock);
    }

    // Set the Suspending handler
    Application::Current->Suspending += ref new SuspendingEventHandler(this, &MainPage::OnApplicationSuspending);

    // Start the Rendering event
    CompositionTarget::Rendering += ref new EventHandler<Object^>(this, &MainPage::OnCompositionTargetRendering);
}

void MainPage::OnApplicationSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    appSettings->Clear();

    for (unsigned int index = 0; index < uniformGrid->Children->Size; index++)
    {
        TimeZoneClock^ timeZoneClock = dynamic_cast<TimeZoneClock^>(uniformGrid->Children->GetAt(index));
        TimeZoneClockViewModel^ viewModel = dynamic_cast<TimeZoneClockViewModel^>(timeZoneClock->DataContext);
        String^ preface = index.ToString();

        appSettings->Insert(preface + "Location", viewModel->Location);
        appSettings->Insert(preface + "TimeZoneKey", viewModel->TimeZoneKey);
        appSettings->Insert(preface + "Foreground", viewModel->ForegroundName);
        appSettings->Insert(preface + "Background", viewModel->BackgroundName);
    }
}

void MainPage::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    for (unsigned int i = 0; i < uniformGrid->Children->Size; i++)
    {
        TimeZoneClockViewModel^ viewModel = dynamic_cast<TimeZoneClockViewModel^>(dynamic_cast<FrameworkElement^>(uniformGrid->Children->GetAt(i))->DataContext);
        String^ timeZoneKey = viewModel->TimeZoneKey;
        viewModel->DateTime = timeZoneManager->GetLocalTime(timeZoneKey);
    }
}

void MainPage::OnRightTapped(RightTappedRoutedEventArgs^ args)
{
    // Check if the parent of the clocked element is a TimeZoneClock
    FrameworkElement^ element = dynamic_cast<FrameworkElement^>(args->OriginalSource);
    TypeName clockType = { TimeZoneClock::typeid->FullName, TypeKind::Metadata };

    while (element != nullptr)
    {
        TypeName elementType = element->GetType();

        if (elementType.Name->Equals(clockType.Name))
            break;

        element = dynamic_cast<FrameworkElement^>(element->Parent);
    }

    if (element == nullptr)
        return;

    // Create a PopupMenu
    PopupMenu^ popupMenu = ref new PopupMenu();
    popupMenu->Commands->Append(ref new UICommand("Add...", ref new UICommandInvokedHandler(this, &MainPage::OnAddMenuItem), element));
    popupMenu->Commands->Append(ref new UICommand("Edit...", ref new UICommandInvokedHandler(this, &MainPage::OnEditMenuItem), element));

    if (uniformGrid->Children->Size > 1)
        popupMenu->Commands->Append(ref new UICommand("Delete...", ref new UICommandInvokedHandler(this, &MainPage::OnDeleteMenuItem), element));

    args->Handled = true;

    // Display the menu
    popupMenu->ShowAsync(args->GetPosition(this));
}

void MainPage::OnAddMenuItem(IUICommand^ command)
{
    TimeZoneClock^ timeZoneClock = ref new TimeZoneClock();
    timeZoneClock->DataContext = ref new TimeZoneClockViewModel();

    // Insert after the tapped clock
    TimeZoneClock^ clickedClock = dynamic_cast<TimeZoneClock^>(command->Id);
    unsigned int index = 0;
    uniformGrid->Children->IndexOf(clickedClock, &index);
    uniformGrid->Children->InsertAt(index + 1, timeZoneClock);
}

void MainPage::OnEditMenuItem(IUICommand^ command)
{
    TimeZoneClock^ timeZoneClock = dynamic_cast<TimeZoneClock^>(command->Id);
    SettingsDialog^ settingsDialog = ref new SettingsDialog(timeZoneManager);
    TimeZoneClockViewModel^ viewModel = dynamic_cast<TimeZoneClockViewModel^>(timeZoneClock->DataContext);
    settingsDialog->DataContext = viewModel;

    // Create Popup with SettingsDialog child
    Popup^ popup = ref new Popup();
    popup->Child = settingsDialog;
    popup->IsLightDismissEnabled = true;

    settingsDialog->SizeChanged += ref new SizeChangedEventHandler([this, settingsDialog, timeZoneClock, popup](Object^ sender, SizeChangedEventArgs^ args)
    {
        // Get clock center
        Point position = Point((float)timeZoneClock->ActualWidth / 2, (float)timeZoneClock->ActualHeight / 2);

        // Convert to page coordinates
        position = timeZoneClock->TransformToVisual(this)->TransformPoint(position);

        // Position popup so lower-left or lower-right corner
        //      aligns with center of edited clock
        if (position.X > this->ActualWidth / 2)
            position.X -= (float)settingsDialog->ActualWidth;

        position.Y -= (float)settingsDialog->ActualHeight;

        // Adjust for size of page
        if (position.X + settingsDialog->ActualWidth > this->ActualWidth)
            position.X = (float)(this->ActualWidth - settingsDialog->ActualWidth);

        if (position.X < 0)
            position.X = 0;

        if (position.Y < 0)
            position.Y = 0;

        // Set the popup position
        popup->HorizontalOffset = position.X;
        popup->VerticalOffset = position.Y;
    });
    popup->IsOpen = true;
}

void MainPage::OnDeleteMenuItem(IUICommand^ command)
{
    TimeZoneClock^ timeZoneClock = dynamic_cast<TimeZoneClock^>(command->Id);
    TimeZoneClockViewModel^ viewModel = dynamic_cast<TimeZoneClockViewModel^>(timeZoneClock->DataContext);

    MessageDialog^ msgdlg = ref new MessageDialog("Delete clock from collection?", viewModel->Location);
    msgdlg->Commands->Append(ref new UICommand("OK"));
    msgdlg->Commands->Append(ref new UICommand("Cancel"));
    msgdlg->DefaultCommandIndex = 0;
    msgdlg->CancelCommandIndex = 1;

    task<IUICommand^> showTask(msgdlg->ShowAsync());
    showTask.then([this, command](IUICommand^ msgDlgCommand)
    {
        if (msgDlgCommand->Label->Equals("OK"))
        {
            unsigned int index;
            uniformGrid->Children->IndexOf(dynamic_cast<TimeZoneClock^>(command->Id), &index);
            uniformGrid->Children->RemoveAt(index);
        }
    });
}
