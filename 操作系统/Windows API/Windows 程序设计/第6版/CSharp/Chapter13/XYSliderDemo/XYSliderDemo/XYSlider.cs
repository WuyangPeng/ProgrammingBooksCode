using System;
using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace XYSliderDemo
{
    public class XYSlider : ContentControl
    {
        ContentPresenter contentPresenter;
        FrameworkElement crossHairPart;

        static readonly DependencyProperty valueProperty = 
                DependencyProperty.Register("Value",
                        typeof(Point), typeof(XYSlider), 
                        new PropertyMetadata(new Point(0.5, 0.5), OnValueChanged));

        public event EventHandler<Point> ValueChanged;

        public XYSlider()
        {
            this.DefaultStyleKey = typeof(XYSlider);
        }

        public static DependencyProperty ValueProperty
        {
            get { return valueProperty; }
        }

        public Point Value
        {
            set { SetValue(ValueProperty, value); }
            get { return (Point)GetValue(ValueProperty); }
        }

        protected override void OnApplyTemplate()
        {
            // Detach event handlers
            if (contentPresenter != null)
            {
                contentPresenter.ManipulationStarted -= OnContentPresenterManipulationStarted;
                contentPresenter.ManipulationDelta -= OnContentPresenterManipulationDelta;
                contentPresenter.SizeChanged -= OnContentPresenterSizeChanged;
            }

            // Get new parts
            crossHairPart = GetTemplateChild("CrossHairPart") as FrameworkElement;
            contentPresenter = GetTemplateChild("ContentPresenterPart") as ContentPresenter;

            // Attach event handlers
            if (contentPresenter != null)
            {
                contentPresenter.ManipulationMode = ManipulationModes.TranslateX |
                                                    ManipulationModes.TranslateY;
                contentPresenter.ManipulationStarted += OnContentPresenterManipulationStarted;
                contentPresenter.ManipulationDelta += OnContentPresenterManipulationDelta;
                contentPresenter.SizeChanged += OnContentPresenterSizeChanged;
            }

            // Make cross-hair transparent to touch
            if (crossHairPart != null)
            {
                crossHairPart.IsHitTestVisible = false;
            }

            base.OnApplyTemplate();
        }

        void OnContentPresenterManipulationStarted(object sender, ManipulationStartedRoutedEventArgs args)
        {
            RecalculateValue(args.Position);
        }

        void OnContentPresenterManipulationDelta(object sender, ManipulationDeltaRoutedEventArgs args)
        {
            RecalculateValue(args.Position);
        }

        void OnContentPresenterSizeChanged(object sender, SizeChangedEventArgs args)
        {
            SetCrossHair();
        }

        void RecalculateValue(Point absolutePoint)
        {
            double x = Math.Max(0, Math.Min(1, absolutePoint.X / contentPresenter.ActualWidth));
            double y = Math.Max(0, Math.Min(1, absolutePoint.Y / contentPresenter.ActualHeight));
            this.Value = new Point(x, y);
        }

        void SetCrossHair()
        {
            if (contentPresenter != null && crossHairPart != null)
            {
                Canvas.SetLeft(crossHairPart, this.Value.X * contentPresenter.ActualWidth);
                Canvas.SetTop(crossHairPart, this.Value.Y * contentPresenter.ActualHeight);
            }
        }

        static void OnValueChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            (obj as XYSlider).SetCrossHair();
            (obj as XYSlider).OnValueChanged((Point)args.NewValue);
        }

        protected void OnValueChanged(Point value)
        {
            if (ValueChanged != null)
                ValueChanged(this, value);
        }
    }
}
