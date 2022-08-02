using System;
using Windows.Devices.Sensors;
using Windows.Graphics.Display;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media.Animation;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Media.Media3D;

using Petzold.Windows8.VectorDrawing;

namespace EarthlyDelights
{
    public sealed partial class MainPage : Page
    {
        // Dependency property for zoom-in transition animation
        static readonly DependencyProperty interpolationFactorProperty =
            DependencyProperty.Register("InterpolationFactor",
                                        typeof(double),
                                        typeof(MainPage),
                                        new PropertyMetadata(0.0, OnInterpolationFactorChanged));

        OrientationSensor orientationSensor = OrientationSensor.GetDefault();
        double pageWidth, pageHeight, maxDimension;
        int imageWidth, imageHeight;
        string title = "The Garden of Earthly Delights by Hieronymus Bosch";
        double zoomInScale;
        double rotation;
        bool isZoomView;

        public MainPage()
        {
            this.InitializeComponent();
            DisplayProperties.AutoRotationPreferences = DisplayProperties.NativeOrientation;
            Loaded += OnMainPageLoaded;
            SizeChanged += OnMainPageSizeChanged;
        }

        // Interpolation Factor property
        public static DependencyProperty InterpolationFactorProperty
        {
            get { return interpolationFactorProperty; }
        }

        public double InterpolationFactor
        {
            set { SetValue(InterpolationFactorProperty, value); }
            get { return (double)GetValue(InterpolationFactorProperty); }
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            if (orientationSensor == null)
            {
                await new MessageDialog("OrientationSensor is not available",
                                        "Earthly Delights").ShowAsync();

                progressBar.Visibility = Visibility.Collapsed;
                statusText.Visibility = Visibility.Collapsed;
            }
            else
            {
                bitmapImage.UriSource =
                  new Uri("http://upload.wikimedia.org/wikipedia/commons/6/62/The_Garden_of_Earthly_Delights_by_Bosch_High_Resolution_2.jpg");
            }
        }

        void OnMainPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            // Save the page dimensions
            pageWidth = this.ActualWidth;
            pageHeight = this.ActualHeight;
            maxDimension = Math.Max(pageWidth, pageHeight);

            // Initialize some values
            outlineBorder.Width = pageWidth;
            outlineBorder.Height = pageHeight;
            borderTransform.CenterX = pageWidth / 2;
            borderTransform.CenterY = pageHeight / 2;
        }

        void OnBitmapImageDownloadProgress(object sender, DownloadProgressEventArgs args)
        {
            progressBar.Value = args.Progress;
        }

        async void OnBitmapImageFailed(object sender, ExceptionRoutedEventArgs args)
        {
            progressBar.Visibility = Visibility.Collapsed;
            statusText.Visibility = Visibility.Collapsed;

            await new MessageDialog("Could not download image: " + args.ErrorMessage,
                                    "Earthly Delights").ShowAsync();
        }

        void OnBitmapImageOpened(object sender, RoutedEventArgs args)
        {
            progressBar.Visibility = Visibility.Collapsed;
            statusText.Visibility = Visibility.Collapsed;

            // Save image dimensions
            imageWidth = bitmapImage.PixelWidth;
            imageHeight = bitmapImage.PixelHeight;
            titleText.Text = String.Format("{0} ({1}\x00D7{2})", title, imageWidth, imageHeight);

            // Initialize image transforms
            zoomInScale = Math.Min(pageWidth / imageWidth, pageHeight / imageHeight);

            // Start OrientationSensor going
            if (orientationSensor != null)
            {
                ProcessNewOrientationReading(orientationSensor.GetCurrentReading());
                orientationSensor.ReportInterval = orientationSensor.MinimumReportInterval;
                orientationSensor.ReadingChanged += OnOrientationSensorReadingChanged;
            }
        }

        async void OnOrientationSensorReadingChanged(OrientationSensor sender, 
                                                     OrientationSensorReadingChangedEventArgs args)
        {
            await this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
                {
                    ProcessNewOrientationReading(args.Reading);
                });
        }

        void ProcessNewOrientationReading(OrientationSensorReading orientationReading)
        {
            if (orientationReading == null)
                return;

            // Get the rotation matrix & convert to horizontal coordinates
            SensorRotationMatrix m = orientationReading.RotationMatrix;

            if (m == null)
                return;

            Matrix3D matrix3d = new Matrix3D(m.M11, m.M12, m.M13, 0,
                                             m.M21, m.M22, m.M23, 0,
                                             m.M31, m.M32, m.M33, 0,
                                             0, 0, 0, 1);
            if (!matrix3d.HasInverse)
                return;

            HorizontalCoordinate horzCoord = HorizontalCoordinate.FromMotionMatrix(matrix3d);

            // Set the transform center on the Image element
            imageTransform.CenterX = (imageWidth + maxDimension) *
                                        (180 + horzCoord.Azimuth) / 360 - maxDimension / 2;
            imageTransform.CenterY = (imageHeight + maxDimension) *
                                        (90 - horzCoord.Altitude) / 180 - maxDimension / 2;

            // Set the translation on the Border element
            borderTransform.TranslateX = imageTransform.CenterX - pageWidth / 2;
            borderTransform.TranslateY = imageTransform.CenterY - pageHeight / 2;

            // Get rotation from Tilt
            rotation = -horzCoord.Tilt;
            UpdateImageTransforms();
        }

        protected override void OnTapped(TappedRoutedEventArgs e)
        {
            // Animate the InterpolationFactor property
            DoubleAnimation doubleAnimation = new DoubleAnimation
            {
                EnableDependentAnimation = true,
                To = isZoomView ? 0 : 1,
                Duration = new Duration(TimeSpan.FromSeconds(1))
            };
            Storyboard.SetTarget(doubleAnimation, this);
            Storyboard.SetTargetProperty(doubleAnimation, "InterpolationFactor");
            Storyboard storyboard = new Storyboard();
            storyboard.Children.Add(doubleAnimation);
            storyboard.Begin();
            isZoomView ^= true;
            base.OnTapped(e);
        }

        static void OnInterpolationFactorChanged(DependencyObject obj,
                                                 DependencyPropertyChangedEventArgs args)
        {
            (obj as MainPage).UpdateImageTransforms();
        }

        void UpdateImageTransforms()
        {
            // If being zoomed out, set scaling
            double interpolatedScale = 1 + InterpolationFactor * (zoomInScale - 1);
            imageTransform.ScaleX =
            imageTransform.ScaleY = interpolatedScale;

            // Move transform center to screen center
            imageTransform.TranslateX = pageWidth / 2 - imageTransform.CenterX;
            imageTransform.TranslateY = pageHeight / 2 - imageTransform.CenterY;

            // If being zoomed out, adjust for scaling
            imageTransform.TranslateX -= InterpolationFactor *
                                (pageWidth / 2 - zoomInScale * imageTransform.CenterX);
            imageTransform.TranslateY -= InterpolationFactor *
                                (pageHeight / 2 - zoomInScale * imageTransform.CenterY);

            // If being zoomed out, center image in screen
            imageTransform.TranslateX += InterpolationFactor *
                                (pageWidth - zoomInScale * imageWidth) / 2;
            imageTransform.TranslateY += InterpolationFactor *
                                (pageHeight - zoomInScale * imageHeight) / 2;

            // Set border thickness
            outlineBorder.BorderThickness = new Thickness(2 / interpolatedScale);
            outlineRectangle.StrokeThickness = 2 / interpolatedScale;

            // Set rotation on image and border
            imageTransform.Rotation = (1 - InterpolationFactor) * rotation;
            borderTransform.Rotation = -rotation;
        }
    }
}
