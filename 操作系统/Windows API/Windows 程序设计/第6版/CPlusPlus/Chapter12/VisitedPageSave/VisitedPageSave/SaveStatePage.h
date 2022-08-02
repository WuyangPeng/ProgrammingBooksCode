#pragma once

namespace VisitedPageSave
{
    public ref class SaveStatePage : Windows::UI::Xaml::Controls::Page
    {
    private:
        static Platform::Collections::Map<int, Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^>^ pages;

    internal:
        SaveStatePage() {}

    protected:
        property Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ PageState;
        static property Windows::Foundation::Collections::IMap<int, Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^>^ Pages
        {
            Windows::Foundation::Collections::IMap<int, Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^>^ get() { return pages; }
        }

        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
    };
}