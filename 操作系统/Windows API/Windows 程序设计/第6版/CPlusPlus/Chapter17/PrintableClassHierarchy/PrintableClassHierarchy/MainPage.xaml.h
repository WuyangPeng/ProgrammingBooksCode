//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ClassAndSubclasses.h"

namespace PrintableClassHierarchy
{
    public ref class MainPage sealed
    {
    private:
        ReflectionHelper::TypeInformation^ rootTypeInfo;
        Platform::Collections::Vector<ReflectionHelper::TypeInformation^>^ classes;
        Windows::UI::Xaml::Media::Brush^ highlightBrush;

        // Printing support
        Platform::Collections::Vector<Windows::UI::Xaml::Controls::TextBlock^>^ printerTextBlocks;
        Windows::UI::Xaml::Media::Brush^ blackBrush;
        Windows::UI::Xaml::Printing::PrintDocument^ printDocument;
        Windows::Graphics::Printing::IPrintDocumentSource^ printDocumentSource;
        Platform::Collections::Vector<Windows::UI::Xaml::UIElement^>^ printerPages;

        Windows::Foundation::EventRegistrationToken printTaskRequestedEventToken;

    public:
        MainPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void AddToClassList(Platform::Type^ sampleType);
        void AddToTree(ClassAndSubclasses^ node, Windows::Foundation::Collections::IVector<ReflectionHelper::TypeInformation^>^ classes);
        void DisplayAndPrinterPrep(ClassAndSubclasses^ node, int indent);
        Windows::UI::Xaml::Controls::TextBlock^ CreateTextBlock(ReflectionHelper::TypeInformation^ typeInfo, int indent);

        void OnPrintManagerPrintTaskRequested(Windows::Graphics::Printing::PrintManager^ sender, Windows::Graphics::Printing::PrintTaskRequestedEventArgs^ args);
        void OnPrintDocumentPaginate(Platform::Object^ sender, Windows::UI::Xaml::Printing::PaginateEventArgs^ args);
        void OnPrintDocumentGetPreviewPage(Platform::Object^ sender, Windows::UI::Xaml::Printing::GetPreviewPageEventArgs^ args);
        void OnPrintDocumentAddPages(Platform::Object^ sender, Windows::UI::Xaml::Printing::AddPagesEventArgs^ args);
    };
}
