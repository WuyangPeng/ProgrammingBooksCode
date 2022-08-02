//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "SplitContainer.xaml.h"
#include "RulerContainer.xaml.h"
#include "SettingsDialog.xaml.h"
#include "TabbableTextBox.h"
#include "AppSettings.h"

namespace XamlCruncher
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::Media::Brush^ textBlockBrush;
        Windows::UI::Xaml::Media::Brush^ textBoxBrush;
        Windows::UI::Xaml::Media::Brush^ errorBrush;
        XamlCruncher::AppSettings^ appSettings;
        Windows::Storage::StorageFile^ loadedStorageFile;

    public:
        MainPage();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void FinishInitialization();
        void OnApplicationSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
        Concurrency::task<void> SetDefaultXamlFile();
        void OnRefreshAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSettingsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

        // File I/O events
        void OnAddAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnOpenAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Concurrency::task<void> CheckIfOkToTrashFile(Concurrency::task<void> (MainPage::*commandAction)(void));
        Concurrency::task<void> LoadFileFromOpenPicker();
        void OnSaveAsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSaveAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Concurrency::task<Windows::Storage::StorageFile^> GetFileFromSavePicker();
        Concurrency::task<void> SaveXamlToFile(Windows::Storage::StorageFile^ storageFile);

        // TextBox events
        void OnEditBoxSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void DisplayLineAndColumn();
        void OnEditBoxTextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ args);
        void ParseText();
        void SetErrorText(Platform::String^ text);
        void SetOkText();
        void SetStatusText(Platform::String^ text, Windows::UI::Xaml::Media::Brush^ statusBrush, Windows::UI::Xaml::Media::Brush^ textBoxBrush);
    };
}
