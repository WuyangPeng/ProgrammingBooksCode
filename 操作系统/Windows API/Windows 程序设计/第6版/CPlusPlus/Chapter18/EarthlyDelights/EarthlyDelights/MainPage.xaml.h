//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace EarthlyDelights
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::OrientationSensor^ orientationSensor;
        double pageWidth, pageHeight, maxDimension;
        int imageWidth, imageHeight;
        double zoomInScale;
        double rotation;
        bool isZoomView;

        // Dependency property for zoom-in transition animation
        static Windows::UI::Xaml::DependencyProperty^ interpolationFactorProperty;

    public:
        MainPage();

        // Interpolation Factor property
        static property Windows::UI::Xaml::DependencyProperty^ InterpolationFactorProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return interpolationFactorProperty; }
        };

        property double InterpolationFactor
        {
            void set(double value) 
            { 
                SetValue(InterpolationFactorProperty, value); 
            }
            double get() 
            { 
                return (double)GetValue(InterpolationFactorProperty); 
            }
        };

    protected:
        virtual void OnTapped(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e) override;

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);

        void OnBitmapImageDownloadProgress(Platform::Object^ sender, Windows::UI::Xaml::Media::Imaging::DownloadProgressEventArgs^ args);
        void OnBitmapImageFailed(Platform::Object^ sender, Windows::UI::Xaml::ExceptionRoutedEventArgs^ arg);
        void OnBitmapImageOpened(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

        void OnOrientationSensorReadingChanged(Windows::Devices::Sensors::OrientationSensor^ sender,
                                               Windows::Devices::Sensors::OrientationSensorReadingChangedEventArgs^ args);
        void ProcessNewOrientationReading(Windows::Devices::Sensors::OrientationSensorReading^ orientationReading);

        DirectX::XMVECTOR HorizontalCoordinateToVector(double altitude, double azimuth);

        static void OnInterpolationFactorChanged(Windows::UI::Xaml::DependencyObject^ obj,
                                                 Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void UpdateImageTransforms();
    };
}
