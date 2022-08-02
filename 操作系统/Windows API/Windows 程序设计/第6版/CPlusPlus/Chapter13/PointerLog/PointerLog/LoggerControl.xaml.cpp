//
// LoggerControl.xaml.cpp
// Implementation of the LoggerControl class
//

#include "pch.h"
#include "LoggerControl.xaml.h"

using namespace PointerLog;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

LoggerControl::LoggerControl()
{
    InitializeComponent();
    pointerDictionary = ref new Map<unsigned int, PointerInfo^>();
}

void LoggerControl::OnPointerEntered(PointerRoutedEventArgs^ args)
{
    Log("Entered", args);
}

void LoggerControl::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    if (this->CaptureOnPress)
        CapturePointer(args->Pointer);

    Log("Pressed", args);
}

void LoggerControl::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    Log("Moved", args);
}

void LoggerControl::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    Log("Released", args);
}

void LoggerControl::OnPointerExited(PointerRoutedEventArgs^ args)
{
    Log("Exited", args);
}

void LoggerControl::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    Log("CaptureLost", args);
}

void LoggerControl::OnPointerCanceled(PointerRoutedEventArgs^ args)
{
    Log("Canceled", args);
}

void LoggerControl::OnPointerWheelChanged(PointerRoutedEventArgs^ args)
{
    Log("WheelChanged", args);
}

void LoggerControl::Log(String^ eventName, PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;
    PointerInfo^ pointerInfo;

    if (pointerDictionary->HasKey(id))
    {
        pointerInfo = pointerDictionary->Lookup(id);
    }
    else
    {
        // New ID, so new StackPanel and header
        TextBlock^ header = ref new TextBlock();
        header->Text = args->Pointer->PointerId.ToString() + " - " + args->Pointer->PointerDeviceType.ToString();
        header->FontWeight = FontWeights::Bold;
        StackPanel^ stackPanel = ref new StackPanel();
        stackPanel->Children->Append(header);

        // New PointerInfo for dictionary
        pointerInfo = ref new PointerInfo();
        pointerInfo->stackPanel = stackPanel;
        pointerDictionary->Insert(id, pointerInfo);

        // New column in the Grid for the StackPanel
        ColumnDefinition^ coldef = ref new ColumnDefinition();
        coldef->Width = GridLengthHelper::FromValueAndType(1, GridUnitType::Star);
        contentGrid->ColumnDefinitions->Append(coldef);
        Grid::SetColumn(stackPanel, contentGrid->ColumnDefinitions->Size - 1);
        contentGrid->Children->Append(stackPanel);
    }

    // Don't repeat PointerMoved and PointerWheelChanged events
    TextBlock^ txtblk = nullptr;

    if (eventName->Equals(pointerInfo->repeatEvent))
    {
        txtblk = pointerInfo->repeatTextBlock;
    }
    else
    {
        txtblk = ref new TextBlock();
        pointerInfo->stackPanel->Children->Append(txtblk);
    }

    txtblk->Text = eventName + " ";

    if (eventName == "WheelChanged")
    {
        txtblk->Text += args->GetCurrentPoint(this)->Properties->MouseWheelDelta.ToString();
    }
    else
    {
        Point position = args->GetCurrentPoint(this)->Position;
        txtblk->Text += position.X.ToString() + "," + position.Y.ToString();
    }

    txtblk->Text += args->Pointer->IsInContact ? " C" : "";
    txtblk->Text += args->Pointer->IsInRange ? " R" : "";

    if (eventName == "Moved" || eventName == "WheelChanged")
    {
        pointerInfo->repeatEvent = eventName;
        pointerInfo->repeatTextBlock = txtblk;
    }
    else
    {
        pointerInfo->repeatEvent = nullptr;
        pointerInfo->repeatTextBlock = nullptr;
    }
}

void LoggerControl::Clear()
{
    contentGrid->ColumnDefinitions->Clear();
    contentGrid->Children->Clear();
    pointerDictionary->Clear();
}

