using System;
using Windows.Devices.Sensors;
using Windows.Graphics.Display;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace AxisAngleRotation
{
    public sealed partial class MainPage : Page
    {
        Inclinometer inclinometer = Inclinometer.GetDefault();
        OrientationSensor orientationSensor = OrientationSensor.GetDefault();

        public MainPage()
        {
            this.InitializeComponent();
            DisplayProperties.AutoRotationPreferences = DisplayProperties.NativeOrientation;
            Loaded += OnMainPageLoaded;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            if (inclinometer == null)
            {
                await new MessageDialog("Inclinometer is not available").ShowAsync();    
            }
            else
            {
                // Start the Inclinometer events
                ShowYawPitchRoll(inclinometer.GetCurrentReading());
                inclinometer.ReadingChanged += OnInclinometerReadingChanged;
            }

            if (orientationSensor == null)
            {
                await new MessageDialog("OrientationSensor is not available").ShowAsync();
            }
            else
            {
                // Start the OrientationSensor events
                ShowOrientation(orientationSensor.GetCurrentReading());
                orientationSensor.ReadingChanged += OrientationSensorChanged;
            }
        }

        async void OnInclinometerReadingChanged(Inclinometer sender, 
                                                InclinometerReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    ShowYawPitchRoll(args.Reading);
                });
        }

        void ShowYawPitchRoll(InclinometerReading inclinometerReading)
        {
            if (inclinometerReading == null)
                return;

            yawText.Text = inclinometerReading.YawDegrees.ToString("F0") + "°";
            pitchText.Text = inclinometerReading.PitchDegrees.ToString("F0") + "°";
            rollText.Text = inclinometerReading.RollDegrees.ToString("F0") + "°";
        }

        async void OrientationSensorChanged(OrientationSensor sender, 
                                            OrientationSensorReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    ShowOrientation(args.Reading);
                });
        }

        void ShowOrientation(OrientationSensorReading orientationReading)
        {
            if (orientationReading == null)
                return;

            SensorRotationMatrix matrix = orientationReading.RotationMatrix;

            if (matrix == null)
                return;

            m11Text.Text = matrix.M11.ToString("F3");
            m12Text.Text = matrix.M12.ToString("F3");
            m13Text.Text = matrix.M13.ToString("F3");

            m21Text.Text = matrix.M21.ToString("F3");
            m22Text.Text = matrix.M22.ToString("F3");
            m23Text.Text = matrix.M23.ToString("F3");

            m31Text.Text = matrix.M31.ToString("F3");
            m32Text.Text = matrix.M32.ToString("F3");
            m33Text.Text = matrix.M33.ToString("F3");

            // Convert rotation matrix to axis and angle
            double angle = Math.Acos((matrix.M11 + matrix.M22 + matrix.M33 - 1) / 2);
            angleText.Text = (180 * angle / Math.PI).ToString("F0");

            if (angle != 0)
            {
                double twoSine = 2 * Math.Sin(angle);
                double x = (matrix.M23 - matrix.M32) / twoSine;
                double y = (matrix.M31 - matrix.M13) / twoSine;
                double z = (matrix.M12 - matrix.M21) / twoSine;

                axisText.Text = String.Format("({0:F2} {1:F2} {2:F2})", x, y, z);
            }
        }
    }
}
