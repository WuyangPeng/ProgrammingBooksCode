using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace FingerPaint
{
    public class XYSlider : ContentControl
    {
        ContentPresenter contentPresenter;
        FrameworkElement crossHairPart;
        Dictionary<uint, Point> pointerDictionary = new Dictionary<uint, Point>();

        static readonly DependencyProperty valueProperty = 
                DependencyProperty.Register("Value",
                        typeof(Point), typeof(XYSlider), 
                        new PropertyMetadata(new Point(), OnValueChanged));

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
                contentPresenter.PointerPressed -= OnContentPresenterPointerPressed;
                contentPresenter.PointerMoved -= OnContentPresenterPointerMoved;
                contentPresenter.PointerReleased -= OnContentPresenterPointerReleased;
                contentPresenter.PointerCaptureLost -= OnContentPresenterPointerReleased;
                contentPresenter.SizeChanged -= OnContentPresenterSizeChanged;
            }

            // Get new parts
            crossHairPart = GetTemplateChild("CrossHairPart") as FrameworkElement;
            contentPresenter = GetTemplateChild("ContentPresenterPart") as ContentPresenter;

            // Attach event handlers
            if (contentPresenter != null)
            {
                contentPresenter.PointerPressed += OnContentPresenterPointerPressed;
                contentPresenter.PointerMoved += OnContentPresenterPointerMoved;
                contentPresenter.PointerReleased += OnContentPresenterPointerReleased;
                contentPresenter.PointerCaptureLost += OnContentPresenterPointerReleased;
                contentPresenter.SizeChanged += OnContentPresenterSizeChanged;
            }

            // Make cross-hair transparent to touch
            if (crossHairPart != null)
            {
                crossHairPart.IsHitTestVisible = false;
            }

            base.OnApplyTemplate();
        }

        void OnContentPresenterPointerPressed(object sender, PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(contentPresenter).Position;
            pointerDictionary.Add(id, point);
            contentPresenter.CapturePointer(args.Pointer);

            RecalculateValue();
            args.Handled = true;
        }

        void OnContentPresenterPointerMoved(object sender, PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(contentPresenter).Position;

            if (pointerDictionary.ContainsKey(id))
            {
                pointerDictionary[id] = point;
                RecalculateValue();
                args.Handled = true;
            }
        }

        void OnContentPresenterPointerReleased(object sender, PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (pointerDictionary.ContainsKey(id))
            {
                pointerDictionary.Remove(id);
                RecalculateValue();
                args.Handled = true;
            }
        }

        void OnContentPresenterSizeChanged(object sender, SizeChangedEventArgs args)
        {
            SetCrossHair();
        }

        void RecalculateValue()
        {
            if (pointerDictionary.Values.Count > 0)
            {
                Point accumPoint = new Point();

                // Average all the current touch points
                foreach (Point point in pointerDictionary.Values)
                {
                    accumPoint.X += point.X;
                    accumPoint.Y += point.Y;
                }
                accumPoint.X /= pointerDictionary.Values.Count;
                accumPoint.Y /= pointerDictionary.Values.Count;

                RecalculateValue(accumPoint);
            }
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
