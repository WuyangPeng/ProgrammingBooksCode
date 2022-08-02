#pragma once

#include "pch.h"

namespace FingerPaint
{
    public delegate Windows::UI::Xaml::Media::Imaging::BitmapSource^ GetBitmap();

    public ref class BitmapPrintDocument sealed : Windows::UI::Xaml::Printing::PrintDocument
    {
    private:
        GetBitmap^ getBitmap;
        Windows::Graphics::Printing::IPrintDocumentSource^ printDocumentSource;
        Windows::UI::Xaml::Controls::Border^ border;
        Windows::UI::Xaml::Controls::Image^ image;
        bool bitmapIsLandscape;

    public:
        BitmapPrintDocument(GetBitmap^ getBitmap);

    private:
        void OnPrintManagerPrintTaskRequested(Windows::Graphics::Printing::PrintManager^ sender, 
                                              Windows::Graphics::Printing::PrintTaskRequestedEventArgs^ args);
        void OnPrintTaskSourceRequested(Windows::Graphics::Printing::PrintTaskSourceRequestedArgs^ args);
        void OnPaginate(Platform::Object^ sender, Windows::UI::Xaml::Printing::PaginateEventArgs^ args);
        void OnGetPreviewPage(Platform::Object^ sender, Windows::UI::Xaml::Printing::GetPreviewPageEventArgs^ args);
        void OnAddPages(Platform::Object^ sender, Windows::UI::Xaml::Printing::AddPagesEventArgs^ args);
    };
}