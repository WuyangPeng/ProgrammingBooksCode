//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace RichTextEditor
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Platform::Collections::Vector<Platform::String^>^ GetFontFamilies();
        void OnAppSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);

        void OnTopAppBarOpened(Platform::Object^ sender, Platform::Object^ args);
        void OnBoldAppBarCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnItalicAppBarCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnUnderlineAppBarCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnFontSizeComboBoxSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ args);
        void OnFontFamilyComboBoxSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ args);
        void OnAlignAppBarRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnOpenAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSaveAsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
