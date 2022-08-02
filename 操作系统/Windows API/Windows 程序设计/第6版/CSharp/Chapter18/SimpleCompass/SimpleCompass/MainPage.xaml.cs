using System;
using Windows.Devices.Sensors;
using Windows.Graphics.Display;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace SimpleCompass
{
    public sealed partial class MainPage : Page
    {
        Compass compass = Compass.GetDefault();

        public MainPage()
        {
            this.InitializeComponent();
            DisplayProperties.AutoRotationPreferences = DisplayProperties.NativeOrientation;
            Loaded += OnMainPageLoaded;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            if (compass != null)
            {
                ShowCompassValues(compass.GetCurrentReading());
                compass.ReportInterval = compass.MinimumReportInterval;
                compass.ReadingChanged += OnCompassReadingChanged;
            }
            else
            {
                await new MessageDialog("Compass is not available").ShowAsync();
            }
        }

        async void OnCompassReadingChanged(Compass sender, CompassReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    ShowCompassValues(args.Reading);
                });
        }

        void ShowCompassValues(CompassReading compassReading)
        {
            if (compassReading == null)
                return;

            magNorthRotate.Angle = -compassReading.HeadingMagneticNorth;

            if (compassReading.HeadingTrueNorth.HasValue)
            {
                trueNorthPath.Visibility = Visibility.Visible;
                trueNorthRotate.Angle = -compassReading.HeadingTrueNorth.Value;
            }
            else
            {
                trueNorthPath.Visibility = Visibility.Collapsed;
            }
        }
    }
}
