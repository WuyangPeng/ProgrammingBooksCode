using System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;

namespace XamlCruncher
{
    public sealed partial class SplitContainer : UserControl
    {
        // Static constructor and properties
        static SplitContainer()
        {
            Child1Property = 
                DependencyProperty.Register("Child1",
                    typeof(UIElement), typeof(SplitContainer), 
                    new PropertyMetadata(null, OnChildChanged));

            Child2Property = 
                DependencyProperty.Register("Child2",
                    typeof(UIElement), typeof(SplitContainer),
                    new PropertyMetadata(null, OnChildChanged));

            OrientationProperty = 
                DependencyProperty.Register("Orientation",
                    typeof(Orientation), typeof(SplitContainer),
                    new PropertyMetadata(Orientation.Horizontal, OnOrientationChanged));

            SwapChildrenProperty =
                DependencyProperty.Register("SwapChildren",
                    typeof(bool), typeof(SplitContainer),
                    new PropertyMetadata(false, OnSwapChildrenChanged));

            MinimumSizeProperty =
                DependencyProperty.Register("MinimumSize",
                    typeof(double), typeof(SplitContainer),
                    new PropertyMetadata(100.0, OnMinSizeChanged));
        }

        public static DependencyProperty Child1Property { private set; get; }
        public static DependencyProperty Child2Property { private set; get; }
        public static DependencyProperty OrientationProperty { private set; get; }
        public static DependencyProperty SwapChildrenProperty { private set; get; }
        public static DependencyProperty MinimumSizeProperty { private set; get; }

        // Instance constructor and properties
        public SplitContainer()
        {
            this.InitializeComponent();
        }

        public UIElement Child1
        {
            set { SetValue(Child1Property, value); }
            get { return (UIElement)GetValue(Child1Property); }
        }

        public UIElement Child2
        {
            set { SetValue(Child2Property, value); }
            get { return (UIElement)GetValue(Child2Property); }
        }

        public Orientation Orientation
        {
            set { SetValue(OrientationProperty, value); }
            get { return (Orientation)GetValue(OrientationProperty); }
        }

        public bool SwapChildren
        {
            set { SetValue(SwapChildrenProperty, value); }
            get { return (bool)GetValue(SwapChildrenProperty); }
        }

        public double MinimumSize
        {
            set { SetValue(MinimumSizeProperty, value); }
            get { return (double)GetValue(MinimumSizeProperty); }
        }

        // Property changed handlers
        static void OnChildChanged(DependencyObject obj, 
                                   DependencyPropertyChangedEventArgs args)
        {
            (obj as SplitContainer).OnChildChanged(args);
        }

        void OnChildChanged(DependencyPropertyChangedEventArgs args)
        {
            Grid targetGrid = (args.Property == Child1Property ^ this.SwapChildren) ? grid1 : grid2;
            targetGrid.Children.Clear();

            if (args.NewValue != null)
                targetGrid.Children.Add(args.NewValue as UIElement);
        }

        static void OnOrientationChanged(DependencyObject obj, 
                                         DependencyPropertyChangedEventArgs args)
        {
            (obj as SplitContainer).OnOrientationChanged((Orientation)args.OldValue, 
                                                         (Orientation)args.NewValue);
        }

        void OnOrientationChanged(Orientation oldOrientation, Orientation newOrientation)
        {
            // Shouldn't be necessary, but...
            if (newOrientation == oldOrientation)
                return;

            if (newOrientation == Orientation.Horizontal)
            {
                coldef1.Width = rowdef1.Height;
                coldef2.Width = rowdef2.Height;

                coldef1.MinWidth = this.MinimumSize;
                coldef2.MinWidth = this.MinimumSize;

                rowdef1.Height = new GridLength(1, GridUnitType.Star);
                rowdef2.Height = new GridLength(0);

                rowdef1.MinHeight = 0;
                rowdef2.MinHeight = 0;

                thumb.Width = 12;
                thumb.Height = Double.NaN;

                Grid.SetRow(thumb, 0);
                Grid.SetColumn(thumb, 1);

                Grid.SetRow(grid2, 0);
                Grid.SetColumn(grid2, 2);
            }
            else
            {
                rowdef1.Height = coldef1.Width;
                rowdef2.Height = coldef2.Width;

                rowdef1.MinHeight = this.MinimumSize;
                rowdef2.MinHeight = this.MinimumSize;

                coldef1.Width = new GridLength(1, GridUnitType.Star);
                coldef2.Width = new GridLength(0);

                coldef1.MinWidth = 0;
                coldef2.MinWidth = 0;

                thumb.Height = 12;
                thumb.Width = Double.NaN;

                Grid.SetRow(thumb, 1);
                Grid.SetColumn(thumb, 0);

                Grid.SetRow(grid2, 2);
                Grid.SetColumn(grid2, 0);
            }
        }

        static void OnSwapChildrenChanged(DependencyObject obj, 
                                          DependencyPropertyChangedEventArgs args)
        {
            (obj as SplitContainer).OnSwapChildrenChanged((bool)args.OldValue, 
                                                          (bool)args.NewValue);
        }

        void OnSwapChildrenChanged(bool oldOrientation, bool newOrientation)
        {
            grid1.Children.Clear();
            grid2.Children.Clear();

            grid1.Children.Add(newOrientation ? this.Child2 : this.Child1);
            grid2.Children.Add(newOrientation ? this.Child1 : this.Child2);
        }

        static void OnMinSizeChanged(DependencyObject obj, 
                                     DependencyPropertyChangedEventArgs args)
        {
            (obj as SplitContainer).OnMinSizeChanged((double)args.OldValue, 
                                                     (double)args.NewValue);
        }

        void OnMinSizeChanged(double oldValue, double newValue)
        {
            if (this.Orientation == Orientation.Horizontal)
            {
                coldef1.MinWidth = newValue;
                coldef2.MinWidth = newValue;
            }
            else
            {
                rowdef1.MinHeight = newValue;
                rowdef2.MinHeight = newValue;
            }
        }

        // Thumb event handlers
        void OnThumbDragStarted(object sender, DragStartedEventArgs args)
        {
            if (this.Orientation == Orientation.Horizontal)
            {
                coldef1.Width = new GridLength(coldef1.ActualWidth, GridUnitType.Star);
                coldef2.Width = new GridLength(coldef2.ActualWidth, GridUnitType.Star);
            }
            else
            {
                rowdef1.Height = new GridLength(rowdef1.ActualHeight, GridUnitType.Star);
                rowdef2.Height = new GridLength(rowdef2.ActualHeight, GridUnitType.Star);
            }
        }

        void OnThumbDragDelta(object sender, DragDeltaEventArgs args)
        {
            if (this.Orientation == Orientation.Horizontal)
            {
                double newWidth1 = Math.Max(0, coldef1.Width.Value + args.HorizontalChange);
                double newWidth2 = Math.Max(0, coldef2.Width.Value - args.HorizontalChange);

                coldef1.Width = new GridLength(newWidth1, GridUnitType.Star);
                coldef2.Width = new GridLength(newWidth2, GridUnitType.Star);
            }
            else
            {
                double newHeight1 = Math.Max(0, rowdef1.Height.Value + args.VerticalChange);
                double newHeight2 = Math.Max(0, rowdef2.Height.Value - args.VerticalChange);

                rowdef1.Height = new GridLength(newHeight1, GridUnitType.Star);
                rowdef2.Height = new GridLength(newHeight2, GridUnitType.Star);
            }
        }
    }
}
