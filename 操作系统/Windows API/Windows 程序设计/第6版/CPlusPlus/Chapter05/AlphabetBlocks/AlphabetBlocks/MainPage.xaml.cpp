//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Block.xaml.h"

using namespace AlphabetBlocks;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

Color MainPage::colors[5] = { Colors::Red, Colors::Green, Colors::Orange, Colors::Blue, Colors::Purple };

MainPage::MainPage()
{
    InitializeComponent();
    srand(int(time(nullptr)));
    blockChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?-+*/%=";
}

void MainPage::OnGridSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    buttonCanvas->Children->Clear();

    double widthFraction = args->NewSize.Width / (args->NewSize.Width + args->NewSize.Height);
    int horzCount = int(widthFraction * blockChars->Length() / 2);
    int vertCount = int(blockChars->Length() / 2 - horzCount);
    int index = 0;
    double slotWidth = (args->NewSize.Width - BUTTON_SIZE) / horzCount;
    double slotHeight = (args->NewSize.Height - BUTTON_SIZE) / vertCount + 1;

    // Across top
    for (int i = 0; i < horzCount; i++)
    {
        Button^ button = MakeButton(index++);
        Canvas::SetLeft(button, i * slotWidth);
        Canvas::SetTop(button, 0);
        buttonCanvas->Children->Append(button);
    }

    // Down right side
    for (int i = 0; i < vertCount; i++)
    {
        Button^ button = MakeButton(index++);
        Canvas::SetLeft(button, this->ActualWidth - BUTTON_SIZE);
        Canvas::SetTop(button, i * slotHeight);
        buttonCanvas->Children->Append(button);
    }

    // Across bottom from right
    for (int i = 0; i < horzCount; i++)
    {
        Button^ button = MakeButton(index++);
        Canvas::SetLeft(button, this->ActualWidth - i * slotWidth - BUTTON_SIZE);
        Canvas::SetTop(button, this->ActualHeight - BUTTON_SIZE);
        buttonCanvas->Children->Append(button);
    }

    // Up left side
    for (int i = 0; i < vertCount; i++)
    {
        Button^ button = MakeButton(index++);
        Canvas::SetLeft(button, 0);
        Canvas::SetTop(button, this->ActualHeight - i * slotHeight - BUTTON_SIZE);
        buttonCanvas->Children->Append(button);
    }
}

Button^ MainPage::MakeButton(int index)
{
    Button^ button = ref new Button();
    button->Content = blockChars->Data()[index].ToString();
    button->Width = BUTTON_SIZE;
    button->Height = BUTTON_SIZE;
    button->FontSize = BUTTON_FONT;
    button->Tag = ref new SolidColorBrush(colors[index % (sizeof(colors) / sizeof(Color))]);
    button->Click += ref new RoutedEventHandler(this, &MainPage::OnButtonClick);

    return button;
}

void MainPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ button = dynamic_cast<Button^>(sender);

    Block^ block = ref new Block();
    block->Text = dynamic_cast<String^>(button->Content);
    block->Foreground = dynamic_cast<SolidColorBrush^>(button->Tag);
    Canvas::SetLeft(block, this->ActualWidth / 2 - 144.0 * rand() / RAND_MAX);
    Canvas::SetTop(block, this->ActualHeight / 2 - 144.0 * rand() / RAND_MAX);
    Canvas::SetZIndex(block, Block::ZIndex);
    blockcanvas->Children->Append(block);
}