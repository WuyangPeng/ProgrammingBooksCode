using System;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Media.Imaging;

namespace FingerPaint
{
    public partial class HslColorSelector : UserControl
    {
        bool doNotSetSliders = false;

        static readonly DependencyProperty colorProperty =
            DependencyProperty.Register("Color",
                typeof(Color), 
                typeof(HslColorSelector),
                new PropertyMetadata(new Color(), OnColorChanged));

        public event EventHandler<Color> ColorChanged;

        public HslColorSelector()
        {
            this.InitializeComponent();
            Loaded += OnLoaded;
        }

        async void OnLoaded(object sender, RoutedEventArgs args)
        {
            // Build bitmap for hue/saturation grid
            WriteableBitmap bitmap = new WriteableBitmap(256, 256);
            byte[] pixels = new byte[4 * 256 * 256];
            int index = 0;

            for (int y = 0; y < 256; y++)
                for (int x = 0; x < 256; x++)
                {
                    HSL hsl = new HSL((byte)x, (byte)(255 - y), (byte)128);
                    Color clr = hsl.Color;

                    pixels[index++] = clr.B;
                    pixels[index++] = clr.G;
                    pixels[index++] = clr.R;
                    pixels[index++] = clr.A;
                }

            using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
            {
                await pixelStream.WriteAsync(pixels, 0, pixels.Length);
            }
            bitmap.Invalidate();
            hsImage.Source = bitmap;
        }

        public static DependencyProperty ColorProperty
        {
            get { return colorProperty; }
        }

        public Color Color
        {
            set { SetValue(ColorProperty, value); }
            get { return (Color)GetValue(ColorProperty); }
        }

        // Event handlers for sliders
        void OnXYSliderValueChanged(object sender, Point point)
        {
            HSL hsl = new HSL(360 * point.X, 1 - point.Y, 0.5);
            sliderGradientStop.Color = hsl.Color;
            SetColorFromSliders();
        }

        void OnSliderValueChanged(object sender, RangeBaseValueChangedEventArgs args)
        {
            SetColorFromSliders();
        }

        void SetColorFromSliders()
        {
            Point point = xySlider.Value;
            double value = slider.Value;
            HSL hsl = new HSL(360 * point.X, 1 - point.Y, value / 100);

            doNotSetSliders = true;
            this.Color = hsl.Color;
            doNotSetSliders = false;
        }

        // Color property-changed handlers
        static void OnColorChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            (obj as HslColorSelector).OnColorChanged((Color)args.NewValue);
        }

        protected void OnColorChanged(Color color)
        {
            HSL hsl = new HSL(color);

            if (!doNotSetSliders)
            {
                xySlider.Value = new Point(hsl.Hue / 360, 1 - hsl.Saturation);
                slider.Value = 100 * hsl.Lightness;
            }

            txtblk.Text = String.Format("RGB = ({0}, {1}, {2})",
                                        this.Color.R, this.Color.G, this.Color.B);

            if (ColorChanged != null)
                ColorChanged(this, color);
        }
    }
}
