//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace PrintPrintableArea
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::Printing::PrintDocument^ printDocument;
        Windows::Graphics::Printing::IPrintDocumentSource^ printDocumentSource;
        Windows::UI::Xaml::Controls::Border^ border;
        Windows::Foundation::EventRegistrationToken printTaskRequestedEventToken;

    public:
        MainPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void OnPrintManagerPrintTaskRequested(Windows::Graphics::Printing::PrintManager^ sender, Windows::Graphics::Printing::PrintTaskRequestedEventArgs^ args);
        void OnPrintDocumentPaginate(Platform::Object^ sender, Windows::UI::Xaml::Printing::PaginateEventArgs^ args);
        void OnPrintDocumentGetPreviewPage(Platform::Object^ sender, Windows::UI::Xaml::Printing::GetPreviewPageEventArgs^ args);
        void OnPrintDocumentAddPages(Platform::Object^ sender, Windows::UI::Xaml::Printing::AddPagesEventArgs^ args);
    };
}
