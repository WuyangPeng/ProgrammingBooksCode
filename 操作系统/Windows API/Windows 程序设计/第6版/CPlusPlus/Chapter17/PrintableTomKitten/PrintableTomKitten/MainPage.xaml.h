//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "TomKitten03.xaml.h"
#include "TomKitten04.xaml.h"
#include "TomKitten05.xaml.h"
#include "TomKitten06.xaml.h"
#include "TomKitten07.xaml.h"
#include "TomKitten08.xaml.h"
#include "TomKitten09.xaml.h"
#include "TomKitten10.xaml.h"
#include "TomKitten11.xaml.h"
#include "TomKitten12.xaml.h"
#include "TomKitten13.xaml.h"
#include "TomKitten14.xaml.h"
#include "TomKitten15.xaml.h"
#include "TomKitten16.xaml.h"
#include "TomKitten17.xaml.h"
#include "TomKitten18.xaml.h"
#include "TomKitten19.xaml.h"
#include "TomKitten20.xaml.h"
#include "TomKitten21.xaml.h"
#include "TomKitten22.xaml.h"
#include "TomKitten23.xaml.h"
#include "TomKitten24.xaml.h"
#include "TomKitten25.xaml.h"
#include "TomKitten26.xaml.h"
#include "TomKitten27.xaml.h"
#include "TomKitten28.xaml.h"
#include "TomKitten29.xaml.h"
#include "TomKitten30.xaml.h"
#include "TomKitten31.xaml.h"
#include "TomKitten32.xaml.h"
#include "TomKitten33.xaml.h"
#include "TomKitten34.xaml.h"
#include "TomKitten35.xaml.h"
#include "TomKitten36.xaml.h"
#include "TomKitten37.xaml.h"
#include "TomKitten38.xaml.h"
#include "TomKitten39.xaml.h"
#include "TomKitten40.xaml.h"
#include "TomKitten41.xaml.h"
#include "TomKitten42.xaml.h"
#include "TomKitten43.xaml.h"
#include "TomKitten44.xaml.h"
#include "TomKitten45.xaml.h"
#include "TomKitten46.xaml.h"
#include "TomKitten47.xaml.h"
#include "TomKitten48.xaml.h"
#include "TomKitten49.xaml.h"
#include "TomKitten50.xaml.h"
#include "TomKitten51.xaml.h"
#include "TomKitten52.xaml.h"
#include "TomKitten53.xaml.h"
#include "TomKitten54.xaml.h"
#include "TomKitten55.xaml.h"
#include "TomKitten56.xaml.h"
#include "TomKitten57.xaml.h"
#include "TomKitten58.xaml.h"
#include "TomKitten59.xaml.h"
#include "CustomPageRange.h"

namespace PrintableTomKitten
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::Printing::PrintDocument^ printDocument;
        Windows::Graphics::Printing::IPrintDocumentSource^ printDocumentSource;
        PrintableTomKitten::CustomPageRange^ customPageRange;
        std::array<Windows::UI::Xaml::UIElement^, 57> bookPages;
        Windows::Foundation::EventRegistrationToken printTaskRequestedEventToken;

    public:
        MainPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void OnPrintManagerPrintTaskRequested(Windows::Graphics::Printing::PrintManager^ sender, Windows::Graphics::Printing::PrintTaskRequestedEventArgs^ args);
        void OnPrintTaskSourceRequested(Windows::Graphics::Printing::PrintTaskSourceRequestedArgs^ args);
        void OnOptionDetailsOptionChanged(Windows::Graphics::Printing::OptionDetails::PrintTaskOptionDetails^ sender, Windows::Graphics::Printing::OptionDetails::PrintTaskOptionChangedEventArgs^ args);
        void OnPrintDocumentPaginate(Platform::Object^ sender, Windows::UI::Xaml::Printing::PaginateEventArgs^ args);
        void OnPrintDocumentGetPreviewPage(Platform::Object^ sender, Windows::UI::Xaml::Printing::GetPreviewPageEventArgs^ args);
        void OnPrintDocumentAddPages(Platform::Object^ sender, Windows::UI::Xaml::Printing::AddPagesEventArgs^ args);
    };
}
