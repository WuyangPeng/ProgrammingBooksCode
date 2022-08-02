#pragma once

namespace ApplicationStateSave
{
    public ref class SaveStatePage : Windows::UI::Xaml::Controls::Page
    {
    internal:
        SaveStatePage();

    private:
        static void OnApplicationSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);

    protected:
        property Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ PageState;
        static property Windows::Foundation::Collections::IMap<int, Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^>^ Pages;
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
    };
}