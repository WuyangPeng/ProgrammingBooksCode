//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "AppSettings.h"
#include "ColorSettingDialog.xaml.h"
#include "ThicknessSettingDialog.xaml.h"

namespace FingerPaint
{
    public ref class MainPage sealed
    {
    private:
        ref struct PointerInfo
        {
        internal:
            Windows::Foundation::Point PreviousPoint;
            float PreviousRadius;
        };

        AppSettings^ appSettings;

        Platform::Collections::Map<unsigned int, PointerInfo^>^ pointerDictionary;
        Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap;
        byte* pixels;

        Windows::Foundation::Collections::IVector<float>^ xCollection;
        PetzoldWindows8VectorDrawing::RoundCappedLine^ roundCappedLine;
        PetzoldWindows8VectorDrawing::RoundCappedPath^ roundCappedPath;

        Windows::Foundation::Point imageOffset;
        float imageScale;

        // In MainPage.xaml.cpp
    public:
        MainPage();

    private:
        void OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void CalculateImageScaleAndOffset();
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnApplicationSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
        void OnColorAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnThicknessAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void DisplayDialog(Platform::Object^ sender, Windows::UI::Xaml::FrameworkElement^ dialog);

        // In MainPage.File.cpp
    private:
        Concurrency::task<void> CreateNewBitmapAndPixelArray();
        Concurrency::task<void> LoadBitmapFromFile();
        Concurrency::task<void> LoadBitmapFromFile(Windows::Storage::StorageFile^ storageFile);
        void InitializeBitmap();
        void OnAddAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnOpenAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Concurrency::task<void> CheckIfOkToTrashFile(Concurrency::task<void> (MainPage::*commandAction)(void));
        Concurrency::task<void> LoadFileFromOpenPicker();
        void OnSaveAsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSaveAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Concurrency::task<Windows::Storage::StorageFile^> GetFileFromSavePicker();
        Concurrency::task<bool> SaveWithErrorNotification(Platform::String^ filename);
        Concurrency::task<bool> SaveWithErrorNotification(Windows::Storage::StorageFile^ storageFile);
        Concurrency::task<void> SaveBitmapToFile();
        Concurrency::task<void> SaveBitmapToFile(Platform::String^ filename);
        Concurrency::task<void> SaveBitmapToFile(Windows::Storage::StorageFile^ storageFile);


        // In MainPage.Pointer.cpp
       protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

    private:
        bool RenderOnBitmap(Windows::Foundation::Point point1, float radius1, Windows::Foundation::Point point2, float radius2, Windows::UI::Color color);
        Windows::Foundation::Point ScaleToBitmap(Windows::Foundation::Point pt);

    };
}
