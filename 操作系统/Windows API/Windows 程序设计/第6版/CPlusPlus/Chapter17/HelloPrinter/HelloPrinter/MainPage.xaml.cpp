//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace HelloPrinter;

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

    // UIElement to print
    txtblk = ref new TextBlock();
    txtblk->Text = "Hello, Printer!";
    txtblk->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily("Times New Roman");
    txtblk->FontSize = 48;
    txtblk->Foreground = ref new SolidColorBrush(Colors::Black);

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
    args->Request->CreatePrintTask("Hello Printer", 
                                   ref new PrintTaskSourceRequestedHandler(this, &MainPage::OnPrintTaskSourceRequested));
}

void MainPage::OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs^ args)
{
    args->SetSource(printDocumentSource);
}

void MainPage::OnPrintDocumentPaginate(Object^ sender, PaginateEventArgs^ args)
{
    printDocument->SetPreviewPageCount(1, PreviewPageCountType::Final);
}

void MainPage::OnPrintDocumentGetPreviewPage(Object^ sender, GetPreviewPageEventArgs^ args)
{
    printDocument->SetPreviewPage(args->PageNumber, txtblk);
}

void MainPage::OnPrintDocumentAddPages(Object^ sender, AddPagesEventArgs^ args)
{
    printDocument->AddPage(txtblk);
    printDocument->AddPagesComplete();
}
