using System;
using Windows.Devices.Sensors;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace AccelerometerAndSimpleOrientation
{
    public sealed partial class MainPage : Page
    {
        Accelerometer accelerometer = Accelerometer.GetDefault();
        SimpleOrientationSensor simpleOrientationSensor = SimpleOrientationSensor.GetDefault();

        public MainPage()
        {
            this.InitializeComponent();
            this.Loaded += OnMainPageLoaded;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            if (accelerometer == null)
                await new MessageDialog("Cannot start Accelerometer").ShowAsync();

            if (simpleOrientationSensor == null)
                await new MessageDialog("Cannot start SimpleOrientationSensor").ShowAsync();
        }

        // Attach event handlers
        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            if (accelerometer != null)
            {
                SetAccelerometerText(accelerometer.GetCurrentReading());
                accelerometer.ReadingChanged += OnAccelerometerReadingChanged;
            }

            if (simpleOrientationSensor != null)
            {
                SetSimpleOrientationText(simpleOrientationSensor.GetCurrentOrientation());
                simpleOrientationSensor.OrientationChanged += OnSimpleOrientationChanged;
            }
            base.OnNavigatedTo(args);
        }

        // Detach event handlers
        protected override void OnNavigatedFrom(NavigationEventArgs args)
        {
            if (accelerometer != null)
                accelerometer.ReadingChanged -= OnAccelerometerReadingChanged;

            if (simpleOrientationSensor != null)
                simpleOrientationSensor.OrientationChanged -= OnSimpleOrientationChanged;

            base.OnNavigatedFrom(args);
        }

        // Accelerometer handler
        async void OnAccelerometerReadingChanged(Accelerometer sender, 
                                                 AccelerometerReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    SetAccelerometerText(args.Reading);
                });
        }

        void SetAccelerometerText(AccelerometerReading accelerometerReading)
        {
            if (accelerometerReading == null)
                return;

            accelerometerX.Text = accelerometerReading.AccelerationX.ToString("F2");
            accelerometerY.Text = accelerometerReading.AccelerationY.ToString("F2");
            accelerometerZ.Text = accelerometerReading.AccelerationZ.ToString("F2");
            magnitude.Text = 
                Math.Sqrt(Math.Pow(accelerometerReading.AccelerationX, 2) +
                          Math.Pow(accelerometerReading.AccelerationY, 2) +
                          Math.Pow(accelerometerReading.AccelerationZ, 2)).ToString("F2");
        }

        // SimpleOrientationSensor handler
        async void OnSimpleOrientationChanged(SimpleOrientationSensor sender, 
                                              SimpleOrientationSensorOrientationChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    SetSimpleOrientationText(args.Orientation);
                });
        }

        void SetSimpleOrientationText(SimpleOrientation simpleOrientation)
        {
            this.simpleOrientation.Text = simpleOrientation.ToString();
        }
    }
}
