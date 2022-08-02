//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace BerniceBobsHerHair;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnRichTextBlockSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    RichTextBlock^ richTextBlock = dynamic_cast<RichTextBlock^>(sender);

    if (richTextBlock->ActualHeight == 0)
        return;

    // Get rid of all previous RichTextBlockOverflow objects
    while (stackPanel->Children->Size > 1)
        stackPanel->Children->RemoveAt(1);

    if (!richTextBlock->HasOverflowContent)
        return;

    // Create first RichTextBlockOverflow
    RichTextBlockOverflow^ richTextBlockOverflow = ref new RichTextBlockOverflow();
    richTextBlock->OverflowContentTarget = richTextBlockOverflow;
    stackPanel->Children->Append(richTextBlockOverflow);

    // Measure it
    richTextBlockOverflow->Measure(Size(float(richTextBlockOverflow->Width), 
                                        float(this->ActualHeight)));

    // if it has overflow content, repeat the process
    while (richTextBlockOverflow->HasOverflowContent)
    {
        RichTextBlockOverflow^ newRichTextBlockOverflow = ref new RichTextBlockOverflow();
        richTextBlockOverflow->OverflowContentTarget = newRichTextBlockOverflow;
        richTextBlockOverflow = newRichTextBlockOverflow;
        stackPanel->Children->Append(richTextBlockOverflow);
        richTextBlockOverflow->Measure(Size(float(richTextBlockOverflow->Width), 
                                            float(this->ActualHeight)));
    }
}
