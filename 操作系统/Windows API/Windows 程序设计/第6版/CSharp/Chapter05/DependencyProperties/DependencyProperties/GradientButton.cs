using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace DependencyProperties
{
    public class GradientButton : Button
    {
        GradientStop gradientStop1, gradientStop2;

        static GradientButton()
        {
            Color1Property =
                DependencyProperty.Register("Color1",
                    typeof(Color),
                    typeof(GradientButton),
                    new PropertyMetadata(Colors.White, OnColorChanged));

            Color2Property =
                DependencyProperty.Register("Color2",
                    typeof(Color),
                    typeof(GradientButton),
                    new PropertyMetadata(Colors.Black, OnColorChanged));
        }

        public static DependencyProperty Color1Property { private set; get; }

        public static DependencyProperty Color2Property { private set; get; }

        public GradientButton()
        {
            gradientStop1 = new GradientStop
            {
                Offset = 0,
                Color = this.Color1
            };

            gradientStop2 = new GradientStop
            {
                Offset = 1,
                Color = this.Color2
            };

            LinearGradientBrush brush = new LinearGradientBrush();
            brush.GradientStops.Add(gradientStop1);
            brush.GradientStops.Add(gradientStop2);

            this.Foreground = brush;
        }

        public Color Color1
        {
            set { SetValue(Color1Property, value); }
            get { return (Color)GetValue(Color1Property); }
        }

        public Color Color2
        {
            set { SetValue(Color2Property, value); }
            get { return (Color)GetValue(Color2Property); }
        }

        static void OnColorChanged(DependencyObject obj,
                                   DependencyPropertyChangedEventArgs args)
        {
            (obj as GradientButton).OnColorChanged(args);
        }

        void OnColorChanged(DependencyPropertyChangedEventArgs args)
        {
            if (args.Property == Color1Property)
                gradientStop1.Color = (Color)args.NewValue;

            gradientStop1.Color = this.Color1;

            if (args.Property == Color2Property)
                gradientStop2.Color = (Color)args.NewValue;
        }
    }
}