//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PrintPrintableArea;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Printing;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Printing;

MainPage::MainPage()
{
    InitializeComponent();

    // Element to print
    border = ref new Border();
    border->Background = ref new SolidColorBrush(Colors::Red);

    Border^ innerBorder = ref new Border();
    innerBorder->Background = ref new SolidColorBrush(Colors::White);
    innerBorder->BorderBrush = ref new SolidColorBrush(Colors::Black);
    innerBorder->BorderThickness = ThicknessHelper::FromUniformLength(1);
    border->Child = innerBorder;

    TextBlock^ txtblk = ref new TextBlock();
    txtblk->Text = "Print Printable Area";
    txtblk->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Times New Roman");
    txtblk->FontSize = 24;
    txtblk->Foreground = ref new SolidColorBrush(Colors::Black);
    txtblk->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Center;
    txtblk->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Center;
    innerBorder->Child = txtblk;

    // Create PrintDocument and attach handlers
    printDocument = ref new PrintDocument();
    printDocumentSource = printDocument->DocumentSource;
    printDocument->Paginate += ref new PaginateEventHandler(this, &MainPage::OnPrintDocumentPaginate);
    printDocument->GetPreviewPage += ref new GetPreviewPageEventHandler(this, &MainPage::OnPrintDocumentGetPreviewPage);
    printDocument->AddPages += ref new AddPagesEventHandler(this, &MainPage::OnPrintDocumentAddPages);
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    // Attach PrintManager handler
    PrintManager^ printManager = PrintManager::GetForCurrentView();
    printTaskRequestedEventToken = printManager->PrintTaskRequested += ref new TypedEventHandler<PrintManager^, PrintTaskRequestedEventArgs^>(this, &MainPage::OnPrintManagerPrintTaskRequested);
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ args)
{
    // Detach PrintManager handler
    PrintManager::GetForCurrentView()->PrintTaskRequested -= printTaskRequestedEventToken;
}

void MainPage::OnPrintManagerPrintTaskRequested(PrintManager^ sender, PrintTaskRequestedEventArgs^ args)
{
    args->Request->CreatePrintTask("Print Printable Area", ref new PrintTaskSourceRequestedHandler(
        [this](PrintTaskSourceRequestedArgs^ args)
        {
            args->SetSource(printDocumentSource);
        }));
}

void MainPage::OnPrintDocumentPaginate(Object^ sender, PaginateEventArgs^ args)
{
    PrintPageDescription printPageDescription = args->PrintTaskOptions->GetPageDescription(0);

    // Set Padding on outer Border
    double left = printPageDescription.ImageableRect.Left;
    double top = printPageDescription.ImageableRect.Top;
    double right = printPageDescription.PageSize.Width
                            - left - printPageDescription.ImageableRect.Width;
    double bottom = printPageDescription.PageSize.Height 
                            - top - printPageDescription.ImageableRect.Height;                    
    border->Padding = ThicknessHelper::FromLengths(left, top, right, bottom);

    printDocument->SetPreviewPageCount(1, PreviewPageCountType::Final);
}

void MainPage::OnPrintDocumentGetPreviewPage(Object^ sender, GetPreviewPageEventArgs^ args)
{
    printDocument->SetPreviewPage(args->PageNumber, border);
}

void MainPage::OnPrintDocumentAddPages(Object^ sender, AddPagesEventArgs^ args)
{
    printDocument->AddPage(border);
    printDocument->AddPagesComplete();
}
