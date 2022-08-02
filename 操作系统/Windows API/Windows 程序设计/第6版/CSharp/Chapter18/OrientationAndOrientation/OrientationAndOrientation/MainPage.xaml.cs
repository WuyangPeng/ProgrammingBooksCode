using System;
using Windows.Devices.Sensors;
using Windows.Graphics.Display;
using Windows.UI.Core;
using Windows.UI.Xaml.Controls;

namespace OrientationAndOrientation
{
    public sealed partial class MainPage : Page
    {
        SimpleOrientationSensor simpleOrientationSensor = SimpleOrientationSensor.GetDefault();

        public MainPage()
        {
            this.InitializeComponent();

            // SimpleOrientationSensor initialization
            if (simpleOrientationSensor != null)
            {
                SetOrientationSensorText(simpleOrientationSensor.GetCurrentOrientation());
                simpleOrientationSensor.OrientationChanged += OnSimpleOrientationChanged;
            }

            // DisplayProperties initialization
            SetDisplayOrientationText(DisplayProperties.CurrentOrientation);
            DisplayProperties.OrientationChanged += OnDisplayPropertiesOrientationChanged;
        }

        // SimpleOrientationSensor handler
        async void OnSimpleOrientationChanged(SimpleOrientationSensor sender, 
                                              SimpleOrientationSensorOrientationChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    SetOrientationSensorText(args.Orientation);
                });
        }

        void SetOrientationSensorText(SimpleOrientation simpleOrientation)
        {
            orientationSensorTextBlock.Text = simpleOrientation.ToString();
        }

        // DisplayProperties handler
        void OnDisplayPropertiesOrientationChanged(object sender)
        {
            SetDisplayOrientationText(DisplayProperties.CurrentOrientation);
        }

        void SetDisplayOrientationText(DisplayOrientations displayOrientation)
        {
            displayOrientationTextBlock.Text = displayOrientation.ToString();
        }
    }
}
