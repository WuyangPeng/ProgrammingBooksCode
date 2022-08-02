using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace FingerPaint1
{
    public sealed partial class MainPage : Page
    {
        Dictionary<uint, Polyline> pointerDictionary = new Dictionary<uint, Polyline>();
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

            // Create Polyline
            Polyline polyline = new Polyline
            {
                Stroke = new SolidColorBrush(color),
                StrokeThickness = 24,
            };
            polyline.Points.Add(point);

            // Add to Grid
            contentGrid.Children.Add(polyline);

            // Add to dictionary
            pointerDictionary.Add(id, polyline);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(this).Position;

            // If ID is in dictionary, add the point to the Polyline
            if (pointerDictionary.ContainsKey(id))
                pointerDictionary[id].Points.Add(point);

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
    }
}
