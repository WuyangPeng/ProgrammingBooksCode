using System;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Geolocation;
using Windows.Devices.Sensors;
using Windows.Foundation.Collections;
using Windows.Graphics.Display;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

using RotatingMap.ImageryService;

namespace RotatingMap
{
    public sealed partial class MainPage : Page
    {
        const int BITRES = 29;

        // Storage of parameters for two views
        class ViewParams
        {
            public string UriTemplate;
            public int MinimumLevel;
            public int MaximumLevel;
        }
        ViewParams aerialParams;
        ViewParams roadParams;

        Geolocator geolocator = new Geolocator();
        Inclinometer inclinometer = Inclinometer.GetDefault();

        int sqrtNumTiles;       // always an odd number
        int integerLongitude = -1;
        int integerLatitude = -1;
        StringBuilder strBuilder = new StringBuilder();

        // Saved as application settings
        MapStyle mapStyle = MapStyle.Aerial;
        int zoomLevel = 12;

        public MainPage()
        {
            this.InitializeComponent();
            DisplayProperties.AutoRotationPreferences = DisplayProperties.NativeOrientation;
            Loaded += OnMainPageLoaded;
            SizeChanged += OnMainPageSizeChanged;

            // Get application settings (and later save them)
            IPropertySet propertySet = ApplicationData.Current.LocalSettings.Values;

            if (propertySet.ContainsKey("ZoomLevel"))
                zoomLevel = (int)propertySet["ZoomLevel"];

            if (propertySet.ContainsKey("MapStyle"))
                mapStyle = (MapStyle)(int)propertySet["MapStyle"];

            Application.Current.Suspending += (sender, args) =>
            {
                propertySet["ZoomLevel"] = zoomLevel;
                propertySet["MapStyle"] = (int)mapStyle;
            };
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            // Initialize the Bing Maps imagery service
            ImageryServiceClient imageryServiceClient = 
                new ImageryServiceClient(
                    ImageryServiceClient.EndpointConfiguration.BasicHttpBinding_IImageryService);

            // Make two requests for road and aerial views
            ImageryMetadataRequest request = new ImageryMetadataRequest
            {
                Credentials = new Credentials
                {
                    ApplicationId = "AkNpobMGtsXUh9o8T9j1doUmjhtcoexUHHTClyBILqnrag-ibtcHruZQPFo61cn8"
                },
                Style = MapStyle.Road
            };
            Task<ImageryMetadataResponse> roadStyleTask = 
                        imageryServiceClient.GetImageryMetadataAsync(request);

            request = new ImageryMetadataRequest
            {
                Credentials = new Credentials
                {
                    ApplicationId = "insert Bing credentials key here"
                },
                Style = MapStyle.Aerial
            };
            Task<ImageryMetadataResponse> aerialStyleTask = 
                        imageryServiceClient.GetImageryMetadataAsync(request);

            // Wait for both tasks to complete
            Task.WaitAll(roadStyleTask, aerialStyleTask);

            // Check if everything is OK
            if (!roadStyleTask.IsCanceled && !roadStyleTask.IsFaulted && 
                !aerialStyleTask.IsCanceled && !aerialStyleTask.IsCanceled)
            {
                // Get the "powered by" bitmap
                poweredByBitmap.UriSource = roadStyleTask.Result.BrandLogoUri;
                poweredByDisplay.Visibility = Visibility.Visible;

                // Get the URIs and min/max zoom levels
                roadParams = CreateViewParams(roadStyleTask.Result.Results[0]);
                aerialParams = CreateViewParams(aerialStyleTask.Result.Results[0]);

                // Get the current location
                Geoposition geoPosition = await geolocator.GetGeopositionAsync();
                GetLongitudeAndLatitude(geoPosition.Coordinate);
                RefreshDisplay();

                // Get updated locations
                geolocator.PositionChanged += OnGeolocatorPositionChanged;

                // Enable the application bar
                bottomAppBar.IsEnabled = true;
                streetViewAppBarButton.IsChecked = mapStyle == MapStyle.Road;

                // Get the current yaw
                if (inclinometer != null)
                {
                    SetRotation(inclinometer.GetCurrentReading());
                    inclinometer.ReadingChanged += OnInclinometerReadingChanged;
                }
            }
        }

        ViewParams CreateViewParams(ImageryMetadataResult result)
        {
            string uri = result.ImageUri;
            uri = uri.Replace("{subdomain}", result.ImageUriSubdomains[0]);
            uri = uri.Replace("&token={token}", "");
            uri = uri.Replace("{culture}", "en-us");

            return new ViewParams
            {
                UriTemplate = uri,
                MinimumLevel = result.ZoomRange.From,
                MaximumLevel = result.ZoomRange.To
            };
        }

        void OnMainPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            // Clear out the existing Image elements
            imageCanvas.Children.Clear();

            // Determine how many Image elements are needed
            double diagonal = Math.Sqrt(Math.Pow(args.NewSize.Width, 2) +
                                        Math.Pow(args.NewSize.Height, 2));

            sqrtNumTiles = 1 + 2 * (int)Math.Ceiling((diagonal / 2) / 256);

            // Create Image elements for a sqrtNumTiles x sqrtNumTiles array
            for (int i = 0; i < sqrtNumTiles * sqrtNumTiles; i++)
            {
                Image image = new Image
                {
                    Source = new BitmapImage(),
                    Stretch = Stretch.None
                };
                imageCanvas.Children.Add(image);
            }
            RefreshDisplay();
        }

        async void OnGeolocatorPositionChanged(Geolocator sender, PositionChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    GetLongitudeAndLatitude(args.Position.Coordinate);
                    RefreshDisplay();
                });
        }

        void GetLongitudeAndLatitude(Geocoordinate geoCoordinate)
        {
            locationDisplay.Visibility = Visibility.Visible;

            // Calculate integer longitude and latitude
            double relativeLongitude = (180 + geoCoordinate.Longitude) / 360;
            integerLongitude = (int)(relativeLongitude * (1 << BITRES));

            double sinTerm = Math.Sin(Math.PI * geoCoordinate.Latitude / 180);
            double relativeLatitude = 0.5 - Math.Log((1 + sinTerm) / (1 - sinTerm)) / (4 * Math.PI);
            integerLatitude = (int)(relativeLatitude * (1 << BITRES));
        }

        async void OnInclinometerReadingChanged(Inclinometer sender, 
                                                InclinometerReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
            {
                SetRotation(args.Reading);
            });
        }

        void SetRotation(InclinometerReading inclinometerReading)
        {
            if (inclinometerReading == null)
                return;

            imageCanvasRotate.Angle = inclinometerReading.YawDegrees;
            northArrowRotate.Angle = inclinometerReading.YawDegrees;
        }

        void RefreshDisplay()
        {
            if (roadParams == null || aerialParams == null)
                return;

            if (integerLongitude == -1 || integerLatitude == -1)
                return;

            // Get coordinates and pixel offsets based on current zoom level
            int croppedLongitude = integerLongitude >> BITRES - zoomLevel;
            int croppedLatitude = integerLatitude >> BITRES - zoomLevel;
            int xPixelOffset = (integerLongitude >> BITRES - zoomLevel - 8) % 256;
            int yPixelOffset = (integerLatitude >> BITRES - zoomLevel - 8) % 256;

            // Prepare for the loop
            string uriTemplate = (mapStyle == MapStyle.Road ? roadParams : aerialParams).UriTemplate;
            int index = 0;
            int maxValue = (1 << zoomLevel) - 1;

            // Loop through the array of Image elements
            for (int row = -sqrtNumTiles / 2; row <= sqrtNumTiles / 2; row++)
                for (int col = -sqrtNumTiles / 2; col <= sqrtNumTiles / 2; col++)
                {
                    // Get the Image and BitmapImage
                    Image image = imageCanvas.Children[index] as Image;
                    BitmapImage bitmap = image.Source as BitmapImage;
                    index++;

                    // Check if we've gone beyond the bounds
                    if (croppedLongitude + col < 0 ||
                        croppedLongitude + col > maxValue ||
                        croppedLatitude + row < 0 ||
                        croppedLatitude + row > maxValue)
                    {
                        bitmap.UriSource = null;
                    }
                    else
                    {
                        // Calculate a quadkey and set URI to bitmap
                        int longitude = croppedLongitude + col;
                        int latitude = croppedLatitude + row;
                        string strQuadkey = ToQuadKey(longitude, latitude, zoomLevel);
                        string uri = uriTemplate.Replace("{quadkey}", strQuadkey);
                        bitmap.UriSource = new Uri(uri);
                    }

                    // Position the Image element
                    Canvas.SetLeft(image, col * 256 - xPixelOffset);
                    Canvas.SetTop(image, row * 256 - yPixelOffset);
                }
        }

        string ToQuadKey(int longitude, int latitude, int level)
        {
            long quadkey = 0;
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

            strBuilder.Clear();

            for (int i = 0; i < level; i++)
            {
                strBuilder.Insert(0, (quadkey & 3).ToString());
                quadkey >>= 2;
            }

            return strBuilder.ToString();
        }

        void OnStreetViewAppBarButtonChecked(object sender, RoutedEventArgs args)
        {
            ToggleButton btn = sender as ToggleButton;
            ViewParams viewParams = null;

            if (btn.IsChecked.Value)
            {
                mapStyle = MapStyle.Road;
                viewParams = roadParams;
            }
            else
            {
                mapStyle = MapStyle.Aerial;
                viewParams = aerialParams;
            }

            zoomLevel = Math.Max(viewParams.MinimumLevel, 
                        Math.Min(viewParams.MaximumLevel, zoomLevel));

            RefreshDisplay();
            RefreshButtons();
        }

        void OnZoomInAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            zoomLevel += 1;
            RefreshDisplay();
            RefreshButtons();
        }

        void OnZoomOutAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            zoomLevel -= 1;
            RefreshDisplay();
            RefreshButtons();
        }

        void RefreshButtons()
        {
            ViewParams viewParams = streetViewAppBarButton.IsChecked.Value ? roadParams : aerialParams;
            zoomInAppBarButton.IsEnabled = zoomLevel < viewParams.MaximumLevel;
            zoomOutAppBarButton.IsEnabled = zoomLevel > viewParams.MinimumLevel;
        }
    }
}
