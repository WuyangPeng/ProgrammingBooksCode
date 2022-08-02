using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace DependencyPropertiesWithBindings
{
    public sealed partial class GradientButton : Button
    {
        static GradientButton()
        {
            Color1Property =
                DependencyProperty.Register("Color1",
                    typeof(Color),
                    typeof(GradientButton),
                    new PropertyMetadata(Colors.White));

            Color2Property =
                DependencyProperty.Register("Color2",
                    typeof(Color),
                    typeof(GradientButton),
                    new PropertyMetadata(Colors.Black));
        }

        public static DependencyProperty Color1Property { private set; get; }

        public static DependencyProperty Color2Property { private set; get; }

        public GradientButton()
        {
            this.InitializeComponent();
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
    }
}
