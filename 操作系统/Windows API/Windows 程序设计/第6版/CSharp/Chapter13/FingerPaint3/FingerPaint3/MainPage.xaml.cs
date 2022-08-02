using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.System;
using Windows.UI;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Shapes;

namespace FingerPaint3
{
    public sealed partial class MainPage : Page
    {
        Dictionary<uint, Polyline> pointerDictionary = new Dictionary<uint, Polyline>();
        Random rand = new Random();
        byte[] rgb = new byte[3];

        public MainPage()
        {
            this.InitializeComponent();
            this.IsTabStop = true;
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
                StrokeThickness = 24
            };
            polyline.PointerPressed += OnPolylinePointerPressed;
            polyline.RightTapped += OnPolylineRightTapped;
            polyline.Points.Add(point);

            // Add to Grid
            contentGrid.Children.Add(polyline);

            // Add to dictionary
            pointerDictionary.Add(id, polyline);

            // Capture the Pointer
            CapturePointer(args.Pointer);

            // Set input focus
            Focus(FocusState.Programmatic);

            base.OnPointerPressed(args);
        }

        void OnPolylinePointerPressed(object sender, PointerRoutedEventArgs args)
        {
            args.Handled = true;
        }

        async void OnPolylineRightTapped(object sender, RightTappedRoutedEventArgs args)
        {
            Polyline polyline = sender as Polyline;
            PopupMenu popupMenu = new PopupMenu();
            popupMenu.Commands.Add(new UICommand("Change color", OnMenuChangeColor, polyline));
            popupMenu.Commands.Add(new UICommand("Delete", OnMenuDelete, polyline));
            await popupMenu.ShowAsync(args.GetPosition(this));
        }

        void OnMenuChangeColor(IUICommand command)
        {
            Polyline polyline = command.Id as Polyline;
            rand.NextBytes(rgb);
            Color color = Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);
            (polyline.Stroke as SolidColorBrush).Color = color;
        }

        void OnMenuDelete(IUICommand command)
        {
            Polyline polyline = command.Id as Polyline;
            contentGrid.Children.Remove(polyline);
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

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is in dictionary, abandon the drawing operation
            if (pointerDictionary.ContainsKey(id))
            {
                contentGrid.Children.Remove(pointerDictionary[id]);
                pointerDictionary.Remove(id);
            }

            base.OnPointerCaptureLost(args);
        }

        protected override void OnKeyDown(KeyRoutedEventArgs args)
        {
            if (args.Key == VirtualKey.Escape)
                ReleasePointerCaptures();

            base.OnKeyDown(args);
        }
    }
}
