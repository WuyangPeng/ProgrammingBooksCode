//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RotatingMap;

using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Devices::Geolocation;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();

    // Initialize fields
    integerLongitude = -1;
    integerLatitude = -1;

    geolocator = ref new Geolocator();
    inclinometer = Inclinometer::GetDefault();
    
    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
    SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnMainPageSizeChanged);

    // Get application settings (and later save them)
    IPropertySet^ propertySet = ApplicationData::Current->LocalSettings->Values;
    zoomLevel = propertySet->HasKey("ZoomLevel") ? (int)propertySet->Lookup("ZoomLevel") : 12;
    mapStyle = propertySet->HasKey("MapStyle") ? (MapStyle)(int)propertySet->Lookup("MapStyle") : MapStyle::Aerial;

    Application::Current->Suspending += ref new SuspendingEventHandler([this] (Object^ sender, SuspendingEventArgs^ args)
    {
        IPropertySet^ propertySet = ApplicationData::Current->LocalSettings->Values;
        propertySet->Insert("ZoomLevel", zoomLevel);
        propertySet->Insert("MapStyle", (int)mapStyle);
    });
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Define two task to obtain ViewParams for Road and Aerial views
    std::array<task<ViewParams>, 2> twoTasks = 
    {
        create_task(GetViewParamsAsync(L"Road")),
        create_task(GetViewParamsAsync(L"Aerial"))
    };

    // When completed, save the results
    when_all(begin(twoTasks), end(twoTasks)).then([this] (std::vector<ViewParams> results)
    {
        roadParams = results[0];
        aerialParams = results[1];

        // Get the "powered by" bitmap
        poweredByBitmap->UriSource = ref new Uri(ref new String(roadParams.PoweredByBingUri.c_str()));
        poweredByDisplay->Visibility = Windows::UI::Xaml::Visibility::Visible;

        // Get the current location
        task<Geoposition^> getGeopositionTask = create_task(geolocator->GetGeopositionAsync());
        getGeopositionTask.then([this] (Geoposition^ geoPosition)
        {
            GetLongitudeAndLatitude(geoPosition->Coordinate);
            RefreshDisplay();

            // Get updated locations
            geolocator->PositionChanged += 
                ref new TypedEventHandler<Geolocator^, 
                                          PositionChangedEventArgs^>(this, &MainPage::OnGeolocatorPositionChanged);

            // Enable the application bar
            bottomAppBar->IsEnabled = true;
            streetViewAppBarButton->IsChecked = mapStyle == MapStyle::Road;

            // Get the current yaw
            if (inclinometer != nullptr)
            {
                SetRotation(inclinometer->GetCurrentReading());
                inclinometer->ReadingChanged += 
                    ref new TypedEventHandler<Inclinometer^, 
                                              InclinometerReadingChangedEventArgs^>(this, &MainPage::OnInclinometerReadingChanged);
            }
        });
    });
}

task<ViewParams> MainPage::GetViewParamsAsync(wchar_t* type)
{
    // Define the URI to get Bing imagery metadata
    wchar_t* bingCredentials = L"insert Bing credentials key here";
    std::wstring strUri(L"http://dev.virtualearth.net/REST/V1/Imagery/Metadata/");
    strUri.append(type);
    strUri.append(L"?output=xml&key=");
    strUri.append(bingCredentials);
    Uri^ uri = ref new Uri(ref new String(strUri.c_str()));

    // Open the URI for reading
    RandomAccessStreamReference^ streamRef = RandomAccessStreamReference::CreateFromUri(uri);
    task<IRandomAccessStreamWithContentType^> openReadTask = create_task(streamRef->OpenReadAsync());
    return openReadTask.then([this](IRandomAccessStreamWithContentType^ stream)
    {
        // Create a COM IStream object from the IRandomAccessStreamWithContentType
        ComPtr<IStream> pStream;
        HRESULT hr = CreateStreamOverRandomAccessStream(stream, __uuidof(IStream), &pStream);

        if (FAILED(hr))
                throw ref new COMException(hr, "CreateStreamOverRandomAccessStream failure");
        
        // Create a COM IXmlReader object
        ComPtr<IXmlReader> pXmlReader;
        hr = CreateXmlReader(__uuidof(IXmlReader), &pXmlReader, nullptr);

        if (FAILED(hr))
                throw ref new COMException(hr, "CreateXmlReader failure");

        hr = pXmlReader->SetInput(pStream.Get());

        if (FAILED(hr))
                throw ref new COMException(hr, "XmlReader->SetInput failure");

        // Look for five elements
        bool awaitingZoomMin = false;
        bool awaitingZoomMax = false;
        bool awaitingSubDomains = false;
        bool awaitingImageUrl = false;
        bool awaitingPoweredByBingUri = false;

        // Store the results here
        ViewParams viewParams;
        std::vector<std::wstring> subdomains;

        // Look until the Read doesn't return any more nodes
        XmlNodeType xmlNodeType;
        while (S_OK == (hr = pXmlReader->Read(&xmlNodeType)))
        {
            // Check for beginning and end of elements
            if (xmlNodeType == XmlNodeType_Element || xmlNodeType == XmlNodeType_EndElement)
            {
                LPCWSTR pName;
                unsigned int charCount;
                hr = pXmlReader->GetLocalName(&pName, &charCount);

                if (FAILED(hr))
                    throw ref new COMException(hr, "XmlReader->GetLocalName failure");

                if (wcscmp(pName, L"ImageUrl") == 0)
                {
                    awaitingImageUrl = (xmlNodeType == XmlNodeType_Element);
                }
                else if (wcscmp(pName, L"ImageUrlSubdomains") == 0)
                {
                    awaitingSubDomains = (xmlNodeType == XmlNodeType_Element);
                }
                else if (wcscmp(pName, L"ZoomMin") == 0)
                {
                    awaitingZoomMin = (xmlNodeType == XmlNodeType_Element);
                }
                else if (wcscmp(pName, L"ZoomMax") == 0)
                {
                    awaitingZoomMax = (xmlNodeType == XmlNodeType_Element);
                }
                else if (wcscmp(pName, L"BrandLogoUri") == 0)
                {
                    awaitingPoweredByBingUri = (xmlNodeType == XmlNodeType_Element);
                }
            }

            // Get value of element
            if (xmlNodeType == XmlNodeType_Text)
            {
                LPCWSTR pValue = nullptr;
                unsigned int charCount = 0;
                hr = pXmlReader->GetValue(&pValue, &charCount);

                if (FAILED(hr))
                    throw ref new COMException(hr, "XmlReader->GetValue failure");

                if (awaitingImageUrl)
                {
                    viewParams.UriTemplate = std::wstring(pValue);
                }
                else if (awaitingSubDomains)
                {
                    subdomains.push_back(std::wstring(pValue));
                }
                else if (awaitingZoomMin)
                {
                    viewParams.MinimumLevel = _wtoi(pValue);
                }
                else if (awaitingZoomMax)
                {
                    viewParams.MaximumLevel = _wtoi(pValue);
                }
                else if (awaitingPoweredByBingUri)
                {
                    viewParams.PoweredByBingUri = std::wstring(pValue);
                }
            }
        }

        // Need to make some modifications to the URI string
        int pos = viewParams.UriTemplate.find(L"{culture}");

        if (pos != std::wstring::npos)
            viewParams.UriTemplate.replace(pos, 9, L"en-us");

        pos = viewParams.UriTemplate.find(L"{subdomain}");

        if (pos != std::wstring::npos)
            viewParams.UriTemplate.replace(pos, 11, subdomains[0].c_str());

        return viewParams;
    });
}

void MainPage::OnMainPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    // Clear out the existing Image elements
    imageCanvas->Children->Clear();

    // Determine how many Image elements are needed
    double diagonal = sqrt(pow(args->NewSize.Width, 2) +
                           pow(args->NewSize.Height, 2));

    sqrtNumTiles = 1 + 2 * (int)ceil((diagonal / 2) / 256);

    // Create Image elements for a sqrtNumTiles x sqrtNumTiles array
    for (int i = 0; i < sqrtNumTiles * sqrtNumTiles; i++)
    {
        Image^ image = ref new Image;
        image->Source = ref new BitmapImage();
        image->Stretch = Stretch::None;
        imageCanvas->Children->Append(image);
    }
    RefreshDisplay();
}

void MainPage::OnGeolocatorPositionChanged(Geolocator^ sender, PositionChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            GetLongitudeAndLatitude(args->Position->Coordinate);
            RefreshDisplay();
        }));
}

void MainPage::GetLongitudeAndLatitude(Geocoordinate^ geoCoordinate)
{
    locationDisplay->Visibility = Windows::UI::Xaml::Visibility::Visible;

    // Calculate integer longitude and latitude
    double pi = 3.14159;
    double relativeLongitude = (180 + geoCoordinate->Longitude) / 360;
    integerLongitude = (int)(relativeLongitude * (1 << BITRES));

    double sineTerm = sin(pi * geoCoordinate->Latitude / 180);
    double relativeLatitude = 0.5 - log((1 + sineTerm) / (1 - sineTerm)) / (4 * pi);
    integerLatitude = (int)(relativeLatitude * (1 << BITRES));
}

void MainPage::OnInclinometerReadingChanged(Inclinometer^ sender, InclinometerReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            SetRotation(args->Reading);
        }));
}

void MainPage::SetRotation(InclinometerReading^ inclinometerReading)
{
    if (inclinometerReading == nullptr)
        return;

    imageCanvasRotate->Angle = inclinometerReading->YawDegrees;
    northArrowRotate->Angle = inclinometerReading->YawDegrees;
}

void MainPage::RefreshDisplay()
{
    if (roadParams.UriTemplate.size() == 0 || aerialParams.UriTemplate.size() == 0)
        return;

    if (integerLongitude == -1 || integerLatitude == -1)
        return;

    // Get coordinates and pixel offsets based on current zoom level
    int croppedLongitude = integerLongitude >> (BITRES - zoomLevel);
    int croppedLatitude = integerLatitude >> (BITRES - zoomLevel);
    int xPixelOffset = (integerLongitude >> (BITRES - zoomLevel - 8)) % 256;
    int yPixelOffset = (integerLatitude >> (BITRES - zoomLevel - 8)) % 256;

    // Prepare for the loop
    std::wstring uriTemplate = (mapStyle == MapStyle::Road ? roadParams : aerialParams).UriTemplate;
    int index = 0;
    int maxValue = (1 << zoomLevel) - 1;

    // Loop through the array of Image elements
    for (int row = -sqrtNumTiles / 2; row <= sqrtNumTiles / 2; row++)
        for (int col = -sqrtNumTiles / 2; col <= sqrtNumTiles / 2; col++)
        {
            // Get the Image and BitmapImage
            Image^ image = dynamic_cast<Image^>(imageCanvas->Children->GetAt(index));
            BitmapImage^ bitmap = dynamic_cast<BitmapImage^>(image->Source);
            index++;

            // Check if we've gone beyond the bounds
            if (croppedLongitude + col < 0 ||
                croppedLongitude + col > maxValue ||
                croppedLatitude + row < 0 ||
                croppedLatitude + row > maxValue)
            {
                bitmap->UriSource = nullptr;
            }
            else
            {
                // Calculate a quadkey and set URI to bitmap
                int longitude = croppedLongitude + col;
                int latitude = croppedLatitude + row;
                std::wstring quadkey = ToQuadKey(longitude, latitude, zoomLevel);

                std::wstring uri(uriTemplate);
                int pos = uri.find(L"{quadkey}");
                uri.replace(pos, 9, quadkey);
                bitmap->UriSource = ref new Uri(ref new String(uri.c_str()));
            }

            // Position the Image element
            Canvas::SetLeft(image, col * 256 - xPixelOffset);
            Canvas::SetTop(image, row * 256 - yPixelOffset);
        }
}

std::wstring MainPage::ToQuadKey(int longitude, int latitude, int level)
{
    int64 quadkey = 0;
    int mask = 1 << (level - 1);

    for (int i = 0; i < level; i++)
    {
        quadkey <<= 2;

        if ((longitude & mask) != 0)
            quadkey |= 1;

        if ((latitude & mask) != 0)
            quadkey |= 2;

        mask >>= 1;
    }

    std::wstring str;

    for (int i = 0; i < level; i++)
    {
        str.insert(0, 1, (quadkey & 3) + '0');
        quadkey >>= 2;
    }
    return str;
}

void MainPage::OnStreetViewAppBarButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    ToggleButton^ btn = dynamic_cast<ToggleButton^>(sender);
    ViewParams viewParams;

    if (btn->IsChecked->Value)
    {
        mapStyle = MapStyle::Road;
        viewParams = roadParams;
    }
    else
    {
        mapStyle = MapStyle::Aerial;
        viewParams = aerialParams;
    }

    zoomLevel = max(viewParams.MinimumLevel, min(viewParams.MaximumLevel, zoomLevel));
    RefreshDisplay();
    RefreshButtons();
}

void MainPage::OnZoomInAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    zoomLevel += 1;
    RefreshDisplay();
    RefreshButtons();
}

void MainPage::OnZoomOutAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    zoomLevel -= 1;
    RefreshDisplay();
    RefreshButtons();
}

void MainPage::RefreshButtons()
{
    ViewParams viewParams = streetViewAppBarButton->IsChecked->Value ? roadParams : aerialParams;
    zoomInAppBarButton->IsEnabled = zoomLevel < viewParams.MaximumLevel;
    zoomOutAppBarButton->IsEnabled = zoomLevel > viewParams.MinimumLevel;
}

