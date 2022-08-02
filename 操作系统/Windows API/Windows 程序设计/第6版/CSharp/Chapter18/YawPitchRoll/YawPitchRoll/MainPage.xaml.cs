using System;
using Windows.Devices.Sensors;
using Windows.Foundation;
using Windows.Graphics.Display;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace YawPitchRoll
{
    public sealed partial class MainPage : Page
    {
        Inclinometer inclinometer = Inclinometer.GetDefault();

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
                await new MessageDialog("Cannot obtain Inclinometer").ShowAsync();    
            }
            else
            {
                ShowYawPitchRoll(inclinometer.GetCurrentReading());
                inclinometer.ReportInterval = inclinometer.MinimumReportInterval;
                inclinometer.ReadingChanged += OnInclinometerReadingChanged;
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

            double yaw = inclinometerReading.YawDegrees;
            double pitch = inclinometerReading.PitchDegrees;
            double roll = inclinometerReading.RollDegrees;

            yawValue.Text = yaw.ToString("F0") + "°";
            pitchValue.Text = pitch.ToString("F0") + "°";
            rollValue.Text = roll.ToString("F0") + "°";

            yawRotate.Angle = yaw;

            if (pitch <= 90 && pitch >= -90)
            {
                pitchPath.Fill = pitchPath.Stroke;
                pitchEllipse.Center = new Point(this.ActualWidth / 2,
                                                this.ActualHeight * (pitch + 90) / 180);
            }
            else
            {
                pitchPath.Fill = null;

                if (pitch > 90)
                    pitchEllipse.Center = new Point(this.ActualWidth / 2,
                                                    this.ActualHeight * (270 - pitch) / 180);
                else // pitch < -90
                    pitchEllipse.Center = new Point(this.ActualWidth / 2,
                                                    this.ActualHeight * (-90 - pitch) / 180);
            }
            rollEllipse.Center = new Point(this.ActualWidth * (roll + 90) / 180,
                                           this.ActualHeight / 2);
        }
    }
}
