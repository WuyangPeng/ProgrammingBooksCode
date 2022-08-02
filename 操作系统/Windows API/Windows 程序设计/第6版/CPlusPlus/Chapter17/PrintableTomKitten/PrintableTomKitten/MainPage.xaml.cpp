//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PrintableTomKitten;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Printing;
using namespace Windows::Graphics::Printing::OptionDetails;
using namespace Windows::UI;
using namespace Windows::UI::Core;
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

    std::array<UIElement^, 57> bookPagesInitialized = 
    { 
        ref new TomKitten03(), ref new TomKitten04(), ref new TomKitten05(), ref new TomKitten06(),
        ref new TomKitten07(), ref new TomKitten08(), ref new TomKitten09(), ref new TomKitten10(), 
        ref new TomKitten11(), ref new TomKitten12(), ref new TomKitten13(), ref new TomKitten14(), 
        ref new TomKitten15(), ref new TomKitten16(), ref new TomKitten17(), ref new TomKitten18(),
        ref new TomKitten19(), ref new TomKitten20(), ref new TomKitten21(), ref new TomKitten22(),
        ref new TomKitten23(), ref new TomKitten24(), ref new TomKitten25(), ref new TomKitten26(),
        ref new TomKitten27(), ref new TomKitten28(), ref new TomKitten29(), ref new TomKitten30(),
        ref new TomKitten31(), ref new TomKitten32(), ref new TomKitten33(), ref new TomKitten34(),
        ref new TomKitten35(), ref new TomKitten36(), ref new TomKitten37(), ref new TomKitten38(),
        ref new TomKitten39(), ref new TomKitten40(), ref new TomKitten41(), ref new TomKitten42(),
        ref new TomKitten43(), ref new TomKitten44(), ref new TomKitten45(), ref new TomKitten46(),
        ref new TomKitten47(), ref new TomKitten48(), ref new TomKitten49(), ref new TomKitten50(),
        ref new TomKitten51(), ref new TomKitten52(), ref new TomKitten53(), ref new TomKitten54(),
        ref new TomKitten55(), ref new TomKitten56(), ref new TomKitten57(), ref new TomKitten58(),
        ref new TomKitten59()
    };
    bookPages = bookPagesInitialized;

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
    PrintTask^ printTask = args->Request->CreatePrintTask("Hello Printer", 
                                   ref new PrintTaskSourceRequestedHandler(this, &MainPage::OnPrintTaskSourceRequested));

    // Get PrintTaskOptionDetails for making changing to options
    PrintTaskOptionDetails^ optionDetails = PrintTaskOptionDetails::GetFromPrintTaskOptions(printTask->Options);

    // Create the custom item
    PrintCustomItemListOptionDetails^ pageRange = optionDetails->CreateItemListOption("idPrintRange", "Print range");
    pageRange->AddItem("idPrintAll", "Print all pages");
    pageRange->AddItem("idPrintCustom", "Print custom range");

    // Add it to the options
    optionDetails->DisplayedOptions->Append("idPrintRange");

    // Create a page-range edit item also, but this only
    //      comes into play when user select "Print custom range"
    optionDetails->CreateTextOption("idCustomRangeEdit", "Custom Range");

    // Set a handler for the OptionChanged event
    optionDetails->OptionChanged += ref new TypedEventHandler<PrintTaskOptionDetails^, PrintTaskOptionChangedEventArgs^>(this, &MainPage::OnOptionDetailsOptionChanged);
}

void MainPage::OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs^ args)
{
    args->SetSource(printDocumentSource);
}

void MainPage::OnOptionDetailsOptionChanged(PrintTaskOptionDetails^ sender, PrintTaskOptionChangedEventArgs^ args)
{
    if (args->OptionId == nullptr)
        return;

    String^ optionId = dynamic_cast<String^>(args->OptionId);
    String^ strValue = sender->Options->Lookup(optionId)->Value->ToString();
    String^ errorText = "";

    if (optionId == "idPrintRange")
    {
        if (strValue == "idPrintAll")
        {
            unsigned int index = 0;
            if (sender->DisplayedOptions->IndexOf("idCustomRangeEdit", &index))
                sender->DisplayedOptions->RemoveAt(index);
        }
        else if (strValue == "idPrintCustom")
        {
            sender->DisplayedOptions->Append("idCustomRangeEdit");
        }
    }
    else if (optionId == "idCustomRangeEdit")
    {
        // Check to see if CustomPageRange accepts this
        CustomPageRange^ pageRange = ref new CustomPageRange(strValue, bookPages.size());

        if (!pageRange->IsValid)
        {
            errorText = "Use the form 2-4, 7, 9-11";
        }
    }

    sender->Options->Lookup(optionId)->ErrorText = errorText;

    // If there's no error, then invalidate the preview
    if (errorText == "")
    {
        this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler(
        [this]()
        {
            printDocument->InvalidatePreview();
        }));
    }
}

void MainPage::OnPrintDocumentPaginate(Object^ sender, PaginateEventArgs^ args)
{
    // Obtain the print range option
    PrintTaskOptionDetails^ optionDetails = PrintTaskOptionDetails::GetFromPrintTaskOptions(args->PrintTaskOptions);

    String^ strValue = dynamic_cast<String^>(optionDetails->Options->Lookup("idPrintRange")->Value);

    if (strValue == "idPrintCustom")
    {
        // Parse the print range for GetPreviewPage and AddPages
        String^ strPageRange = dynamic_cast<String^>(optionDetails->Options->Lookup("idCustomRangeEdit")->Value);
        customPageRange = ref new CustomPageRange(strPageRange, bookPages.size());
    }
    else
    {
        // Make sure field is null if printing all pages
        customPageRange = nullptr;
    }

    int pageCount = bookPages.size();

    if (customPageRange != nullptr && customPageRange->IsValid)
        pageCount = customPageRange->PageMapping->Size;

    printDocument->SetPreviewPageCount(pageCount, PreviewPageCountType::Final);
}

void MainPage::OnPrintDocumentGetPreviewPage(Object^ sender, GetPreviewPageEventArgs^ args)
{
    int oneBasedIndex = args->PageNumber;

    if (customPageRange != nullptr && customPageRange->IsValid)
        oneBasedIndex = customPageRange->PageMapping->GetAt(args->PageNumber - 1);

    printDocument->SetPreviewPage(args->PageNumber, bookPages[oneBasedIndex - 1]);
}

void MainPage::OnPrintDocumentAddPages(Object^ sender, AddPagesEventArgs^ args)
{
    if (customPageRange != nullptr && customPageRange->IsValid)
    {
        for (unsigned int index = 0; index < customPageRange->PageMapping->Size; index++)
            printDocument->AddPage(bookPages[customPageRange->PageMapping->GetAt(index) - 1]);
    }
    else
    {
        for (unsigned int index = 0; index < bookPages.size(); index++)
            printDocument->AddPage(bookPages[index]);
    }
    printDocument->AddPagesComplete();
}
