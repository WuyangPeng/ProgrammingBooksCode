using System;
using Windows.Devices.Geolocation;
using Windows.Foundation;
using Windows.UI.Xaml.Controls;

namespace XYSliderDemo
{
    public sealed partial class MainPage : Page
    {
        bool manualChange = false;

        public MainPage()
        {
            this.InitializeComponent();

            // Initialize position of cross-hair in XYSlider
            Loaded += async (sender, args) =>
                {
                    Geolocator geolocator = new Geolocator();

                    // Might not have permission!
                    try
                    {
                        Geoposition position = await geolocator.GetGeopositionAsync();

                        if (!manualChange)
                        {
                            double x = (position.Coordinate.Longitude + 180) / 360;
                            double y = (90 - position.Coordinate.Latitude) / 180;
                            xySlider.Value = new Point(x, y);
                        }
                    }
                    catch
                    {
                    }
                };
        }

        void OnXYSliderValueChanged(object sender, Point point)
        {
            double longitude = 360 * point.X - 180;
            double latitude = 90 - 180 * point.Y;
            label.Text = String.Format("Longitude: {0:F0} Latitude: {1:F0}",
                                       longitude, latitude);
            manualChange = true;
        }
    }
}
