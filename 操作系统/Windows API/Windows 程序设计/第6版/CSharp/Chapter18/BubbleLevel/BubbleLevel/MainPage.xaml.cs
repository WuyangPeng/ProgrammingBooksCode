using System;
using Windows.Devices.Sensors;
using Windows.Graphics.Display;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace BubbleLevel
{
    public sealed partial class MainPage : Page
    {
        Accelerometer accelerometer = Accelerometer.GetDefault();

        public MainPage()
        {
            this.InitializeComponent();
            DisplayProperties.AutoRotationPreferences = DisplayProperties.NativeOrientation;
            Loaded += OnMainPageLoaded;
            SizeChanged += OnMainPageSizeChanged;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            if (accelerometer != null)
            {
                accelerometer.ReportInterval = accelerometer.MinimumReportInterval;
                SetBubble(accelerometer.GetCurrentReading());
                accelerometer.ReadingChanged += OnAccelerometerReadingChanged;
            }
            else
            {
                await new MessageDialog("Accelerometer is not available").ShowAsync();
            }
        }

        void OnMainPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            double size = Math.Min(args.NewSize.Width, args.NewSize.Height);
            outerCircle.Width = size;
            outerCircle.Height = size;
            halfCircle.Width = size / 2;
            halfCircle.Height = size / 2;
        }

        async void OnAccelerometerReadingChanged(Accelerometer sender, 
                                                 AccelerometerReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () => 
            { 
                SetBubble(args.Reading); 
            });
        }

        void SetBubble(AccelerometerReading accelerometerReading)
        {
            if (accelerometerReading == null)
                return;

            double x = accelerometerReading.AccelerationX;
            double y = accelerometerReading.AccelerationY;

            bubbleTranslate.X = -x * centeredGrid.ActualWidth / 2;
            bubbleTranslate.Y = y * centeredGrid.ActualHeight / 2;
        }
    }
}
