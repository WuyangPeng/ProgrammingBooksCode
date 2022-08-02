//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SilasMarner;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();

    // Save and reload fraction read
    IPropertySet^ propertySet = ApplicationData::Current->LocalSettings->Values;
    fractionRead = propertySet->HasKey("FractionRead") ? (double)propertySet->Lookup("FractionRead") : 0;

    Application::Current->Suspending += ref new SuspendingEventHandler([this] (Object^ sender, SuspendingEventArgs^ args)
    {
        IPropertySet^ propertySet = ApplicationData::Current->LocalSettings->Values;
        propertySet->Insert("FractionRead", fractionRead);
    });
}

void MainPage::OnFlipViewSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    // First time through after program is launched
    if (flipView->Items->Size == 0)
    {
        task<IVector<String^>^> readLinesTask = create_task(PathIO::ReadLinesAsync("ms-appx:///Books/pg550.txt", 
                                                                                   UnicodeEncoding::Utf8));
        readLinesTask.then([this] (IVector<String^>^ bookLines)
        {
            // Get the size of the FlipView
            Size containerSize = Size(float(flipView->ActualWidth), float(flipView->ActualHeight));

            // Actual value gets modified during processing here, so save it
            double saveFractionRead = fractionRead;

            // CreateRichTextBlock
            RichTextBlock^ richTextBlock = ref new RichTextBlock();
            richTextBlock->FontSize = 22;
            richTextBlock->Foreground = ref new SolidColorBrush(Colors::Black);

            // Create paragraphs
            Paragraph^ paragraph = ref new Paragraph();
            paragraph->Margin = ThicknessHelper::FromUniformLength(12);
            richTextBlock->Blocks->Append(paragraph);

            for each (String^ line in bookLines)
            {
                // End of paragraph, make new Paragraph
                if (line->Length() == 0)
                {
                    paragraph = ref new Paragraph();
                    paragraph->Margin = ThicknessHelper::FromUniformLength(12);
                    richTextBlock->Blocks->Append(paragraph);
                }
                // Continue the paragraph
                else
                {
                    String^ textLine = line;
                    wchar_t lastChar = line->Data()[line->Length() - 1];

                    if (lastChar != ' ')
                        textLine += " ";

                    if (line->Data()[0] == ' ')
                        paragraph->Inlines->Append(ref new LineBreak());

                    Run^ run = ref new Run();
                    run->Text = textLine;
                    paragraph->Inlines->Append(run);
                }
            }

            // Make RichTextBlock the same size as the FlipView
            flipView->Items->Append(richTextBlock);
            richTextBlock->Measure(containerSize);

            // Generate RichTextBlockOverflow elements
            if (richTextBlock->HasOverflowContent)
            {
                // Add the first one
                RichTextBlockOverflow^ richTextBlockOverflow = ref new RichTextBlockOverflow();
                richTextBlock->OverflowContentTarget = richTextBlockOverflow;
                flipView->Items->Append(richTextBlockOverflow);
                richTextBlockOverflow->Measure(containerSize);

                // Add subsequent ones
                while (richTextBlockOverflow->HasOverflowContent)
                {
                    RichTextBlockOverflow^ newRichTextBlockOverflow = ref new RichTextBlockOverflow();
                    richTextBlockOverflow->OverflowContentTarget = newRichTextBlockOverflow;
                    richTextBlockOverflow = newRichTextBlockOverflow;
                    flipView->Items->Append(richTextBlockOverflow);
                    richTextBlockOverflow->Measure(containerSize);
                }
            }

            InitializeControls(saveFractionRead);
        });
    }

    // Subsequent SizeChanged events
    else
    {
        // Get the size of the FlipView
        Size containerSize = args->NewSize;

        // Actual value gets modified during processing here, so save it
        double saveFractionRead = fractionRead;

        // Resize all the items in the FlipView
        for each (Object^ obj in flipView->Items)
        {
            dynamic_cast<FrameworkElement^>(obj)->Measure(containerSize);
        }

        // Generate new RichTextBlockOverflow elements if needed
        while (dynamic_cast<RichTextBlockOverflow^>(flipView->Items->GetAt(flipView->Items->Size - 1))->HasOverflowContent)
        {
            RichTextBlockOverflow^ richTextBlockOverflow = dynamic_cast<RichTextBlockOverflow^>(flipView->Items->GetAt(flipView->Items->Size - 1));
            RichTextBlockOverflow^ newRichTextBlockOverflow = ref new RichTextBlockOverflow();
            richTextBlockOverflow->OverflowContentTarget = newRichTextBlockOverflow;
            richTextBlockOverflow = newRichTextBlockOverflow;
            flipView->Items->Append(richTextBlockOverflow);
            richTextBlockOverflow->Measure(args->NewSize);
        }

        // Remove superfluous RichTextBlockOverflow elements
        while (!dynamic_cast<RichTextBlockOverflow^>(flipView->Items->GetAt(flipView->Items->Size - 2))->HasOverflowContent)
        {
            flipView->Items->RemoveAt(flipView->Items->Size - 1);
        }

        InitializeControls(saveFractionRead);
    }
}

void MainPage::InitializeControls(double saveFractionRead)
{
    // Initialize the header and Slider
    int count = flipView->Items->Size;
    pageNumber->Text = "1";                 // probably modified soon
    pageCount->Text = count.ToString();
    pageSlider->Minimum = 1;
    pageSlider->Maximum = count;
    pageSlider->Value = 1;                  // probably modified soon

    // Go to approximate page
    fractionRead = saveFractionRead;
    flipView->SelectedIndex = int(min(count - 1, fractionRead * count));
}

void MainPage::OnFlipViewSelectionChanged(Object^ sender, SelectionChangedEventArgs^ args)
{
    int pageNum = flipView->SelectedIndex + 1;
    pageNumber->Text = pageNum.ToString();
    fractionRead = (pageNum - 1.0) / flipView->Items->Size;
    pageSlider->Value = pageNum;
}

void MainPage::OnPageSliderValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    flipView->SelectedIndex = min(int(flipView->Items->Size), int(args->NewValue)) - 1;
}


