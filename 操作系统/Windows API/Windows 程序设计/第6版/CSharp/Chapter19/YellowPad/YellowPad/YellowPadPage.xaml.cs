using System.Collections.Generic;
using System.Linq;
using Windows.Devices.Input;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Input;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace YellowPad
{
    public sealed partial class YellowPadPage : UserControl
    {
        static readonly DependencyProperty inkFileManagerProperty =
            DependencyProperty.Register("InkFileManager",
                                typeof(InkFileManager),
                                typeof(YellowPadPage),
                                new PropertyMetadata(null, OnInkFileManagerChanged));

        Dictionary<uint, Point> pointerDictionary = new Dictionary<uint, Point>();
        Brush selectionBrush = new SolidColorBrush(Colors.Red);

        public YellowPadPage()
        {
            this.InitializeComponent();

            // Draw horizontal lines in blue
            Brush blueBrush = new SolidColorBrush(Colors.Blue);

            for (int y = 120; y < sheetPanel.Height; y += 24)
                sheetPanel.Children.Add(new Line
                {
                    X1 = 0,
                    Y1 = y,
                    X2 = sheetPanel.Width,
                    Y2 = y,
                    Stroke = blueBrush
                });
        }

        // Overhead for InkFileManager dependency property
        public static DependencyProperty InkFileManagerProperty
        {
            get { return inkFileManagerProperty; }
        }

        public InkFileManager InkFileManager
        {
            set { SetValue(InkFileManagerProperty, value); }
            get { return (InkFileManager)GetValue(InkFileManagerProperty); }
        }

        static void OnInkFileManagerChanged(DependencyObject obj, 
                                            DependencyPropertyChangedEventArgs args)
        {
            (obj as YellowPadPage).OnInkFileManagerChanged(args);
        }

        async void OnInkFileManagerChanged(DependencyPropertyChangedEventArgs args)
        {
            contentGrid.Children.Clear();
            newLineGrid.Children.Clear();

            if (args.NewValue != null)
            {
                await this.InkFileManager.LoadAsync();
                this.InkFileManager.RenderTarget = contentGrid;
                this.InkFileManager.RenderAll();
            }
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            if (args.Pointer.PointerDeviceType == PointerDeviceType.Pen)
            {
                // Get information
                PointerPoint pointerPoint = args.GetCurrentPoint(sheetPanel);
                uint id = pointerPoint.PointerId;
                InkManager inkManager = this.InkFileManager.InkManager;

                // Initialize for inking, erasing, or selecting
                if (pointerPoint.Properties.IsEraser)
                {
                    inkManager.Mode = InkManipulationMode.Erasing;
                    this.InkFileManager.UnselectAll();
                }
                else if (pointerPoint.Properties.IsBarrelButtonPressed)
                {
                    inkManager.Mode = InkManipulationMode.Selecting;

                    // Create Polyline for showing enclosure
                    Polyline polyline = new Polyline
                    {
                        Stroke = selectionBrush,
                        StrokeThickness = 1
                    };
                    polyline.Points.Add(pointerPoint.Position);
                    newLineGrid.Children.Add(polyline);
                }
                else
                {
                    inkManager.Mode = InkManipulationMode.Inking;
                    this.InkFileManager.UnselectAll();
                }

                // Give PointerPoint to InkManager
                inkManager.ProcessPointerDown(pointerPoint);

                // Add an entry to the dictionary
                pointerDictionary.Add(args.Pointer.PointerId, pointerPoint.Position);

                // Capture the pointer
                this.CapturePointer(args.Pointer);
            }
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get information
            PointerPoint pointerPoint = args.GetCurrentPoint(sheetPanel);
            uint id = pointerPoint.PointerId;
            InkManager inkManager = this.InkFileManager.InkManager;
            InkDrawingAttributes inkDrawingAttributes =
                                    this.InkFileManager.InkDrawingAttributes;

            if (pointerDictionary.ContainsKey(id))
            {
                foreach (PointerPoint point in args.GetIntermediatePoints(sheetPanel).Reverse())
                {
                    Point point1 = pointerDictionary[id];
                    Point point2 = pointerPoint.Position;

                    // Give PointerPoint to InkManager
                    object obj = inkManager.ProcessPointerUpdate(point);

                    if (inkManager.Mode == InkManipulationMode.Erasing)
                    {
                        // See if something has actually been removed
                        Rect rect = (Rect)obj;

                        if (rect.Width != 0 && rect.Height != 0)
                        {
                            this.InkFileManager.RenderAll();
                        }
                    }
                    else if (inkManager.Mode == InkManipulationMode.Selecting)
                    {
                        Polyline polyline = newLineGrid.Children[0] as Polyline;
                        polyline.Points.Add(point2);
                    }
                    else // inkManager.Mode == InkManipulationMode.Inking
                    {
                        // Render the line
                        Line line = new Line
                        {
                            X1 = point1.X,
                            Y1 = point1.Y,
                            X2 = point2.X,
                            Y2 = point2.Y,
                            Stroke = new SolidColorBrush(inkDrawingAttributes.Color),
                            StrokeThickness = inkDrawingAttributes.Size.Width *
                                              pointerPoint.Properties.Pressure,
                            StrokeStartLineCap = PenLineCap.Round,
                            StrokeEndLineCap = PenLineCap.Round
                        };
                        newLineGrid.Children.Add(line);
                    }
                    pointerDictionary[id] = point2;
                }
            }
            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            // Get information
            PointerPoint pointerPoint = args.GetCurrentPoint(sheetPanel);
            uint id = pointerPoint.PointerId;
            InkManager inkManager = this.InkFileManager.InkManager;

            if (pointerDictionary.ContainsKey(id))
            {
                // Give PointerPoint to InkManager
                inkManager.ProcessPointerUp(pointerPoint);

                if (inkManager.Mode == InkManipulationMode.Inking)
                {
                    // Get rid of the little line segments
                    newLineGrid.Children.Clear();

                    // Render the new stroke
                    IReadOnlyList<InkStroke> inkStrokes = inkManager.GetStrokes();
                    InkStroke inkStroke = inkStrokes[inkStrokes.Count - 1];
                    this.InkFileManager.RenderStroke(inkStroke);
                }
                else if (inkManager.Mode == InkManipulationMode.Selecting)
                {
                    // Get rid of the enclosure line
                    newLineGrid.Children.Clear();

                    // Render everything so selected items are identified
                    this.InkFileManager.RenderAll();
                }
                pointerDictionary.Remove(id);
            }
            base.OnPointerReleased(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (pointerDictionary.ContainsKey(id))
            {
                pointerDictionary.Remove(id);
                newLineGrid.Children.Clear();
                this.InkFileManager.RenderAll();
            }
        }
    }
}
