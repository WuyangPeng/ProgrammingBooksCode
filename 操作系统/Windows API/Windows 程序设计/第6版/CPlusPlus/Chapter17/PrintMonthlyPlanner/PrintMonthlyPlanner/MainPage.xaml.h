//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "MonthYearSelect.xaml.h"

namespace PrintMonthlyPlanner
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::Printing::PrintDocument^ printDocument;
        Windows::Graphics::Printing::IPrintDocumentSource^ printDocumentSource;
        Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ calendarPages;
        bool printingEnabled;
        Windows::Foundation::EventRegistrationToken printTaskRequestedEventToken;

    public:
        MainPage();

    private:
        void OnMonthYearChanged(Platform::Object^ sender, Windows::Globalization::Calendar^ args);
        int GetPrintableMonthCount();
        void OnPrintButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

        void OnPrintManagerPrintTaskRequested(Windows::Graphics::Printing::PrintManager^ sender, Windows::Graphics::Printing::PrintTaskRequestedEventArgs^ args);
        void OnPrintTaskSourceRequested(Windows::Graphics::Printing::PrintTaskSourceRequestedArgs^ args);
        void OnPrintDocumentPaginate(Platform::Object^ sender, Windows::UI::Xaml::Printing::PaginateEventArgs^ args);
        void OnPrintDocumentGetPreviewPage(Platform::Object^ sender, Windows::UI::Xaml::Printing::GetPreviewPageEventArgs^ args);
        void OnPrintDocumentAddPages(Platform::Object^ sender, Windows::UI::Xaml::Printing::AddPagesEventArgs^ args);
    };
}
