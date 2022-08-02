using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Input;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace FingerPaint4
{
    public sealed partial class MainPage : Page
    {
        struct PointerInfo
        {
            public Brush Brush;
            public Point PreviousPoint;
        }

        Dictionary<uint, PointerInfo> pointerDictionary = new Dictionary<uint, PointerInfo>();
        Random rand = new Random();
        byte[] rgb = new byte[3];

        public MainPage()
        {
            this.InitializeComponent();
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(this).Position;

            // Create random color
            rand.NextBytes(rgb);
            Color color = Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);

            // Create PointerInfo
            PointerInfo pointerInfo = new PointerInfo
            {
                PreviousPoint = point,
                Brush = new SolidColorBrush(color)
            };

            // Add to dictionary
            pointerDictionary.Add(id, pointerInfo);

            // Capture the Pointer
            CapturePointer(args.Pointer);

            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get ID from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is in dictionary, start a loop
            if (pointerDictionary.ContainsKey(id))
            {
                PointerInfo pointerInfo = pointerDictionary[id];
                IList<PointerPoint> pointerpoints = args.GetIntermediatePoints(this);

                for (int i = pointerpoints.Count - 1; i >= 0; i--)
                {
                    PointerPoint pointerPoint = pointerpoints[i];

                    // For each point, create a new Line element and add to Grid
                    Point point = pointerPoint.Position;
                    float pressure = pointerPoint.Properties.Pressure;

                    Line line = new Line
                    {
                        X1 = pointerInfo.PreviousPoint.X,
                        Y1 = pointerInfo.PreviousPoint.Y,
                        X2 = point.X,
                        Y2 = point.Y,
                        Stroke = pointerInfo.Brush,
                        StrokeThickness = pressure * 24,
                        StrokeStartLineCap = PenLineCap.Round,
                        StrokeEndLineCap = PenLineCap.Round
                    };
                    contentGrid.Children.Add(line);

                    // Update PointerInfo 
                    pointerInfo.PreviousPoint = point;
                }
                // Store PointerInfo back in dictionary
                pointerDictionary[id] = pointerInfo;
            }
            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is in dictionary, remove it
            if (pointerDictionary.ContainsKey(id))
                pointerDictionary.Remove(id);

            base.OnPointerReleased(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is still in dictionary, remove it
            if (pointerDictionary.ContainsKey(id))
                pointerDictionary.Remove(id);

            base.OnPointerCaptureLost(args);
        }
    }
}
