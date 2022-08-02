//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint;

using namespace Concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI;
using namespace Windows::UI::ApplicationSettings;
using namespace Windows::UI::Input;
using namespace Windows::UI::Popups;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace PetzoldWindows8VectorDrawing;

MainPage::MainPage()
{
    InitializeComponent();

    appSettings = ref new AppSettings();
    imageScale = 1;
    imageOffset = Point(0, 0);

    pointerDictionary = ref new Map<unsigned int, PointerInfo^>();

    roundCappedLine = ref new RoundCappedLine();
    roundCappedPath = ref new RoundCappedPath();
    xCollection = ref new Vector<float>();

    SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnMainPageSizeChanged);
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
    Application::Current->Suspending += ref new SuspendingEventHandler(this, &MainPage::OnApplicationSuspending);

    // Install a handler for the Settings pane
    SettingsPane^ settingsPane = SettingsPane::GetForCurrentView();
    settingsPane->CommandsRequested += 
        ref new TypedEventHandler<SettingsPane^, SettingsPaneCommandsRequestedEventArgs^>(this, &MainPage::OnSettingsPaneCommandsRequested);

    // Initialize sharing
    InitializeSharing();

    // Create a PrintDocument derivative for handling printing
    bitmapPrintDocument = ref new BitmapPrintDocument(ref new GetBitmap([this] () { return bitmap; }));
}

void MainPage::OnSettingsPaneCommandsRequested(SettingsPane^ sender,
                                               SettingsPaneCommandsRequestedEventArgs^ args)
{
    SettingsCommand^ aboutCommand = ref new SettingsCommand("0", "About", 
                        ref new UICommandInvokedHandler(this, &MainPage::OnAboutInvoked));
    args->Request->ApplicationCommands->Append(aboutCommand);
}

void MainPage::OnAboutInvoked(IUICommand^ command)
{
    AboutBox^ aboutBox = ref new AboutBox();
    aboutBox->Height = this->ActualHeight;

    Popup^ popup = ref new Popup();
    popup->IsLightDismissEnabled = true;
    popup->Child = aboutBox;
    popup->IsOpen = true;
    popup->HorizontalOffset = this->ActualWidth - aboutBox->Width;
}

void MainPage::OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args)
{
    VisualStateManager::GoToState(this, ApplicationView::Value.ToString(), true);

    if (bitmap != nullptr)
    {
        CalculateImageScaleAndOffset();
    }
}

void MainPage::CalculateImageScaleAndOffset()
{
    imageScale = (float)min(this->ActualWidth / bitmap->PixelWidth,
                            this->ActualHeight / bitmap->PixelHeight);

    imageOffset = Point(float(this->ActualWidth - imageScale * bitmap->PixelWidth) / 2,
                        float(this->ActualHeight - imageScale * bitmap->PixelHeight) / 2);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    task<void> loadBitmapTask = create_task(LoadBitmapFromFile());
    loadBitmapTask.then([this] (task<void> thisTask)
    {
        try
        {
            thisTask.get();
        }
        catch (Exception^)
        {
            // Ignore any errors
        }
        if (bitmap == nullptr)
        {
            CreateNewBitmapAndPixelArray();
        }
    });
}

void MainPage::OnApplicationSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    // Save application settings
    appSettings->Save();

    SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

    // Save current bitmap
    task<void> saveBitmapTask = create_task(SaveBitmapToFile());
    saveBitmapTask.then([deferral] (task<void> thisTask)
    {
        try
        {
            thisTask.get();
        }
        catch (Exception^)
        {
            // Ignore any errors
        }
        deferral->Complete();
    });
}

void MainPage::OnColorAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    DisplayDialog(sender, ref new ColorSettingDialog());
}

void MainPage::OnThicknessAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    DisplayDialog(sender, ref new ThicknessSettingDialog());
}

void MainPage::DisplayDialog(Object^ sender, FrameworkElement^ dialog)
{
    Button^ btn = dynamic_cast<Button^>(sender);

    dialog->DataContext = appSettings;

    Popup^ popup = ref new Popup();
    popup->Child = dialog;
    popup->IsLightDismissEnabled = true;

    dialog->SizeChanged += ref new SizeChangedEventHandler([this, popup, btn] (Object^, SizeChangedEventArgs^ args)
    {
        Size dialogSize = args->NewSize;

        // Get Button location relative to screen
        Point pt = btn->TransformToVisual(nullptr)->TransformPoint(Point(float(btn->ActualWidth) / 2,
                                                                         float(btn->ActualHeight) / 2));
        popup->HorizontalOffset = max(24, pt.X - dialogSize.Width);

        if (popup->HorizontalOffset + dialogSize.Width > this->ActualWidth)
            popup->HorizontalOffset = this->ActualWidth - dialogSize.Width;

        popup->HorizontalOffset = max(0, popup->HorizontalOffset);

        popup->VerticalOffset = this->ActualHeight - dialogSize.Height - this->BottomAppBar->ActualHeight - 24;
    });

    popup->Closed += ref new EventHandler<Object^>([this] (Object^, Object^)
    {
        this->BottomAppBar->IsOpen = false;
    });

    popup->IsOpen = true;
}

