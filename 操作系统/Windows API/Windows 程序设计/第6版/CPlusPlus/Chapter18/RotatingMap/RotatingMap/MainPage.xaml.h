//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ViewParams.h"
#include "MapStyle.h"

namespace RotatingMap
{
    public ref class MainPage sealed
    {
    private:
        static const int BITRES = 29;

        ViewParams aerialParams;
        ViewParams roadParams;

        Windows::Devices::Geolocation::Geolocator^ geolocator;
        Windows::Devices::Sensors::Inclinometer^ inclinometer;

        int sqrtNumTiles;           // always an odd number
        int integerLongitude;
        int integerLatitude;
        
        // Saved as application settings
        MapStyle mapStyle;
        int zoomLevel;

    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Concurrency::task<ViewParams> GetViewParamsAsync(wchar_t* type);
        void OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void OnGeolocatorPositionChanged(Windows::Devices::Geolocation::Geolocator^ sender, 
                                         Windows::Devices::Geolocation::PositionChangedEventArgs^ args);
        void GetLongitudeAndLatitude(Windows::Devices::Geolocation::Geocoordinate^ geoCoordinate);

        void OnInclinometerReadingChanged(Windows::Devices::Sensors::Inclinometer^ sender,
                                          Windows::Devices::Sensors::InclinometerReadingChangedEventArgs^ args);
        void SetRotation(Windows::Devices::Sensors::InclinometerReading^ inclinometerReading);
        void RefreshDisplay();
        std::wstring ToQuadKey(int longitude, int latitude, int level);

        // App bar buttons
        void OnStreetViewAppBarButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnZoomInAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnZoomOutAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void RefreshButtons();
    };
}
