
#include "pch.h"
#include "BitmapPrintDocument.h"

using namespace FingerPaint;

using namespace Concurrency;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Printing;
using namespace Windows::Graphics::Printing::OptionDetails;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Printing;

BitmapPrintDocument::BitmapPrintDocument(GetBitmap^ getBitmap)
{
    // Save callback
    this->getBitmap = getBitmap;

    // Element to print
    border = ref new Border();
    image = ref new Image();
    border->Child = image;

    // Get IPrintDocumentSource and attach event handlers
    printDocumentSource = this->DocumentSource;
    this->Paginate += ref new PaginateEventHandler(this, &BitmapPrintDocument::OnPaginate);
    this->GetPreviewPage += ref new GetPreviewPageEventHandler(this, &BitmapPrintDocument::OnGetPreviewPage);
    this->AddPages += ref new AddPagesEventHandler(this, &BitmapPrintDocument::OnAddPages);

    // Attach PrintManager handler
    PrintManager::GetForCurrentView()->PrintTaskRequested += 
        ref new TypedEventHandler<PrintManager^, PrintTaskRequestedEventArgs^>(this, &BitmapPrintDocument::OnPrintManagerPrintTaskRequested);
}

void BitmapPrintDocument::OnPrintManagerPrintTaskRequested(PrintManager^ sender, PrintTaskRequestedEventArgs^ args)
{
    PrintTaskRequestedDeferral^ deferral = args->Request->GetDeferral();

    // Obtain PrintTask
    PrintTask^ printTask = args->Request->CreatePrintTask("Finger Paint", 
                    ref new PrintTaskSourceRequestedHandler(this, &BitmapPrintDocument::OnPrintTaskSourceRequested));

    // Probably set orientation to landscape
    PrintTaskOptionDetails^ optionDetails = 
        PrintTaskOptionDetails::GetFromPrintTaskOptions(printTask->Options);

    PrintOrientationOptionDetails^ orientation =
        dynamic_cast<PrintOrientationOptionDetails^>(optionDetails->Options->Lookup(StandardPrintTaskOptions::Orientation));

    bitmapIsLandscape = false;

    task<void> dispatcherRunTask = create_task(
        this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this]()
            {
                BitmapSource^ bitmapSource = getBitmap();

                if (bitmapSource != nullptr)
                    bitmapIsLandscape = bitmapSource->PixelWidth > bitmapSource->PixelHeight;
            })));
    dispatcherRunTask.then([this, orientation, deferral]()
    {
        orientation->TrySetValue(bitmapIsLandscape ? PrintOrientation::Landscape : PrintOrientation::Portrait);
        deferral->Complete();
    });
}

void BitmapPrintDocument::OnPrintTaskSourceRequested(PrintTaskSourceRequestedArgs^ args)
{
    args->SetSource(printDocumentSource);
}

void BitmapPrintDocument::OnPaginate(Object^ sender, PaginateEventArgs^ args)
{
    PrintPageDescription pageDesc = args->PrintTaskOptions->GetPageDescription(0);

    // Get the bitmap
    image->Source = getBitmap();

    // Set padding on the Border
    double left = pageDesc.ImageableRect.Left;
    double top = pageDesc.ImageableRect.Top;
    double right = pageDesc.PageSize.Width - left - pageDesc.ImageableRect.Width;
    double bottom = pageDesc.PageSize.Height - top - pageDesc.ImageableRect.Height;
    border->Padding = ThicknessHelper::FromLengths(left, top, right, bottom);

    this->SetPreviewPageCount(1, PreviewPageCountType::Final);
}

void BitmapPrintDocument::OnGetPreviewPage(Object^ sender, GetPreviewPageEventArgs^ args)
{
    this->SetPreviewPage(args->PageNumber, border);
}

void BitmapPrintDocument::OnAddPages(Object^ sender, AddPagesEventArgs^ args)
{
    this->AddPage(border);
    this->AddPagesComplete();
}

    